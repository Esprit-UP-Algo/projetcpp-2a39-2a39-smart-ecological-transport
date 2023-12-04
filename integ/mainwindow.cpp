#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTextStream>
#include <QTextDocument>
#include <QDesktopWidget>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include <iostream>
#include <QMediaPlayer>
#include <QUrl>
#include <QVideoWidget>
#include <QSqlQuery>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSeries>
#include <QPieSlice>
#include <QDateTime>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
    ui->emp_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
    ui->qan_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
    ui->qual_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
    ui->t_c->setModel(Etmp.afficher());
    ui->le_id_v->setValidator(new QIntValidator(100, 999999999, this));
    ui->stackedWidget->setCurrentIndex(0);

    ui->le_qua->setValidator(new QIntValidator(100, 999999999, this));
    ui->le_type->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
    ui->le_prix->setValidator(new QIntValidator(100, 999999999, this));
    ui->le_montant->setValidator(new QIntValidator(100, 999999999, this));
    //ui->le_id_col->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
    ui->tab_vente->setModel(v.afficher());
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(20);
    effect->setXOffset(2);
    effect->setYOffset(2);
    effect->setColor(Qt::lightGray);
    ui->frame->setGraphicsEffect(effect);
    QGraphicsDropShadowEffect *effect8 = new QGraphicsDropShadowEffect;
    effect8->setBlurRadius(20);
    effect8->setXOffset(2);
    effect8->setYOffset(2);
    effect8->setColor(Qt::lightGray);
    ui->frame_7->setGraphicsEffect(effect8);
    QGraphicsDropShadowEffect *effect20 = new QGraphicsDropShadowEffect;
    effect20->setBlurRadius(20);
    effect20->setXOffset(2);
    effect20->setYOffset(2);
    effect20->setColor(Qt::lightGray);
    ui->frame_13->setGraphicsEffect(effect20);
    QGraphicsDropShadowEffect *effect9 = new QGraphicsDropShadowEffect;
    effect9->setBlurRadius(20);
    effect9->setXOffset(2);
    effect9->setYOffset(2);
    effect9->setColor(Qt::lightGray);
    ui->frame_6->setGraphicsEffect(effect9);
    QGraphicsDropShadowEffect *effect10 = new QGraphicsDropShadowEffect;
    effect10->setBlurRadius(20);
    effect10->setXOffset(2);
    effect10->setYOffset(2);
    effect10->setColor(Qt::lightGray);
    ui->frame_5->setGraphicsEffect(effect10);
    QGraphicsDropShadowEffect *effect11 = new QGraphicsDropShadowEffect;
    effect11->setBlurRadius(20);
    effect11->setXOffset(2);
    effect11->setYOffset(2);
    effect11->setColor(Qt::lightGray);
    ui->frame_8->setGraphicsEffect(effect11);
    QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect;
    effect1->setBlurRadius(20);
    effect1->setXOffset(2);
    effect1->setYOffset(2);
    effect1->setColor(Qt::lightGray);
    ui->frame_2->setGraphicsEffect(effect1);
    QGraphicsDropShadowEffect *effect3 = new QGraphicsDropShadowEffect;
    effect3->setBlurRadius(20);
    effect3->setXOffset(2);
    effect3->setYOffset(2);
    effect3->setColor(Qt::lightGray);
    ui->frame_9->setGraphicsEffect(effect3);
    QGraphicsDropShadowEffect *effect4 = new QGraphicsDropShadowEffect;
    effect4->setBlurRadius(20);
    effect4->setXOffset(2);
    effect4->setYOffset(2);
    effect4->setColor(Qt::lightGray);
    ui->frame_10->setGraphicsEffect(effect4);
    QGraphicsDropShadowEffect *effect5 = new QGraphicsDropShadowEffect;
    effect5->setBlurRadius(20);
    effect5->setXOffset(2);
    effect5->setYOffset(2);
    effect5->setColor(Qt::lightGray);
    ui->frame_11->setGraphicsEffect(effect5);
    QGraphicsDropShadowEffect *effect6 = new QGraphicsDropShadowEffect;
    effect6->setBlurRadius(20);
    effect6->setXOffset(2);
    effect6->setYOffset(2);
    effect6->setColor(Qt::lightGray);
    ui->frame_12->setGraphicsEffect(effect6);
    ui->Afficher->setModel(d.afficher()); //constructeur afficahge tableaur
    ui->tablehistorique->setModel(d.afficher_historique());
    QRegularExpression rx("^[A-Za-z]+$");
    QSqlQuery query;
    query.prepare("select  nom from dechets");
                   query.exec();
                   while (query.next())

    ui->nomdechet->addItem(query.value(0).toString());
                   ui->t_c->setModel(Etmp.afficher());

                QValidator *validator = new QRegularExpressionValidator(rx, this);
                ui->nom->setValidator(validator);
    ui->poids->setValidator(new QIntValidator(0,999999999));

//             chartdechets=d.statistique_chart();

//            QChartView *chartviedechets = new QChartView(chartdechets,ui->Stat);

//            chartviedechets->setMinimumSize(441,301);

//            chartviedechets->setRenderHint(QPainter::Antialiasing);

//chartviedechets->show();
ui->pushButton_3->clicked();
ui->tab_vente->setModel((v.afficher()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCamera(const QCameraInfo &cameraInfo)
{
    Camera = new QCamera(cameraInfo);
    imageCapture = new QCameraImageCapture(Camera);
    Camera->setViewfinder(ui->viewfinder_3);
    connect(imageCapture, &QCameraImageCapture::readyForCaptureChanged, this, &MainWindow::readyForCapture);
    Camera->start();
}


void MainWindow::readyForCapture(bool ready)
{
    ui->takeImageButton->setEnabled(ready);
}
void MainWindow::on_takeImageButton_clicked()
{
    isCapturingImage = true;
    imageCapture->capture();
}


void MainWindow::init_button(QWidget *q,QString link)
{

    q->setStyleSheet("background: transparent;border-radius:60px;color: white;qproperty-icon:url('"+link+"');font: 40pt  'Oswald';font-size:22px;");
}



void MainWindow::on_pushButton_12_clicked()
{
    ui->pushButton_11->setChecked(false);
    ui->pushButton_12->setChecked(true);
    ui->pushButton_13->setChecked(false);
    ui->pushButton_14->setChecked(false);
    ui->pushButton_3->setChecked(false);

    ui->pushButton_12->setStyleSheet("qproperty-icon:url(:/icons/icons/reservation1.png);background: white;border-image:url(:/img/img/final.png);color: #379237;font: 40pt  'Oswald';font-size:22px;");
    init_button(ui->pushButton_14,":/icons/icons/container.png");
    init_button(ui->pushButton_13,":/icons/icons/hand.png");
    init_button(ui->pushButton_11,":/icons/icons/bin.png");
    init_button(ui->pushButton_3,":/icons/icons/info1.png");
    ui->stackedWidget->setCurrentIndex(2);
    on_pushButton_STAT_clicked();

    ui->t_c->setModel(Etmp.afficher());

}


void MainWindow::on_pushButton_11_clicked()
{
    ui->pushButton_12->setChecked(false);
    ui->pushButton_13->setChecked(false);
    ui->pushButton_14->setChecked(false);
    ui->pushButton_11->setChecked(true);
    ui->pushButton_3->setChecked(false);
Dechets e;
   ui->Afficher->setModel(e.afficher());

        ui->pushButton_11->setStyleSheet("qproperty-icon:url(:/icons/icons/bin1.png);background: white;border-image:url(:/img/img/final.png);color: #379237;font: 40pt  'Oswald';font-size:22px;");
init_button(ui->pushButton_14,":/icons/icons/container.png");
init_button(ui->pushButton_13,":/icons/icons/hand.png");
init_button(ui->pushButton_12,":/icons/icons/reservation.png");
init_button(ui->pushButton_3,":/icons/icons/info1.png");
ui->stackedWidget->setCurrentIndex(1);

statistique_chart();

}

void MainWindow::on_pushButton_13_clicked()
{
    ui->pushButton_11->setChecked(false);
    ui->pushButton_12->setChecked(false);
    ui->pushButton_14->setChecked(false);
    ui->pushButton_13->setChecked(true);
    ui->pushButton_3->setChecked(false);

    ui->stackedWidget->setCurrentIndex(3);

    ui->tab_vente->setModel((v.afficher()));

    ui->pushButton_13->setStyleSheet("qproperty-icon:url(:/icons/icons/hand1.png);background: white;border-image:url(:/img/img/final.png);color: #379237;font: 40pt  'Oswald';font-size:22px;");
init_button(ui->pushButton_14,":/icons/icons/container.png");
init_button(ui->pushButton_12,":/icons/icons/reservation.png");
init_button(ui->pushButton_11,":/icons/icons/bin.png");
init_button(ui->pushButton_3,":/icons/icons/info1.png");
stat();
setCamera(QCameraInfo::defaultCamera());
conteneur E;
ui->tab_cont-> setModel(E.afficher());

}

void MainWindow::on_pushButton_14_clicked()
{
    ui->pushButton_11->setChecked(false);
    ui->pushButton_13->setChecked(false);
    ui->pushButton_12->setChecked(false);
    ui->pushButton_14->setChecked(true);
    ui->pushButton_3->setChecked(false);
    ui->stackedWidget->setCurrentIndex(4);

        ui->pushButton_14->setStyleSheet("qproperty-icon:url(:/icons/icons/container1.png);background: white;border-image:url(:/img/img/final.png);color: #379237;font: 40pt  'Oswald';font-size:22px;");
init_button(ui->pushButton_13,":/icons/icons/hand.png");
init_button(ui->pushButton_12,":/icons/icons/reservation.png");
init_button(ui->pushButton_11,":/icons/icons/bin.png");
init_button(ui->pushButton_3,":/icons/icons/info1.png");


}


void MainWindow::on_pushButton_3_clicked()
{
    ui->pushButton_11->setChecked(false);
    ui->pushButton_12->setChecked(false);
    ui->pushButton_13->setChecked(false);
    ui->pushButton_14->setChecked(false);
    ui->pushButton_3->setChecked(true);
  ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_3->setStyleSheet("qproperty-icon:url(:/icons/icons/info.png);background: white;border-image:url(:/icons/icons/info0.png);color: #379237;font: 40pt  'Oswald';font-size:22px;");
    init_button(ui->pushButton_14,":/icons/icons/container.png");
    init_button(ui->pushButton_13,":/icons/icons/hand.png");
    init_button(ui->pushButton_12,":/icons/icons/reservation.png");
    init_button(ui->pushButton_11,":/icons/icons/bin.png");



}

void MainWindow::on_pushButton_6_clicked()   // bouton ajouter
{
    QString nom =ui->nom->text();
    //type est un combobox donc currentText donne la valeur choisie
    QString type =ui->type->currentText();
    float poids =ui->poids->text().toFloat();
    float volume=ui->volume->text().toFloat();
    QString matiere =ui->matiere->currentText();
    QString destinataire =ui->destintaire->text();
    QString etat =ui->etat->currentText();
    QDate Date =ui->date->date();
qDebug()<<nom<<type<<poids<<volume<<matiere<<destinataire<<etat<<Date;
    /// reste des attributs
    Dechets e (nom ,type ,poids ,volume ,etat ,destinataire ,matiere ,Date); // attributs : construction mtaa objet dechets : fel mainwindow.h normalement
    bool test = e.ajouter() ; //nerjaa le base de données (car cnx avec QT )pour vérifier est ce que l'ajout est correcte et vérifier ou non
    if (test)
    {
        ui->Afficher->setModel(e.afficher());


        QMessageBox::information(nullptr, QObject::tr("Succés"),  QObject::tr("ajout effectué avec succés.\n" "Click OK to exit."), QMessageBox::Ok);
        }
        else

                QMessageBox::critical(nullptr, QObject::tr("Erreur"),QObject::tr("Ajout n'est pas effectué.\n"  "Click OK to exit."), QMessageBox::Ok);
    statistique_chart();
}

void MainWindow::on_pushButton_7_clicked() // bouton supprimer
{
    // Get the selection model for the table view
    QItemSelectionModel *selectionModel = ui->Afficher->selectionModel();

    // Check if any item is selected
    if (selectionModel->hasSelection())
    {
        // Get the selected item's QModelIndex
        QModelIndex selectedIndex = selectionModel->selectedIndexes().first();

        // Extract the "id" from the selected item
        int column = 0; // Assuming "id" is in the first column
        int id = selectedIndex.sibling(selectedIndex.row(), column).data().toInt();

        // Call the supprimer(int id) function with the selected "id"
        bool deletionSuccessful = d.supprimer(id);

        if (deletionSuccessful)
        {
            // Refresh the table view
            ui->Afficher->setModel(d.afficher());

            QMessageBox::information(nullptr, QObject::tr("Succès"), QObject::tr("Suppression effectuée avec succès.\nClick OK to exit."), QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Suppression n'est pas effectuée.\nClick OK to exit."), QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::warning(nullptr, QObject::tr("Avertissement"), QObject::tr("Aucun élément sélectionné.\nSélectionnez un élément à supprimer."), QMessageBox::Ok);
    }
    statistique_chart();
}


void MainWindow::on_pushButton_8_clicked() // bouton modifier
{
    // Get the selected item's QModelIndex
        QItemSelectionModel *selectionModel = ui->Afficher->selectionModel();
        if (selectionModel->hasSelection())
        {
            QModelIndex selectedIndex = selectionModel->selectedIndexes().first();
            int column = 0; // Assuming "id" is in the first column
            int id = selectedIndex.sibling(selectedIndex.row(), column).data().toInt();

            // Get the new values from the UI elements
            QString newNom = ui->nom->text();
            QString newType = ui->type->currentText();
            float newPoids = ui->poids->text().toFloat();
            float newVolume = ui->volume->text().toFloat();
            QString newMatiere = ui->matiere->currentText();
            QString newDestinataire = ui->destintaire->text();
            QString newEtat = ui->etat->currentText();
            QDate newDate = ui->date->date();

            // Create a Dechets object with the new values
            Dechets newDechets(newNom, newType, newPoids, newVolume, newEtat, newDestinataire, newMatiere, newDate);

            // Call the modifier function with the selected "id" and the new Dechets object
            bool modificationSuccessful = d.modifier(id, newDechets);

            if (modificationSuccessful)
            {
                // Refresh the table view
                ui->Afficher->setModel(d.afficher());

                QMessageBox::information(nullptr, QObject::tr("Modification réussie"), QObject::tr("Modification effectuée avec succès.\nCliquez sur OK pour quitter."), QMessageBox::Ok);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Erreur de modification"), QObject::tr("La modification n'a pas été effectuée.\nCliquez sur OK pour quitter."), QMessageBox::Ok);
            }
        }
        else
        {
            QMessageBox::warning(nullptr, QObject::tr("Avertissement"), QObject::tr("Aucun élément sélectionné.\nSélectionnez un élément à modifier."), QMessageBox::Ok);
        }
statistique_chart();



    /*
    QString nom =ui->nom->text();
    //type est un combobox donc currentText donne la valeur choisie
    QString type =ui->type->currentText();
    float poids =ui->poids->text().toFloat();
    float volume=ui->volume->text().toFloat();
    QString matiere =ui->matiere->currentText();
    QString destinataire =ui->destintaire->text();
    QString etat =ui->etat->currentText();
    QDate Date =ui->date->date();

    /// reste des attrubuts
    Dechets d (nom,type,poids,volume,etat,destinataire,matiere,Date);
    bool test = d.modifier() ;
    if (test)
    {
        ui->Afficher->setModel(d.modifier());


        QMessageBox::information(nullptr, QObject::tr("modification effuctué"),  QObject::tr("connection successful.\n" "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else

                QMessageBox::critical(nullptr, QObject::tr("modification n'est pas effuctué"),QObject::tr("connection failed.\n"  "Click Cancel to exit."), QMessageBox::Cancel);
*/}

void MainWindow::on_comboBox_activated(const QString &arg1) // tri -> type (.......)
{
    if (arg1 == "type")
        ui->Afficher->setModel(d.trier (1));
    if (arg1 == "nom du dechet ")
        ui->Afficher->setModel(d.trier (2));
    if (arg1 == "volume")
        ui->Afficher->setModel(d.trier (3));

}

void MainWindow::on_pushButton_clicked() // bouton  rechercher
{
    int id = ui->recherche->text().toInt(); //
    QString id_s = QString::number (id);    //
    if (id!=0)
        ui->Afficher->setModel(d.recherche(id_s)); // setmodel : traki7 tableau
    else
        ui->Afficher->setModel(d.afficher()); // ki n7eb nraj3 tableau dechets au niveau 0
}






void MainWindow::on_PDF_clicked()
{
    QPdfWriter pdf("C:/Users/Administrateur/Downloads/Fichier pdf.pdf");  // ////
           QPainter painter(&pdf);

               int i = 4000;
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Arial", 30));
                   painter.drawText(1100,1200,"List des Dechets");
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Arial", 15));

                   painter.drawRect(100,100,9200,2600);//drawRect (x1, y1, w, h
                   painter.drawRect(0,3000,9600,500);// mta3 titre
                   painter.setFont(QFont("Arial", 9));

                   painter.drawText(200,3300,"ID");
                   painter.drawText(1300,3300,"NOM");
                   painter.drawText(2100,3300,"TYPE");
                   painter.drawText(3200,3300,"POIDS");
                   painter.drawText(4500,3300,"VOLUME");
                   painter.drawText(5400,3300,"MATIERE");
                   painter.drawText(6400,3300,"DESTINATAIRE");
                   painter.drawText(8400,3300,"ETAT");
                   QSqlQuery query;
                   query.prepare("select * from Dechets");

                   query.exec();
                   while (query.next())
                   {
                       painter.drawText(200,i,query.value(0).toString());
                       painter.drawText(1300,i,query.value(1).toString());
                       painter.drawText(2200,i,query.value(2).toString());
                       painter.drawText(3200,i,query.value(3).toString());
                       painter.drawText(4500,i,query.value(4).toString());
                       painter.drawText(5400,i,query.value(5).toString());
                       painter.drawText(6400,i,query.value(6).toString());
                       painter.drawText(7400,i,query.value(7).toString());
                     i = i + 500;
                   }
                    painter.drawRect(0,3000,9600,i-3000);
                   int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                       if (reponse == QMessageBox::Yes)
                       {
                       QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Administrateur/Downloads/Fichier pdf.pdf"));
                           painter.end();
                       }
                       if (reponse == QMessageBox::No)
                       {
                            painter.end();
                       }
    }


void MainWindow::on_Afficher_activated(const QModelIndex &index)   // controle de saisie qui tenzel ala dechets yjik les champs mte3ou fel lineedits  ??
{
    QString val=ui->Afficher->model()->data(index).toString();   // val : nazla
        QSqlQuery qry;

        qry.prepare("select * from Dechets where id='"+val+" ' ");
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->nom->setText(qry.value(1).toString());   //qry.value(1).toString()
                ui->type->setCurrentText(qry.value(2).toString());
                ui->poids->setText(qry.value(3).toString());
                ui->volume->setText(qry.value(4).toString());
                ui->matiere->setCurrentText(qry.value(5).toString());
                ui->date->setDateTime(qry.value(6).toDateTime());
                ui->etat->setCurrentText(qry.value(7).toString());
                ui->destintaire->setText(qry.value(8).toString());



}
}
        else
            {
                QMessageBox::critical(nullptr, QObject::tr("selection n'est pas effuctué"),  QObject::tr("connection failed.\n" "Click Cancel to exit."), QMessageBox::Cancel);
            }
}





void MainWindow::mailSentt(QString status)  // email envoyé
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void MainWindow :: sendMaill()    // envoyer email
{
    QString mail = "mouradhriz0@gmail.com"; // ena bech nebathlou

    QString t="ktiba bla bla";
    Smtp* smtp = new Smtp("mourad.hriz@esprit.tn", "221JMT3943", "smtp.gmail.com", 465); // smtp : ptocole mail  ??
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString))); // appel mailsent elli bech yetebth fih lel mouradhriz0@gamil.com
    smtp->sendMail(mail, mail,"objet",t); // fonction pour envoyer email
}

/*void MainWindow::sendMaill()
{
    QString senderEmail = "";
    QString password = "";
    QString recipientEmail = "";
    QString subject = "objet";
    QString body = "ktiba bla bla";

    Smtp* smtp = new Smtp(senderEmail, password, "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail(senderEmail, recipientEmail, subject, body);
}
*/

void MainWindow::on_pushButton_4_clicked()
{
    sendMaill();
}

void MainWindow::on_nomdechet_activated(const QString &arg1) // nom dechet elli bech yakhtaro client f west combobox f tab 2 et poids aussi
{
    QString n = ui->nomdechet->currentText();
    QSqlQuery query;
    query.prepare("select  nom from dechets");  //  f tableau dechets bech ylawej ala nom kima nom elli dakhlo client
                   query.exec();
                   while (query.next()) // ken nom f dechet = nom elli dakhlo client

    ui->nomdechet->addItem(query.value(0).toString()); // client enfin dakhel nom dechet elli fel combobox
    query.prepare("select  poids from dechets WHERE nom ='"+n+"' "); // bech ythabet fama poids wela
                   query.exec();
                   while (query.next()){
                   int  a = query.value(0).toInt();  // a : valeur poids elli fel tableu dechets

       ui->poids_2->setValidator(new QIntValidator(0,a));} //  new setValidator : valeur entre 0 et a : poids mtaa client
                   // setValidator : client ki bech ydakhel poids lezem ykoun betwwen 0 and a : valeur poids elli fel tableau dechets
}

void MainWindow::on_vendre_clicked()
{
    QString poids = ui->poids_2->text(); // client dakhel poids
    QString n = ui->nomdechet->currentText(); // client dakhel nom mtaa dechet
    QSqlQuery query;
    query.prepare("UPDATE dechets SET poids = poids - :poids WHERE nom ='"+n+"' ");// nom : elli  dakhlo client elli al imin fe west tab2  et lekher nom heka elli fe west tabelau dechets al isar
    query.bindValue(":poids", poids.toUInt());

     // baad difference mabinet les deux poids  ki nenzel ala bouton vendre yetefecha dechets elli khtaro client baad masaret alih modification

    query.exec();
    while (query.next());
    query.prepare("select * from Dechets where nom='"+n+"' "); //baad masaret modf entre les poids bech nemchi nchouf el dechet
    QString nom , type ="llllll" , matiere ;
    QDateTime date;
    if(query.exec())
    {
        while(query.next())
        {
            nom=(query.value(1).toString());   //qry.value(1).toString() // bech tsir recuperation mtaa dechets hetha w bech yeta7at f tableau histoooooooo
            type=(query.value(2).toString());
             poids=(query.value(3).toString());
             matiere=(query.value(5).toString());
             date=(query.value(6).toDateTime());




}

}
    query.prepare("insert into Historique (NOM,DATEARRIVE,DATEVENDUE,TYPE,POIDS,MATIERE)""values(:nom,:datearrive,sysdate,:type,:poids,:matiere)");
    query.bindValue(":nom",n); // bindValue : relier les variables (attributs ) ajoutés a les attributs principales dans tableau déchets elli houwa f BD
    query.bindValue(":datearrive",date);
    query.bindValue(":matiere",matiere);

    query.bindValue(":type",type);
    query.bindValue(":poids",poids);
    query.exec();
    while (query.next());
    ui->tablehistorique->setModel(d.afficher_historique());

}

void MainWindow::on_pb_ajouter_clicked()
{
    QString id_c = ui->id_2->text();
    QString empp = ui->emp_2->text();
    QString quantit = ui->qan_2->text();
    QString qua = ui->qual_2->text();
    QDate date_po = ui->le_date->date();


    if(id_c.length()==0)
    {
        QMessageBox msgbox(QMessageBox::Warning,"invalid","ID_C doit etre remplie par une chaine de caractere valid");
        msgbox.exec();
        ui->id_2->setFocus();
    }
    if(empp.length()==0)
    {
        QMessageBox msgbox(QMessageBox::Warning,"invalid","emplacement doit etre remplie par une chaine de caractere valid");
        msgbox.exec();
        ui->emp_2->setFocus();
    }
    if(quantit.length()==0)
    {
        QMessageBox msgbox(QMessageBox::Warning,"invalid","quantite doit etre remplie par une chaine de caractere valid");
        msgbox.exec();
        ui->qan_2->setFocus();
    }


    collect c(id_c,empp,quantit,qua,date_po);
    bool test=c.ajouter();

     if (test==true)
    {
             ui->t_c->setModel(Etmp.afficher());

    QMessageBox msgBox;
        QMessageBox::information(nullptr, QObject::tr("success!"),
                                             QObject::tr(""
                                                         "collecte Ajouter."), QMessageBox::Ok);

                   }
                   else
                  {
                       QMessageBox::critical(nullptr, QObject::tr("Error !!"),
                                             QObject::tr(""
                                                         "Probleme d'Ajout."), QMessageBox::Cancel);

                   }
     on_pushButton_STAT_clicked();
}



void MainWindow::on_le_id_c_supp_clicked()
{
    QModelIndex index=ui->t_c->currentIndex();
        int i=index.row();
        QModelIndex in=index.sibling(i,0);
        QString val=ui->t_c->model()->data(in).toString();
        collect c;
        bool test=c.supprimer(val);
        if (test)
        {

            ui->t_c->setModel(Etmp.afficher());

        }
        on_pushButton_STAT_clicked();

}





void MainWindow::on_pushButton_update_clicked()
{
    QModelIndex index = ui->t_c->currentIndex(); // Récupérer l'index de la ligne sélectionnée dans le TableView

    if (!index.isValid()) {
        QMessageBox::warning(this, "Erreur", "Aucune ligne sélectionnée.");
        return;
    }

    int row = index.row();
    const int COLONNE_ID = 0;
    QModelIndex idIndex = ui->t_c->model()->index(row, COLONNE_ID);
    QVariant idData = ui->t_c->model()->data(idIndex);
    int idToUpdate = idData.toInt(); // Assurez-vous que COLONNE_ID est correctement défini

    // Récupérer les valeurs des champs de saisie
    QDate date_po = ui->le_date->date();
    QString empp = ui->emp_2->text();
    QString quantit = ui->qan_2->text();
    QString qua = ui->qual_2->text();
    QString id_c = ui->id_2->text();

    QSqlQuery qry;

    qry.prepare("UPDATE COLLECTE SET EMPLACEMENT = :EMPLACEMENT, QUANTITE = :QUANTITE, QUALITE = :QUALITE, DATE_DE_COLLECTE = :DATE_DE_COLLECTE WHERE ID_COL = :ID_COL");
    qry.bindValue(":ID_COL",id_c);
    qry.bindValue(":EMPLACEMENT", empp);
    qry.bindValue(":QUANTITE", quantit);
    qry.bindValue(":QUALITE",qua);
    qry.bindValue(":DATE_DE_COLLECTE",date_po);
    qry.bindValue(":id_c", idToUpdate);

    if (qry.exec()) {
        // Rafraîchir le modèle pour refléter les modifications
        ui->t_c->setModel(Etmp.afficher());

        qDebug() << "Collecte modifiée avec succès.";
        QMessageBox::information(this, "Succès", "Collecte modifiée avec succès.");


        // Vous n'avez probablement pas besoin de supprimer la ligne de la vue ici
        // ui->t_c->model()->removeRow(row);

        // Effacer les champs après la modification
        ui->id_2->clear();
        ui->emp_2->clear();
        ui->qan_2->clear();
        ui->qual_2->clear();
        ui->le_date->setDate(QDate::currentDate()); // Réinitialiser la date à la date actuelle ou à une valeur par défaut
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de la collecte.");
    }
    on_pushButton_STAT_clicked();

}








void MainWindow::on_pushButton_trier_clicked()
{
    QSqlQueryModel *model =new QSqlQueryModel;
        model->setQuery("SELECT * FROM COLLECTE ORDER BY ID_COL");


                // Refresh the view

            ui->t_c->setModel(model);

}



void MainWindow::on_pushButton_exporter_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Exporter le tableau au format PDF", "", "Fichiers PDF (*.pdf)");//permet de sélectionner des fichiers ou des répertoires
//filepath:stock le chemain de fichier
    //getSaveFileName:choisir un emplacement et un nom ll fichier
          if (filePath.isEmpty())
          {
              return;
          }

          QPrinter printer(QPrinter::PrinterResolution); //QPrinter besh l qt yaaref eli enty une imprimente virtuelle
          printer.setOutputFormat(QPrinter::PdfFormat); //besh yaaref eli l format fl sortie type taa3ou PDF
          printer.setOutputFileName(filePath);//besh yaaref chemain
          printer.setPageSize(QPrinter::Tabloid);//thaded taille taa l page


          QPainter painter(&printer);//ay haj amarssouma besh natb3ouha bl machine virtuelle
          painter.setRenderHint(QPainter::Antialiasing);//tech graphidue besh l bord ywaliw plus lisse
          painter.setRenderHint(QPainter::TextAntialiasing);//les contours de caractere plus lisses
          painter.setRenderHint(QPainter::HighQualityAntialiasing);//ll qualite
          painter.setRenderHint(QPainter::SmoothPixmapTransform);//améliore la qualité du rendu des images ki ne9elbouha wela ay faaza


          QAbstractItemModel* originalModel = ui->t_c->model();//recuperer un pointeur vers la table ppour acceder au donnes actuelle de la table
          QString originalStylesheet = ui->t_c->styleSheet();//recuperer une feuille sur qt
          QSize originalSize = ui->t_c->size();//TAILLE DE LA TABLE X,Y taille bidemonsionnelle

          QStandardItemModel model;

          model.setHorizontalHeaderLabels({"ID_COL", "EMPLACEMENT", "QUANTIE", "QUALITE", "DATE_DE_COLLECTE"});

          int rowCount = originalModel->rowCount();//pour obtenir le nombre de ligne
          int columnCount = originalModel->columnCount();//nombre de colonnes
          for (int row = 0; row < rowCount; ++row)
          {
              QList<QStandardItem*> rowData;//l kol ligne nakhel9ou rowdata nesstokio fih les donnes taa ligne
              for (int col = 0; col < columnCount-1; ++col)
              {
                  QStandardItem* item = new QStandardItem(originalModel->data(originalModel->index(row, col)).toString());//nesstokiw led donner eli fi col row yaani mither (2.3) w nrodouhom des chaines de caractere
                  rowData.append(item);
              }
              model.appendRow(rowData);
          }

          ui->t_c->setModel(&model);//laffichage de noubelle model

          ui->t_c->resize(printer.width(), printer.height());//besh nhafedh aal led dimensions

          ui->t_c->render(&painter);//besh nhawlou mn tabel l pdf

          ui->t_c->setModel(originalModel);// baaed l imrimentatioon nraj3ou l table
          ui->t_c->setStyleSheet(originalStylesheet);// revenir à l'apparence visuelle initiale de la table.
          ui->t_c->resize(originalSize);//dimensions d'origine après le processus d'impression.


          painter.end();
}




void MainWindow::print(QPrinter *printer)
{

    QPainter painter(printer);
       painter.setRenderHint(QPainter::Antialiasing);
       painter.setRenderHint(QPainter::TextAntialiasing);
       painter.setRenderHint(QPainter::HighQualityAntialiasing);
       painter.setRenderHint(QPainter::SmoothPixmapTransform);

       QAbstractItemModel* originalModel = ui->t_c->model();
       QString originalStylesheet = ui->t_c->styleSheet();
       QSize originalSize = ui->t_c->size();

       QStandardItemModel model;

       model.setHorizontalHeaderLabels({"ID_COL", "EMPLACEMENT", "QUANTITE", "QUALITE", "DATE_DE_COLLECTE"});

       int rowCount = originalModel->rowCount();
       int columnCount = originalModel->columnCount();
       for (int row = 0; row < rowCount; ++row)
       {
           QList<QStandardItem*> rowData;
           for (int col = 0; col < columnCount-1; ++col)
           {
               QStandardItem* item = new QStandardItem(originalModel->data(originalModel->index(row, col)).toString());
               rowData.append(item);
           }
           model.appendRow(rowData);
       }

       ui->t_c->setModel(&model);
       ui->t_c->resize(printer->width(), printer->height());
       ui->t_c->render(&painter);

       ui->t_c->setModel(originalModel);
       ui->t_c->setStyleSheet(originalStylesheet);
       ui->t_c->resize(originalSize);
}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    bool ok;
      QString note = QInputDialog::getText(this, "Ajouter une note", "Entrez une note :", QLineEdit::Normal, "", &ok);

      // Si l'utilisateur clique sur "OK", afficher un message avec la note
      if (ok && !note.isEmpty())
      {
          QString message = QString("Note ajoutée le %1 : %2").arg(date.toString("dd/MM/yyyy")).arg(note);
          QMessageBox::information(this, "Note ajoutée", message);

          // Stocker la note dans la liste des notes
          NoteEntry entry;
          entry.date = date;
          entry.note = note;
          notes.append(entry);

          // Rafraîchir les info-bulles pour prendre en compte la nouvelle note
          on_calendarWidget_selectionChanged();
      }
    }


void MainWindow::on_calendarWidget_selectionChanged()
{        // Reuse the existing model or create a new one if needed
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView_note->model());
    if (!model) {
        model = new QStandardItemModel(this);
        model->setHorizontalHeaderLabels(QStringList() << "Date" << "Note");
    } else {
        // Clear the existing table if the model is being reused
    }

    // La date sélectionnée dans le calendrier
    QDate selectedDate = ui->calendarWidget->selectedDate();

    // Liste pour stocker toutes les notes associées à la date sélectionnée
    QList<NoteEntry> selectedNotes;

    // Remplir la liste des notes associées à la date sélectionnée
    foreach (const NoteEntry &entry, notes) {
        if (selectedDate == entry.date) {
            selectedNotes.append(entry);
        }
    }

    // Ajouter les notes à la table
    foreach (const NoteEntry &entry, selectedNotes) {
        QList<QStandardItem *> rowItems;
        rowItems.append(new QStandardItem(entry.date.toString("dd/MM/yyyy")));
        rowItems.append(new QStandardItem(entry.note));
        model->appendRow(rowItems);
    }

    // Définir le modèle pour le tableau
    ui->tableView_note->setModel(model);

    // Effacer l'info-bulle
    ui->calendarWidget->setToolTip("");


}


void MainWindow::on_pushButton_enregistrer_clicked()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView_note->model());

       // Check if the model exists
       if (!model) {
           qDebug() << "No model available for export.";
           return;
       }

       // Ask the user to choose a file path
       QString filePath = QFileDialog::getSaveFileName(this, tr("Export Table to TXT"), "", tr("Text Files (*.txt);;All Files (*)"));
       if (filePath.isEmpty()) {
           qDebug() << "Export canceled or no file selected.";
           return;
       }

       // Open the file for writing
       QFile file(filePath);
       if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
           QTextStream out(&file);

           // Write headers to the file
           QStringList headers;
           headers << "#" << "Date" << "***"<<"Note";  // Added a column for row numbers
           out << headers.join('\t') << '\n';

           // Write data to the file
           for (int row = 0; row < model->rowCount(); ++row) {
               QStringList rowData;

               // Add row number
               rowData << QString::number(row + 1);

               for (int column = 0; column < model->columnCount(); ++column) {
                   // Get the data for each cell
                   QString data = model->item(row, column)->text();
                   rowData << data;
               }
               out << rowData.join('\t') << '\n';
           }

           // Close the file
           file.close();
           qDebug() << "Export successful. File saved at:" << filePath;
       } else {
           qDebug() << "Failed to open the file for export:" << file.errorString();
       }
}



int MainWindow::calculerNombreCollecteJanvier(int mois)
{
    QSqlQuery query;

        if (mois < 1 || mois > 12) {
            qDebug() << "Mois invalide. Le mois doit être compris entre 1 et 12.";
            return -1;  // Valeur d'erreur
        }

        query.prepare("SELECT COUNT(*) AS count FROM COLLECTE WHERE EXTRACT(MONTH FROM DATE_DE_COLLECTE) = :mois");
        query.bindValue(":mois", mois);

        if (query.exec() && query.next()) {
            int nombreCertificats = query.value("count").toInt();
            return nombreCertificats;
        } else {
            qDebug() << "Erreur lors du calcul du nombre de COLLECTE pour le mois " << mois;
            return -1;  // Valeur d'erreur
        }
}
void MainWindow::on_pushButton_STAT_clicked()
{
    MainWindow p;
    // Créer le graphique à barres
    QBarSet *set0 = new QBarSet("");
    QBarSet *set1 = new QBarSet("Nombre de collecte");

    // Ajoutez le nombre de collecte en janvier aux QBarSet
    *set0 << 0;
    *set1 << p.calculerNombreCollecteJanvier(1) << p.calculerNombreCollecteJanvier(2) << p.calculerNombreCollecteJanvier(3) << p.calculerNombreCollecteJanvier(4)
         << p.calculerNombreCollecteJanvier(5) << p.calculerNombreCollecteJanvier(6) << p.calculerNombreCollecteJanvier(7) << p.calculerNombreCollecteJanvier(8)
         << p.calculerNombreCollecteJanvier(9) << p.calculerNombreCollecteJanvier(10) << p.calculerNombreCollecteJanvier(11) << p.calculerNombreCollecteJanvier(12);

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("LE NOMBRE DE collecte SELON MOIS");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "JANVIER" << "FEVRIER" << "MARS" << "AVRIL" << "MAI" << "JUIN" << "JUILLET" << "AOUT" << "SEPTEMBRE" << "OCTOBRE" << "NOVEMBRE" << "DECEMBRE";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    // Créer une scène graphique
    QGraphicsScene *scene = new QGraphicsScene(this);

    QChartView *chartView = new QChartView(chart);
    chartView->setMinimumSize(371, 181);

    scene->addWidget(chartView);

    // Définir la scène de QGraphicsView
    ui->graphicsView->setScene(scene);
    // Afficher la fenêtre
    ui->graphicsView->show();
    int totalCollecte = 0;
    for (int mois = 1; mois <= 12; ++mois) {
        totalCollecte += p.calculerNombreCollecteJanvier(mois);
    }

    // Créez un modèle de tableau standard
    QStandardItemModel *model = new QStandardItemModel();

    // Ajoutez des en-têtes de colonne
    model->setHorizontalHeaderLabels(QStringList() << "Mois" << "Nombre de collecte" << "Pourcentage");

    // Ajoutez les résultats pour chaque mois
    for (int mois = 1; mois <= 12; ++mois) {
        int resultat = p.calculerNombreCollecteJanvier(mois);

        // Obtenez le nom du mois
        QString nomMois;
        switch (mois) {
        case 1: nomMois = "Janvier"; break;
        case 2: nomMois = "Février"; break;
        case 3: nomMois = "Mars"; break;
        case 4: nomMois = "Avril"; break;
        case 5: nomMois = "Mai"; break;
        case 6: nomMois = "Juin"; break;
        case 7: nomMois = "Juillet"; break;
        case 8: nomMois = "Août"; break;
        case 9: nomMois = "Septembre"; break;
        case 10: nomMois = "Octobre"; break;
        case 11: nomMois = "Novembre"; break;
        case 12: nomMois = "Décembre"; break;
        default: nomMois = "Inconnu"; break;
        }

        // Calculez le pourcentage par rapport au total
        double pourcentage = 0.0;
        if (totalCollecte > 0) {
            pourcentage = static_cast<double>(resultat) / totalCollecte * 100.0;
        }

        // Ajoutez une nouvelle ligne au modèle avec le mois, le résultat et le pourcentage
        QList<QStandardItem *> items;
        items << new QStandardItem(nomMois);
        items << new QStandardItem(QString::number(resultat));
        items << new QStandardItem(QString("%1%").arg(QString::number(pourcentage, 'f', 2)));
        model->appendRow(items);
    }
    ui->tableView_Resultat->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView_Resultat->setModel(model);

}




void MainWindow::on_pb_ajouter_2_clicked()
{
    int id_v=ui->le_id_v->text().toInt();
    QString date_=ui->le_date_->text();
    int qua=ui->le_qua->text().toInt();
    QString type=ui->le_type->currentText();
    int prix=ui->le_prix->text().toInt();
    int montant=ui->le_montant->text().toInt();


    vente v(id_v,date_,qua,type,prix,montant);


    //testi kol w7da esque hya far8a w la

    bool test=v.ajouter();
    QMessageBox msgBox;
     if (test==true)
    {
        ui->tab_vente->setModel(v.afficher());

        QMessageBox::information(nullptr, QObject::tr("success!"),
                                             QObject::tr(""
                                                         "vente Ajouter."), QMessageBox::Ok);
                   }
                   else
                  {
                       QMessageBox::critical(nullptr, QObject::tr("Error !!"),
                                             QObject::tr(""
                                                         "Probleme d'Ajout."), QMessageBox::Cancel);

                   }
     stat();

}





void MainWindow::on_pb_supprimer_clicked()
{
  vente v1; v1.setid_v(ui->le_id_v->text().toInt());
  bool test=v1.supprimer(v1.getid_v());
     QMessageBox msgBox;

     if(test)
        { msgBox.setText("supp avec succes");
         ui->tab_vente->setModel(v.afficher());
        }
     else
         msgBox.setText("Echec de supp");
         msgBox.exec();
         stat();

}






void MainWindow::on_pb_modifier_clicked()
{
    int id_v=ui->le_id_v->text().toInt();
    QString date_=ui->le_date_->text();
    int qua=ui->le_qua->text().toInt();
    QString type=ui->le_type->currentText();
    int prix=ui->le_prix->text().toInt();
    int montant=ui->le_montant->text().toInt();


    vente v(id_v,date_,qua,type,prix,montant);
    bool test=v.modifier(v.getid_v(),v.getdate_(),v.getqua(),v.gettype(),v.getprix(),v.getmontant());
    if (test)
    {
        ui->tab_vente->setModel(v.afficher());
    QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("modifier avec succes.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui->le_id_v->clear();



     }
    else
    QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                QObject::tr("modifier non effectue.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    stat();

}








void MainWindow::on_pb_trier_clicked()
{
    QString critere;

    if (ui->croisssant_->isChecked())
        critere = "ASC";
    else if (ui->decroissant_->isChecked())
        critere = "DESC";
    else
    {
        qDebug() << "Please select a sorting order.";
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);

    QString query = "SELECT * FROM VENTE_DE_DECHETS ORDER BY ID_V " + critere;

    // Execute
    model->setQuery(query);

    // Add translations for each column header
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_V"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MONTANT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_COL"));

    // Configure
    ui->tab_vente->setModel(model);

    }


void MainWindow::on_pb_pdf_clicked()
{QString filePath = QFileDialog::getSaveFileName(this, tr("Save PDF File"), QDir::homePath(), tr("PDF Files (*.pdf)"));

        QFile file(filePath);
                if (!file.open(QIODevice::WriteOnly))
                {
                    QMessageBox::warning(this, "Error", "Could not create file!");
                    return;
                }

                QPdfWriter pdfWriter(&file);
                pdfWriter.setPageSize(QPagedPaintDevice::A4);
                pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30));

                QPainter painter(&pdfWriter);
                int i = 4000;
                painter.setPen(Qt::red); // change the color of the title to red
                painter.setFont(QFont("Time New Roman", 25));
                painter.drawText(2000,1000,"Gestion de vente");
                painter.setPen(Qt::black);
                painter.setFont(QFont("Time New Roman", 15));
                painter.drawRect(50,100,9000,13000);
                painter.drawRect(100,3000,8800,500);
                painter.setFont(QFont("Time New Roman", 9));
                painter.drawText(400,3300,"ID_V");
                painter.drawText(1000,3300,"DATE_");
                painter.drawText(2200,3300,"QUANTITE");
                painter.drawText(3400,3300,"TYPE");
                painter.drawText(5900,3300,"PRIX");
                painter.drawText(8100,3300,"MONTANT");
                painter.drawText(8100,3300,"ID_COL");

                // increase the vertical space between each line by 500
                i = 4500;

                painter.drawRect(100,3000,8800,8000);

                QSqlQuery query;
                query.prepare("select * from VENTE_DE_DECHETS");
                query.exec();
                while (query.next())
                {
                    painter.drawText(400,i,query.value(0).toString());
                    painter.drawText(1000,i,query.value(1).toString());
                    painter.drawText(2300,i,query.value(2).toString());
                    painter.drawText(3400,i,query.value(3).toString());
                    painter.drawText(5900,i,query.value(4).toString());
                    painter.drawText(8100,i,query.value(5).toString());

                    i = i + 500; // increase the vertical space between each line by 500
                }

                QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                            QObject::tr("PDF Enregistré!.\n"), QMessageBox::Ok);



}



void MainWindow::stat()
{
    int mauvaisCount = 0;
    int bonCount = 0;
    int moyenCount = 0;

    QSqlQuery query;

    query.prepare("SELECT * FROM VENTE_DE_DECHETS WHERE TYPE = 'mauvais'");
    query.exec();

    while (query.next())
        mauvaisCount++;

    query.prepare("SELECT * FROM VENTE_DE_DECHETS WHERE TYPE = 'bon'");
    query.exec();

    while (query.next())
        bonCount++;

    query.prepare("SELECT * FROM VENTE_DE_DECHETS WHERE TYPE = 'moyen'");
    query.exec();

    while (query.next())
        moyenCount++;

    qDebug() << "Mauvais Count:" << mauvaisCount << ", Bon Count:" << bonCount << ", Moyen Count:" << moyenCount;

    // Create a pie series
    QPieSeries *series = new QPieSeries();
    series->append("Mauvais", mauvaisCount);
    series->append("Bon", bonCount);
    series->append("Moyen", moyenCount);

    // Customize pie slices
    series->slices().at(0)->setColor("#f37b78");
    series->slices().at(1)->setColor("#663333");
    series->slices().at(2)->setColor("#cccccc");

    // Create a chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique du VENTE");

    series->setLabelsVisible();

    // Create a chart view
    chartView = new QChartView(chart,ui->chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(801,351);

    chartView->show();
}


/*void MainWindow::on_pb_excel_clicked()
{
    QString invoiceId = ui->lineEdit_rech->text();

        // Call the function to generate the Excel file
        vente.generateInvoiceExcel(invoiceId);
}*/



void MainWindow::on_pb_excel_clicked()
{
    // Assuming ui->tab_emp is a QTableView in your UI file

        // Set the model for the QTableView

        QString filters("CSV files (*.csv);;All files (*)");
        QString defaultFilter("CSV files (*.csv)");
        QString fileName = QFileDialog::getSaveFileName(this, "Save file", QCoreApplication::applicationDirPath(),
                                    filters, &defaultFilter);
        QFile file(fileName);

        QAbstractItemModel *model = ui->tab_vente->model(); // Use ui->tab_emp here

        if (file.open(QFile::WriteOnly | QFile::Truncate)) {
            QTextStream data(&file);
            QStringList strList;

            // Write headers
            for (int i = 0; i < model->columnCount(); i++) {
                if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                    strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") << "\n";

            // Write data
            for (int i = 0; i < model->rowCount(); i++) {
                strList.clear();
                for (int j = 0; j < model->columnCount(); j++) {
                    if (model->data(model->index(i, j)).toString().length() > 0)
                        strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                    else
                        strList.append("");
                }
                data << strList.join(";") + "\n";
            }

            file.close();
            QMessageBox::information(this, "Exporter To Excel", "Exporter En Excel Avec Succès");
        }
        else {
            QMessageBox::warning(this, "Error", "Unable to open the file for writing");
        }

}








void MainWindow::on_lineEdit_rech_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString text=ui->lineEdit_rech->text();
    if(text.isEmpty())
    {
         vente v;
        v.afficher();

    }
    else
    {
        modal = v.rechercherParId(ui->lineEdit_rech->text().toInt());
        ui->tab_vente->setModel(modal);
    }
}

void MainWindow::on_tab_vente_clicked(const QModelIndex &index)
{
    int i;
i=index.row();
QModelIndex in=index.sibling(i,0);
QString val=ui->tab_vente->model()->data(in).toString();


    QSqlQuery qry;
    qry.prepare("select * from VENTE_DE_DECHETS where id_v='"+val+"' " );


    if(qry.exec())
    {
        while(qry.next())
        {


            ui->le_id_v->setText(qry.value(0).toString());
            ui->le_prix->setText(qry.value(4).toString());
            ui->le_montant->setText(qry.value(5).toString());


            ui->le_date_->setDate(qry.value(1).toDate());
            ui->le_qua->setText(qry.value(2).toString());
            ui->le_type->setCurrentText(qry.value(3).toString());


        }
}
}

void MainWindow::on_lineEdit_idcol_rechercher_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString text=ui->lineEdit_idcol_rechercher->text();

    if(text.isEmpty())
    {
         collect c;
         ui->t_c->setModel(Etmp.afficher());

    }
    else
    {
        qry->prepare("select * from collecte where ( ID_COL LIKE'%"+text+"%' OR EMPLACEMENT LIKE'%"+text+"%' OR QUANTITE LIKE'%"+text+"%') ");
        qry->exec();
        modal->setQuery(*qry);
        ui->t_c->setModel(modal);
    }
}

void MainWindow::on_t_c_clicked(const QModelIndex &index)
{
    int i;
i=index.row();
QModelIndex in=index.sibling(i,0);
QString val=ui->t_c->model()->data(in).toString();


    QSqlQuery qry;
    qry.prepare("select * from collecte where ID_COL='"+val+"' " );


    if(qry.exec())
    {
        while(qry.next())
        {


            ui->id_2->setText(qry.value(0).toString());
            ui->le_date->setDate(qry.value(4).toDate());
            ui->le_montant->setText(qry.value(5).toString());
            //ui->le_id_col->setText(qry.value(6).toString());

            ui->emp_2->setText(qry.value(1).toString());
            ui->qan_2->setText(qry.value(2).toString());
            ui->qual_2->setText(qry.value(3).toString());


        }
}
}


void MainWindow::on_recherche_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString text=ui->recherche->text();

    if(text.isEmpty())
    {
         Dechets d;
        d.afficher();

    }
    else
    {
        qry->prepare("select * from dechets where ( id LIKE'%"+text+"%' OR nom LIKE'%"+text+"%' OR type LIKE'%"+text+"%') ");
        qry->exec();
        modal->setQuery(*qry);
        ui->Afficher->setModel(modal);
    }
}
void MainWindow::statistique_chart()
{

    QSqlQuery query0,query1,query2,query3,query4,query5,query6,query8,query7;

    qreal c1_1=0,c1_2=0,c1_3=0,c1_4=0
                ,c2_1=0 ,c2_2=0;

    int totale=0;

        query0.prepare("SELECT * FROM DECHETS");
        query0.exec();

        //Les classes de type violation
        query1.prepare("SELECT * FROM DECHETS WHERE type='plastique' ");
        query1.exec();

        query2.prepare("SELECT * FROM DECHETS WHERE type='verre' ");
        query2.exec();

        query3.prepare("SELECT * FROM DECHETS WHERE poids > 30 ");
        query3.exec();

        query4.prepare("SELECT * FROM DECHETS WHERE poids < 30 ");
        query4.exec();






        while (query0.next()){totale++;}
        //total des classes par rapport au type violation
        while (query1.next()){c1_1++;}
        while (query2.next()){c1_2++;}
        while (query3.next()){c1_3++;}
        while (query4.next()){c1_4++;}
        while (query5.next()){c2_1++;}
        while (query6.next()){c2_2++;}


        totale=totale/2;


        // Assign names to the set of bars used
                QBarSet *set0 = new QBarSet(" type:plastique");
                QBarSet *set1 = new QBarSet("type:verre");
                QBarSet *set2 = new QBarSet("poids:>15");
                QBarSet *set3 = new QBarSet("poids:<15 ");

                // Assign values for each bar
                *set0 << c1_3;
                *set1 << c1_4;
                 *set2<< c2_1;
                 *set3<< c2_2;

                // Add all sets of data to the chart as a whole
                // 1. Bar Chart
                QBarSeries *series = new QBarSeries();

                // 2. Stacked bar chart
                series->append(set0);
                series->append(set1);
                series->append(set2);
                series->append(set3);

                // Used to define the bar chart to display, title
                // legend,
                QChart *chart = new QChart();

                // Add the chart
                chart->addSeries(series);
                chart->setTitle("statistique Dechets");
                chart->setAnimationOptions(QChart::SeriesAnimations);
                chart->setTheme( QChart::ChartThemeBlueCerulean);

                QStringList type;
                    type << "plastique" << "verre"  ;
                // Adds categories to the axes
                    QBarCategoryAxis *axisX = new QBarCategoryAxis();
                        axisX->append(type);
                        chart->addAxis(axisX, Qt::AlignBottom);
                        series->attachAxis(axisX);

                        QValueAxis *axisY = new QValueAxis();
                        axisY->setRange(0,totale);
                        chart->addAxis(axisY, Qt::AlignLeft);
                        series->attachAxis(axisY);


                // 1. Bar chart
               // chart->setAxisX(axis, series);

                // Used to change the palette
                QPalette pal = qApp->palette();

                // Change the color around the chart widget and text
                pal.setColor(QPalette::Window, QRgb(0xffffff));
                pal.setColor(QPalette::WindowText, QRgb(0x404044));

                // Apply palette changes to the application
                qApp->setPalette(pal);
                chartView = new QChartView(chart,ui->Stat);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->setMinimumSize(441,301);

                chartView->show();
}

void MainWindow::on_pushButton_statistique_2_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    QString id_collecte = ui->id_3->text();
    QString nom_client = ui->emp_4->text();
    QString adresse_client = ui->qan_4->text();
    QString cin_client = ui->qual_3->text();
    QString date = ui->le_date_2->date().toString();
    QString emplacement,quantite,qualite,date_collecte;
    QSqlQuery query;
    query.prepare("SELECT * FROM COLLECTE WHERE ID_COL = :id");
    query.bindValue(":id", id_collecte);
    if(query.exec()){
     while(query.next()){
          emplacement = query.value(1).toString();
          quantite = query.value(2).toString();
          qualite = query.value(3).toString();
          date_collecte = query.value(4).toString();}
          out <<  "<html>\n"
              "<head>\n"
              "<meta Content=\"Text/html; charset=Windows-1251\">\n"
              <<  QString("<title>%1</title>\n").arg("col1")
              <<  "</head>\n"
              "<body bgcolor=#ffffff link=#5000A0>\n"
              "<h3 style='position: absolute; top: 0; right: 0; margin: 0; padding: 10px; text-align: right; font-size: 24px; color: #333;'> Tunis "+date+"</h3>"
              "<h1 style='text-align: center;'>Contrat</h1>\n"
              "<br>\n"
              "<br>\n"
              "<div align='center'>"
              "<p>ID Collecte : <strong>" + id_collecte + "</strong></p>"
              "<p>Nom du client : <strong>" + nom_client + "</strong></p>"
              "<p>Adresse du client : <strong>" + adresse_client + "</strong></p>"
              "<p>CIN du client : <strong>" + cin_client + "</strong></p>"
              "<p>Date de collecte : <strong>" + date_collecte + "</strong></p>"
              "<p>Emplacement : <strong>" + emplacement + "</strong></p>"
              "<p>Quantite : <strong>" + quantite + "</strong></p>"
              "<p>Qualite : <strong>" + qualite + "</strong></p>"
              "</div>"
              "<br>\n"
              "<br>\n"
              "<p align='left'><strong>Signature du client : </strong></p>"
              "<p align='right'><strong>Signature du responsable : </strong></p>"
              "</body>\n"
              "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

        document->print(&printer);


    delete document;}
    else{
        QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                              QObject::tr("Collecte n'existe pas.\nCliquez sur OK pour continuer"), QMessageBox::Ok);
    }
}

void MainWindow::on_pb_ajouter_3_clicked()
{
    int id=ui->id->text().toInt();
    int niveau=ui->niveau->text().toInt();
    int capacite=ui->capacite->text().toInt();
    conteneur E(id,niveau,capacite);
    bool test=E.ajouter();

            if(test)
            {
                ui->tab_cont-> setModel(E.afficher());
                QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajouter effectue\n"
                                                                               "ok cancel to cancel"),QMessageBox::Ok);}
}

void MainWindow::on_pb_modifier_2_clicked()
{
    int id=ui->id->text().toInt();
    int niveau=ui->niveau->text().toInt();
    int capacite=ui->capacite->text().toInt();
    conteneur E(id,niveau,capacite);
    bool test=E.modifier(id,niveau,capacite);

            if(test)
            {
                ui->tab_cont-> setModel(E.afficher());
                QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("modification effectue\n"
                                                                               "ok cancel to cancel"),QMessageBox::Ok);
            }
}

void MainWindow::on_tab_cont_clicked(const QModelIndex &index)
{
    int i;
i=index.row();
QModelIndex in=index.sibling(i,0);
QString val=ui->t_c->model()->data(in).toString();


    QSqlQuery qry;
    qry.prepare("select * from CONTENEUR where ID='"+val+"' " );

    if(qry.exec())
    {
        while(qry.next())
        {


            ui->id->setText(qry.value(0).toString());


            ui->niveau->setText(qry.value(1).toString());
            ui->capacite->setText(qry.value(2).toString());


        }
}
}

void MainWindow::on_pb_supprimer_2_clicked()
{
    QModelIndex index=ui->tab_cont->currentIndex();
        int i=index.row();
        QModelIndex in=index.sibling(i,0);
        QString val=ui->tab_cont->model()->data(in).toString();
        conteneur c;
        bool test=c.supprimer(val.toInt());
        if (test)
        {
            ui->tab_cont->setModel(c.afficher());

        }

}

void MainWindow::on_pb_pdf_2_clicked()
{
    conteneur E;
    E.pdfprinter();
    QMessageBox::information(nullptr, QObject::tr("database is open"),
                QObject::tr("generation pdf ² est effectue.\n"
                            "Click ok to exit."), QMessageBox::Ok);
}

void MainWindow::on_pushButton_9_clicked()
{
    conteneur E;

            ui->tab_cont->setModel(E.trie_id());
}

void MainWindow::on_lineEdit_rech_2_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString text=ui->lineEdit_rech_2->text();

    if(text.isEmpty())
    {
        conteneur c;
        ui->tab_cont->setModel(c.afficher());


    }
    else
    {
        qry->prepare("select * from CONTENEUR where ( id LIKE'%"+text+"%' OR NIVEAU LIKE'%"+text+"%' OR CAPACITE LIKE'%"+text+"%') ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tab_cont->setModel(modal);
    }
}
