from dotenv import load_dotenv
load_dotenv()
from flask import Flask, render_template, request, redirect, flash, url_for, Response, session, jsonify, send_from_directory
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime
from functools import wraps
from authlib.integrations.flask_client import OAuth
from werkzeug.middleware.proxy_fix import ProxyFix
import resend
import os

app = Flask(__name__)

# Secret key configuration (respects SECRET_KEY and FLASK_SECRET)
app.secret_key = os.environ.get("SECRET_KEY") or os.environ.get("FLASK_SECRET", "change_this_secret")

# Secure Session Cookies
is_production = os.environ.get('FLASK_ENV') == 'production' or bool(os.environ.get('RENDER'))
app.config.update(
    SESSION_COOKIE_HTTPONLY=True,
    SESSION_COOKIE_SAMESITE='Lax',
    SESSION_COOKIE_SECURE=is_production and not app.debug
)

# Reverse proxy support for Render / production HTTPS
if is_production:
    app.wsgi_app = ProxyFix(app.wsgi_app, x_for=1, x_proto=1, x_host=1, x_prefix=1)

# Authlib Google OAuth 2.0 configuration
oauth = OAuth(app)
oauth.register(
    name='google',
    client_id=os.environ.get('GOOGLE_CLIENT_ID'),
    client_secret=os.environ.get('GOOGLE_CLIENT_SECRET'),
    server_metadata_url='https://accounts.google.com/.well-known/openid-configuration',
    client_kwargs={
        'scope': 'openid email profile'
    }
)

base_dir = os.path.abspath(os.path.dirname(__file__))
db_path = os.path.join(base_dir, "database.db")

env_db_url = os.environ.get("DATABASE_URL")
if env_db_url:
    if env_db_url.startswith("postgres://"):
        env_db_url = env_db_url.replace("postgres://", "postgresql://", 1)
    app.config['SQLALCHEMY_DATABASE_URI'] = env_db_url
else:
    if os.environ.get("VERCEL"):
        app.config['SQLALCHEMY_DATABASE_URI'] = "sqlite:////tmp/site.db"
    else:
        app.config['SQLALCHEMY_DATABASE_URI'] = f"sqlite:///{db_path}"

app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

# ----------------------------------------------------
# Protected Projects Configuration
# Real links and files are kept private on the backend
# ----------------------------------------------------
PROJECTS = {
    "lingua-ai": {
        "title": "LinguaAI",
        "links": {
            "github": "https://github.com/I6maeil/LinguaAI",
            "demo": "https://github.com/I6maeil/LinguaAI"
        },
        "file": {
            "filename": "lingua-ai-preview.zip",
            "directory": os.path.join(base_dir, "private_files")
        }
    },
    "souk-ma": {
        "title": "Souk.ma",
        "links": {
            "demo": "https://portfolio-project11.vercel.app/",
            "github": "https://github.com/I6maeil/souk-ma"
        }
    },
    "cvcraft": {
        "title": "CVCraft",
        "links": {
            "demo": "https://portfolio-project-sable-omega.vercel.app/",
            "github": "https://github.com/I6maeil/cvcraft"
        }
    }
}

def validate_return_url(url):
    """
    Validate return URL to prevent Open Redirect attacks.
    Accepts only internal paths starting with '/' and not '//'.
    """
    if url and url.startswith('/') and not url.startswith('//'):
        return url
    return '/portfolio#portfolio'

class Message(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(120), nullable=False)
    email = db.Column(db.String(120), nullable=False)
    message = db.Column(db.Text, nullable=False)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)

with app.app_context():
    try:
        db.create_all()
    except Exception as e:
        print(f"Database initialization error: {e}")

@app.context_processor
def inject_now():
    return {'now': datetime.utcnow()}

resend.api_key = os.environ.get("RESEND_API_KEY")

def send_email(name, email, message_text):
    resend.Emails.send({
        "from": "onboarding@resend.dev",
        "to": "benismail722@gmail.com",
        "subject": f"Nouveau message de {name}",
        "text": f"Nom: {name}\nEmail: {email}\nMessage:\n{message_text}"
    })

ADMIN_USERNAME = os.environ.get("ADMIN_USERNAME", "admin")
ADMIN_PASSWORD = os.environ.get("ADMIN_PASSWORD", "1234")

def check_auth(username, password):
    return username == ADMIN_USERNAME and password == ADMIN_PASSWORD

def authenticate():
    return Response('Non autorisé.', 401, {'WWW-Authenticate': 'Basic realm="Login Required"'})

def requires_auth(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        auth = request.authorization
        if not auth or not check_auth(auth.username, auth.password):
            return authenticate()
        return f(*args, **kwargs)
    return decorated

# ----------------------------------------------------
# Main Public Views
# ----------------------------------------------------
@app.route('/')
def index():
    return render_template('home.html')

@app.route('/skills')
def skills():
    return render_template('skills.html')

@app.route('/services')
def services():
    return render_template('services.html')

@app.route('/portfolio')
def portfolio():
    return render_template('portfolio.html')

@app.route('/certifications')
def certifications():
    return render_template('certifications.html')

@app.route('/contact')
def contact_page():
    return render_template('contact.html')

# ----------------------------------------------------
# Google OAuth 2.0 & Session Management
# ----------------------------------------------------
@app.route('/login/google')
def login_google():
    # Capture return URL, sanitized to avoid open redirects
    return_url = request.args.get('next', '/portfolio#portfolio')
    session['next_url'] = validate_return_url(return_url)
    
    redirect_uri = url_for('auth_google_callback', _external=True)
    if request.headers.get('X-Forwarded-Proto') == 'https' and redirect_uri.startswith('http://'):
        redirect_uri = redirect_uri.replace('http://', 'https://', 1)
        
    return oauth.google.authorize_redirect(redirect_uri)

@app.route('/auth/google/callback')
def auth_google_callback():
    try:
        token = oauth.google.authorize_access_token()
    except Exception as e:
        print(f"OAuth Callback Error: {e}")
        flash("Échec de l'authentification Google. Veuillez réessayer.", "error")
        return redirect(url_for('portfolio') + '#portfolio')
    
    user_info = token.get('userinfo')
    if not user_info:
        try:
            user_info = oauth.google.userinfo()
        except Exception as e:
            print(f"OAuth Userinfo Error: {e}")
            user_info = None
            
    if not user_info:
        flash("Impossible de récupérer le profil Google.", "error")
        return redirect(url_for('portfolio') + '#portfolio')
        
    # Check that email_verified is true
    if not user_info.get('email_verified'):
        flash("Votre adresse email Google n'a pas été validée.", "error")
        return redirect(url_for('portfolio') + '#portfolio')
        
    # Store user profile in Flask session only (no DB required)
    session['user'] = {
        'name': user_info.get('name') or user_info.get('given_name') or 'Utilisateur',
        'email': user_info.get('email'),
        'picture': user_info.get('picture')
    }
    
    next_url = validate_return_url(session.pop('next_url', '/portfolio#portfolio'))
    return redirect(next_url)

@app.route('/logout')
def logout():
    session.pop('user', None)
    flash("Vous avez été déconnecté avec succès.", "info")
    return redirect(url_for('portfolio') + '#portfolio')

# ----------------------------------------------------
# Protected APIs for Project Access
# ----------------------------------------------------
@app.route('/api/me')
def api_me():
    user = session.get('user')
    if user:
        return jsonify({
            'logged_in': True,
            'name': user.get('name'),
            'picture': user.get('picture')
        })
    return jsonify({
        'logged_in': False,
        'name': None,
        'picture': None
    })

@app.route('/api/project/<slug>/<action>')
def api_project_action(slug, action):
    # Guard: Require active Google OAuth session
    if not session.get('user'):
        return jsonify({'error': 'Unauthorized', 'login_required': True}), 401
        
    project = PROJECTS.get(slug)
    if not project:
        return jsonify({'error': 'Projet introuvable'}), 404
        
    if action == 'download':
        file_info = project.get('file')
        if not file_info:
            return jsonify({'error': 'Aucun fichier disponible pour ce projet'}), 404
            
        directory = file_info.get('directory')
        filename = file_info.get('filename')
        if not os.path.exists(os.path.join(directory, filename)):
            return jsonify({'error': 'Fichier non trouvé sur le serveur'}), 404
            
        return send_from_directory(directory, filename, as_attachment=True)
        
    links = project.get('links', {})
    url = links.get(action)
    if not url:
        return jsonify({'error': f"Action '{action}' non supportée pour ce projet"}), 400
        
    return jsonify({
        'slug': slug,
        'action': action,
        'url': url
    })

# ----------------------------------------------------
# Contact & Admin Routes
# ----------------------------------------------------
@app.route('/contact', methods=['POST'])
def contact():
    try:
        name = request.form.get('name', '').strip()
        email = request.form.get('email', '').strip()
        message_text = request.form.get('message', '').strip()

        if not name or not email or not message_text:
            flash("Tous les champs sont obligatoires.", "error")
            return redirect(url_for('contact_page'))

        msg = Message(name=name, email=email, message=message_text)
        db.session.add(msg)
        db.session.commit()

        try:
            send_email(name, email, message_text)
            flash("Message envoyé et sauvegardé avec succès !", "success")
        except Exception as e:
            print(f"Email Error: {e}")
            flash("Message sauvegardé, mais erreur d'envoi mail.", "warning")

    except Exception as e:
        db.session.rollback()
        print(f"Server Error: {e}")
        flash("Une erreur interne est survenue.", "error")

    return redirect(url_for('contact_page'))

@app.route('/admin')
@requires_auth
def admin():
    messages = Message.query.order_by(Message.created_at.desc()).all()
    return render_template('admin.html', messages=messages)

@app.route('/admin/delete/<int:id>', methods=['POST'])
@requires_auth
def delete_message(id):
    msg = Message.query.get_or_404(id)
    db.session.delete(msg)
    db.session.commit()
    flash("Message supprimé.", "success")
    return redirect(url_for('admin'))

if __name__ == '__main__':
    port = int(os.environ.get("PORT", 5000))
    app.run(host='0.0.0.0', port=port, debug=True)
