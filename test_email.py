import smtplib
from email.message import EmailMessage

EMAIL_ADDRESS = "benismail722@gmail.com"          # بدلها بالإيميل ديالك
EMAIL_PASSWORD = "srkbhgqevpxggcjppyth"  # App Password من Gmail

try:
    msg = EmailMessage()
    msg['Subject'] = "Test Email"
    msg['From'] = EMAIL_ADDRESS
    msg['To'] = EMAIL_ADDRESS
    msg.set_content("Si ça marche, vous allez recevoir cet email.")

    with smtplib.SMTP_SSL('smtp.gmail.com', 465) as smtp:
        smtp.login(EMAIL_ADDRESS, EMAIL_PASSWORD)
        smtp.send_message(msg)
    
    print("✅ Email envoyé avec succès !")
except Exception as e:
    print("❌ Erreur:", e)
