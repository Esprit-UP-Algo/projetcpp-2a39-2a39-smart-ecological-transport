#include <QtNetwork>
#include "sms.h"
#include <QString>
#include <QNetworkAccessManager>


QString twilio_phone_number = "+12566079155";
sms::sms(){

}
void sms::sendSMS(const QString &to, const QString &message) {
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QUrl url("https://api.twilio.com/2010-04-01/Accounts/ACde1831165998c43ce434a2613ffef657/Messages.json");
    QNetworkRequest request(url);


    QString credentials = "ACde1831165998c43ce434a2613ffef657:b6136482ff41d91904931e1ce0c3fbe5";
    QByteArray base64Credentials = credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + base64Credentials);


    QByteArray postData;
    postData.append("From="+twilio_phone_number);
    postData.append("&To=" + to);
    postData.append("&Body=" + message);


    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Make the request
    QNetworkReply *reply = manager->post(request, postData);


    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "SMS sent successfully";
        } else {
            qDebug() << "Failed to send SMS:" << reply->errorString();
        }


        reply->deleteLater();
        manager->deleteLater();
    });
}
