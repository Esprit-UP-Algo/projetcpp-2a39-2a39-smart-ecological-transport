#include "facture.h"
#include<QtDebug>
#include<QLabel>

Facture::Facture(int id) : id(id), estPaye(false) {}

bool Facture::estPayee() const {
    return estPaye;
}

void Facture::payerFacture() {
    estPaye = true;
}

void SMSManager::envoyerSMS(const std::string& numeroPortable, const std::string& message) {
    // Code pour envoyer un SMS avec le service approprié
    qDebug() << "Envoi du SMS à " << numeroPortable.c_str() << ": " << message.c_str();
}

FactureApp::FactureApp() : facture(0) {
    initUI();
    initConnections();
}

void FactureApp::initUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* idLayout = new QHBoxLayout;
    idLayout->addWidget(new QLabel("ID de la facture:"));
    idLineEdit = new QLineEdit;
    idLayout->addWidget(idLineEdit);

    QHBoxLayout* numeroPortableLayout = new QHBoxLayout;
    numeroPortableLayout->addWidget(new QLabel("Numéro de portable:"));
    numeroPortableLineEdit = new QLineEdit;
    numeroPortableLayout->addWidget(numeroPortableLineEdit);

    envoyerSMSButton = new QPushButton("Envoyer SMS");

    mainLayout->addLayout(idLayout);
    mainLayout->addLayout(numeroPortableLayout);
    mainLayout->addWidget(envoyerSMSButton);
}

void FactureApp::initConnections() {
    connect(envoyerSMSButton, &QPushButton::clicked, this, &FactureApp::onEnvoyerSMSClicked);
}

void FactureApp::onEnvoyerSMSClicked() {
    int id_v = idLineEdit->text().toInt();
    std::string numeroPortable = numeroPortableLineEdit->text().toStdString();

    if (facture.estPayee()) {
        QMessageBox::information(this, "Information", "La facture est déjà payée.");
    } else {
        std::string message = "Votre facture a été payée avec succès. Merci!";
        smsManager.envoyerSMS(numeroPortable, message);

        facture.payerFacture();
        QMessageBox::information(this, "Information", "La facture a été marquée comme payée.");
    }
}

