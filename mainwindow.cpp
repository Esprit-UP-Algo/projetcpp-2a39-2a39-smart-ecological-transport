#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QPrintDialog>
#include<QMessageBox>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QPrintDialog>
#include <QDebug>
#include <QInputDialog>
#include <QCalendarWidget>
#include <QMap>
#include <QStringList>
#include <QApplication>
#include <QWidget>
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItemModel>
#include <QGraphicsScene>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QDate>
#include <QBarSet>
#include <QtCore>
#include <QtCharts>
#include<QSqlRecord>
QString test12; //variable global


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->t_c->setModel(Etmp.afficher());
    ui->t_c2->setModel(Etmp.afficher());
    ui->id_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
    ui->emp_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
    ui->qan_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
    ui->qual_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
    ui->qual_3->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
    ui->id_3->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
    int ret=A.connect_arduino(); // lancer la connexion à arduino
         switch(ret){
         case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
             break;
         case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
            break;
         case(-1):qDebug() << "arduino is not available";
         }
     QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(input()));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::input()
{



    data=A.read_from_arduino();//y9ra mel arudino
    //test1 = data;
    test12 = data;//conversion mel byte ll qstring
    qDebug()<<test12.left(test12.length()-2)<<endl;// /d /n
    ui->rfid->setText(test12.left(test12.length()-2));


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
    if (ui->rfid->text()!=""){

    bool test=c.ajouter();

     if (test==true)
    {
             ui->t_c->setModel(Etmp.afficher());
             ui->t_c2->setModel(Etmp.afficher());

    QMessageBox msgBox;
        QMessageBox::information(nullptr, QObject::tr("success!"),
                                             QObject::tr(""
                                                         "collecte Ajouter."), QMessageBox::Ok);
        QSqlQuery query;
          query.prepare("INSERT INTO rfid (rfid, time) "
                              "VALUES (:rfid, :time)");
              query.bindValue(0, test12.left(test12.length()-2));
              query.bindValue(1, QDateTime::currentDateTime());

       query.exec();
                   }
                   else
                  {
                       QMessageBox::critical(nullptr, QObject::tr("Error !!"),
                                             QObject::tr(""
                                                         "Probleme d'Ajout."), QMessageBox::Cancel);


                   }}
}



void MainWindow::on_le_id_c_supp_clicked()
{
    QModelIndex index = ui->t_c->currentIndex(); // Récupérer l'index de la ligne sélectionnée dans le TableView
     const int COLONNE_ID = 0;
     if (index.isValid()) {
         int row = index.row();

         QModelIndex index = ui->t_c->model()->index(row, COLONNE_ID);
         QVariant idData = ui->t_c->model()->data(index);
         int idToDelete = idData.toInt();
         QString idToDeleteStr = QString::number(idToDelete); // Assurez-vous que COLONNE_ID est correctement défini

         collect C2;
         C2.setid_c(idToDeleteStr);
         if (ui->rfid->text()!=""){

         if (C2.supprimer(C2.getid_c())) {
             ui->t_c->setModel(Etmp.afficher());
             ui->t_c2->setModel(Etmp.afficher());

             QSqlQuery query;
               query.prepare("INSERT INTO rfid (rfid, time) "
                                   "VALUES (:rfid, :time)");
                   query.bindValue(0, test12.left(test12.length()-2));
                   query.bindValue(1, QDateTime::currentDateTime());

            query.exec();

             QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("Collecte supprimé.\nCliquez sur OK pour continuer"), QMessageBox::Ok);



             // Rafraîchir la QTableView en supprimant la ligne supprimée
             ui->t_c->model()->removeRow(row);
             ui->id_2->clear();
             ui->emp_2->clear();
             ui->qan_2->clear();
             ui->qual_2->clear();
             ui->le_date->clear();
    ui->t_c->setModel(Etmp.afficher());
    ui->t_c2->setModel(Etmp.afficher());
         } else {
             QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                                   QObject::tr("Échec de la suppression.\nCliquez sur OK pour continuer"), QMessageBox::Ok);


         }
     } else {


         QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                               QObject::tr("Aucune ligne sélectionnée dans le TableView.\nCliquez sur OK pour continuer"), QMessageBox::Ok);
     }
}}


void MainWindow::on_t_c_activated(const QModelIndex &index)
{

       QString val=ui->t_c-> model()->data(index).toString();
       QString val1=ui->t_c2-> model()->data(index).toString();
          QSqlQuery qry ;
          qry.prepare("select * from COLLECTE where ID_COL='"+val+"'");
            qry.prepare("select * from COLLECTE where ID_COL='"+val1+"'");
          if(qry.exec())
          {
           while (qry.next())
           {   ui -> id_2 -> setText(qry.value(0).toString());
               ui -> emp_2 -> setText (qry.value(1).toString ());
               ui -> qan_2-> setText(qry.value(2).toString());
               ui -> qual_2 -> setText ( qry . value ( 3 ). toString ());
               ui -> le_date -> setDate ( QDate :: fromString ( qry . value ( 4 ). toString (), "aaaa-MM-jj" ));
           }
          }

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
    if (ui->rfid->text()!=""){

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
        ui->t_c2->setModel(Etmp.afficher());

        qDebug() << "Collecte modifiée avec succès.";
        QMessageBox::information(this, "Succès", "Collecte modifiée avec succès.");
        QSqlQuery query;
          query.prepare("INSERT INTO rfid (rfid, time) "
                              "VALUES (:rfid, :time)");
              query.bindValue(0, test12.left(test12.length()-2));
              query.bindValue(1, QDateTime::currentDateTime());

       query.exec();


        // Vous n'avez probablement pas besoin de supprimer la ligne de la vue ici
        // ui->t_c->model()->removeRow(row);

        // Effacer les champs après la modification
        ui->id_2->clear();
        ui->emp_2->clear();
        ui->qan_2->clear();
        ui->qual_2->clear();
        ui->le_date->setDate(QDate::currentDate()); // Réinitialiser la date à la date actuelle ou à une valeur par défaut
    } else {
        qDebug() << "Erreur SQL :" << qry.lastError().text();
        QMessageBox::critical(this, "Erreur", "Échec de la modification de la collecte.");
    }
}}


void MainWindow::on_pushButton_rechercher_clicked()
{
    QString id_cRechercher = ui->lineEdit_idcol_rechercher->text();

       if (id_cRechercher.length()!=0) {
            // Check to ensure the search number is valid
            QMessageBox::warning(this, "Error", "entrer un id de collecte valide svp.");


            return;
        }



        QSqlQuery query;//taqra ml l base acceder ll base
        query.prepare("SELECT * FROM COLLECTE WHERE ID_COL = :id_c");
        query.bindValue(":id_c",id_cRechercher);

        if (query.exec() && query.next()) {
            // A collecte with the searched id_c has been found

            // Create a new model and set it to the QTableView
            QStandardItemModel *model = new QStandardItemModel(this);  //l faza eli besh tdhaharlek star wahdou
            ui->t_c->setModel(model);

            QStringList headers; //les entete taa tablou horizontale
            headers << "ID_COL" << "EMPLACEMENT" << "QUANTITE" << "QUALITE" << "DATE_DE_COLLECTE" ;
            model->setHorizontalHeaderLabels(headers);

            do {
                // Get the data from the query result
               QString id_c = query.value("ID_COL").toString();
               QString empp = query.value("EMPLACEMENT").toString();
               QString quantit = query.value("QUANTITE").toString();
               QString qua= query.value("QUALITE").toString();
                QDate date_po = query.value("DATE_DE_COLLECTE").toDate();


                // Add a new row to the model ,yaani nhot les valeur eli
                QList<QStandardItem*> rowItems;
                rowItems
                         << new QStandardItem(id_c)
                         << new QStandardItem(empp)
                         << new QStandardItem(quantit)
                         << new QStandardItem(qua)
                         << new QStandardItem((date_po).toString());




                model->appendRow(rowItems);//ajouter une nouvelle ligne dans un modele sur QT
            } while (query.next());
        } else {
            // No collecte with the searched id_c was found
            QMessageBox::information(this, "Information", "No Collecte with the number " + QString(id_cRechercher) + " was found.");
        }
}


void MainWindow::on_pushButton_retourner_clicked()
{
     ui->t_c->setModel(Etmp.afficher());
}



void MainWindow::on_pushButton_trier_clicked()
{
    QSqlQueryModel *model =new QSqlQueryModel;
        model->setQuery("SELECT * FROM COLLECTE ORDER BY ID_COL");

            if (model->lastError().isValid()) {

                delete model;
                return;
                // Refresh the view
            }
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



void MainWindow::on_pushButton_clicked()
{
    QPrinter printer(QPrinter::PrinterResolution);
       printer.setPageSize(QPrinter::A4);//thaded taille taa l page
       // Utiliser le format natif de l'imprimante

       // Afficher la boîte de dialogue d'aperçu
       QPrintPreviewDialog previewDialog(&printer, this);

       // Connecter le signal paintRequested avant d'exécuter la boîte de dialogue
       connect(&previewDialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));

       // Afficher la boîte de dialogue d'aperçu
       previewDialog.showMaximized();

       // Exécuter la boîte de dialogue
       if (previewDialog.exec() == QDialog::Accepted) {
           // Si l'utilisateur clique sur OK dans la boîte de dialogue d'aperçu, l'impression sera effectuée dans la fonction print.
       }

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
    chartView->setMinimumSize(600, 400);

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

    ui->tableView_Resultat->setModel(model);
}

void MainWindow::on_ajoutmain_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_suppmain_clicked()
{
     ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_updatemain_clicked()
{
     ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_calendriemain_clicked()
{
     ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_statistique_clicked()
{
     ui->tabWidget->setCurrentIndex(3);
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

void MainWindow::on_lineEdit_idcol_rechercher_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
        QSqlQuery*qry=new QSqlQuery();
        QString text=ui->lineEdit_idcol_rechercher->text();

        if(text.isEmpty())
        {
            ui->t_c2->setModel(Etmp.afficher());

            ui->t_c2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        }
        else
        {
            qry->prepare("select * from COLLECTE where ( ID_COL LIKE'%"+text+"%' OR EMPLACEMENT LIKE'%"+text+"%' OR QUANTITE LIKE'%"+text+"%'OR QUALITE LIKE'%"+text+"%'OR DATE_DE_COLLECTE LIKE'%"+text+"%' ) ");
            qry->exec();
            modal->setQuery(*qry);
            ui->t_c2->setModel(Etmp.afficher());
        }
}
