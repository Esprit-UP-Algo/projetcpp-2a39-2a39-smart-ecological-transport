#ifndef FACTURE_H
#define FACTURE_H


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

class Facture : public QObject {
    Q_OBJECT
public:
    Facture(int id_v);

    bool estPayee() const;
    void payerFacture();

private:
    int id_v;
    bool estPaye;
};

class SMSManager : public QObject {
    Q_OBJECT
public slots:
    void envoyerSMS(const std::string& numeroPortable, const std::string& message);
};

class FactureApp : public QWidget {
    Q_OBJECT
public:
    FactureApp();

private slots:
    void onEnvoyerSMSClicked();

private:
    void initUI();
    void initConnections();

    QLineEdit* idLineEdit;
    QLineEdit* numeroPortableLineEdit;
    QPushButton* envoyerSMSButton;
    SMSManager smsManager;
    Facture facture;
};



#endif // FACTURE_H
