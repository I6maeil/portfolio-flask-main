from dotenv import load_dotenv
load_dotenv()
from flask import Flask, render_template, request, redirect, flash, url_for, Response
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime
import smtplib
from email.message import EmailMessage
from functools import wraps
import os

app = Flask(__name__)
app.secret_key = os.environ.get("FLASK_SECRET", "change_this_secret")

base_dir = os.path.abspath(os.path.dirname(__file__))
db_path = os.path.join(base_dir, "database.db")

env_db_url = os.environ.get("DATABASE_URL")
if env_db_url:
    if env_db_url.startswith("postgres://"):
        env_db_url = env_db_url.replace("postgres://", "postgresql://", 1)
    app.config['SQLALCHEMY_DATABASE_URI'] = env_db_url
else:
    app.config['SQLALCHEMY_DATABASE_URI'] = f"sqlite:///{db_path}"

app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

class Message(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(120), nullable=False)
    email = db.Column(db.String(120), nullable=False)
    message = db.Column(db.Text, nullable=False)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)

with app.app_context():
    db.create_all()

@app.context_processor
def inject_now():
    return {'now': datetime.utcnow()}

# ✅ Gmail مكتوب مباشرة
EMAIL_ADDRESS = "benismail722@gmail.com"
EMAIL_PASSWORD = "vwbcvuphyslgsyvl"

def send_email(name, email, message_text):
    msg = EmailMessage()
    msg['Subject'] = f"Nouveau message de {name}"
    msg['From'] = EMAIL_ADDRESS
    msg['To'] = EMAIL_ADDRESS
    msg.set_content(f"Nom: {name}\nEmail: {email}\nMessage:\n{message_text}")
    with smtplib.SMTP_SSL('smtp.gmail.com', 465) as smtp:
        smtp.login(EMAIL_ADDRESS, EMAIL_PASSWORD)
        smtp.send_message(msg)

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