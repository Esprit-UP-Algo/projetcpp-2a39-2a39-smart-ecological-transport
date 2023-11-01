#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dechets.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Afficher->setModel(d.afficher()); //constructeur afficahge tableaur
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    ui->Afficher->setModel(d.afficher());

}

void MainWindow::on_pushButton_6_clicked()   // bouton ajouter
{
    QString nom =ui->nom->text();
    QString type =ui->nom->text();
    QString poids =ui->nom->text();
    QString volume=ui->nom->text();
    QString matiere =ui->nom->text();
    QString destinataire =ui->nom->text();
    QString etat =ui->nom->text();
    QString Date =ui->nom->text();

    /// reste des attrubuts
    Dechets e ( nom ,type ,poids ,volume ,etat ,destinataire ,matiere ,Date  ); // attributs : construction mtaa objet dechets : fel mainwindow.h normalement
    bool test = e.ajouter() ; //nerjaa le base de données (car cnx avec QT )pour vérifier est ce que l'ajout est correcte et vérifier ou non
    if (test)
    {
        ui->Afficher->setModel(e.afficher());


        QMessageBox::information(nullptr, QObject::tr("ajout effuctué"),  QObject::tr("connection successful.\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else

                QMessageBox::critical(nullptr, QObject::tr("ajout n'est pas effuctué"),QObject::tr("connection failed.\n"  "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_7_clicked() // bouton supprimer
{
    QString nom =ui->nom->text();
    QString type =ui->nom->text();
    QString poids =ui->nom->text();
    QString volume=ui->nom->text();
    QString matiere =ui->nom->text();
    QString destinataire =ui->nom->text();
    QString etat =ui->nom->text();
    QString Date =ui->nom->text();

    /// reste des attrubuts
    Dechets d ( nom,type,poids,volume,etat,destinataire,matiere,Date );      // aprés suppression il y aura une nouvelle construction d'un nouvel objet dechets
    bool test = d.supprimer() ;
    if (test)
    {
        ui->Afficher->setModel(d.supprimer());


        QMessageBox::information(nullptr, QObject::tr("suppression effuctué"),  QObject::tr("connection successful.\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else

                QMessageBox::critical(nullptr, QObject::tr("suppression n'est pas effuctué"),QObject::tr("connection failed.\n"  "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_8_clicked() // bouton modifier
{
    QString nom =ui->nom->text();
    QString type =ui->nom->text();
    QString poids =ui->nom->text();
    QString volume=ui->nom->text();
    QString matiere =ui->nom->text();
    QString destinataire =ui->nom->text();
    QString etat =ui->nom->text();
    QString Date =ui->nom->text();

    /// reste des attrubuts
    Dechets d ( nom,type,poids,volume,etat,destinataire,matiere,Date );
    bool test = d.modifier() ;
    if (test)
    {
        ui->Afficher->setModel(d.modifier());


        QMessageBox::information(nullptr, QObject::tr("modification effuctué"),  QObject::tr("connection successful.\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else

                QMessageBox::critical(nullptr, QObject::tr("modification n'est pas effuctué"),QObject::tr("connection failed.\n"  "Click Cancel to exit."), QMessageBox::Cancel);
}
