#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dechets.h"
QString test="";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Afficher->setModel(d.afficher()); //constructeur afficahge tableaur
    ui->tablehistorique->setModel(d.afficher_historique());
    QChart *chartdechets = new QChart();
    QRegularExpression rx("^[A-Za-z]+$");
    QSqlQuery query;
    query.prepare("select  nom from dechets");
                   query.exec();
                   while (query.next())

    ui->nomdechet->addItem(query.value(0).toString());

                QValidator *validator = new QRegularExpressionValidator(rx, this);
                ui->nom->setValidator(validator);
    ui->poids->setValidator(new QIntValidator(0,999999999));

             chartdechets=d.statistique_chart();

            QChartView *chartviedechets = new QChartView(chartdechets,ui->Stat);

            chartviedechets->resize(1000,500);

            chartviedechets->setRenderHint(QPainter::Antialiasing);
            int ret=A.connect_arduino(); // lancer la connexion à arduino
            switch(ret){
            case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available";
            }
             QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(input())); // permet de lancer
             //le slot update_label suite à la reception du signal readyRead (reception des données).
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::input(){
    data=A.read_from_arduino();
    test= data;
    qDebug()<<test.left(test.length()-2);
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


