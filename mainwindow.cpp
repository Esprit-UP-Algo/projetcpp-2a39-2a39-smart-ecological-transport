#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vente.h"
#include<QIntValidator>
#include <QMessageBox>
#include <QSqlRecord>
#include <QRegExpValidator>
#include <QSqlError>
#include <QDebug>
#include <QChartView>

int re=0;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCamera(QCameraInfo::defaultCamera());

        ui->le_id_v->setValidator(new QIntValidator(100, 9999999, this));

        ui->le_qua->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
        ui->le_type->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
        ui->le_prix->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
        ui->le_montant->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
        ui->le_id_col->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,9}"), this));
        ui->tab_vente->setModel(v.afficher());



                /*creation d'un QStandardItemModel et affichage dans un QTableView

                    model = new QStandardItemModel(7,7,this);
                    model->setHorizontalHeaderLabels({"id_v ","date_ ","qua","type","prix","montant","id_col",});


                  // pour les lignes
                  for (int i=0;i<7;++i)
                    { // Pour les colonnes
                    for (int j=0;j<7;++j)
                      {  // on crée un item==cellule
                       QStandardItem *item = new QStandardItem;
                       // On définit les valeurs initiales des cases
                       //item->setText("") ;
                       //item->setText(QString::number(0));
                       // Et enfin on l'associe avec notre model

                       model->setItem(0,0,item);
                      }
                    }
                    //recuperer les valeurs :
                       // int valeur = model->item(ligne, colonne)->text().toInt();
                       // double valeur = model->item(ligne, colonne)->text().toDouble();

                  // affichage, on utilise un QTableView
*/



        int ret=A.connect_arduino(); // lancer la connexion à arduino
                    switch(ret){
                    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                        break;
                    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                       break;
                    case(-1):qDebug() << "arduino is not available";
                        re=1;
                    }
                     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(input()));
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
    MainWindow::~MainWindow()
    {
        delete ui;
    }
    void MainWindow::input(){
        data=A.read_from_arduino();
        ref= data;
        qDebug()<<ref.left(ref.length()-2);
        QSqlQuery query;
        query.prepare("SELECT acti FROM  matrics where digit=:id");
        query.bindValue(":id", ref.left(ref.length()-2));
    query.exec();
            if(query.next()){
        if (query.value(0).toString()=="ajout"){
            int id_v=ui->le_id_v->text().toInt();
            QString date_=ui->le_date_->text();
            QString qua=ui->le_qua->text();
            QString type=ui->le_type->currentText();
            QString prix=ui->le_prix->text();
            QString montant=ui->le_montant->text();
            QString id_col=ui->le_id_col->text();

            vente v(id_v,date_,qua,type,prix,montant,id_col);
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
        }
        else if (query.value(0).toString()=="modifier"){
            int id_v=ui->lineEdit_id_v->text().toInt();
            QString date_=ui->DateEdit_date->text();
            QString qua=ui->lineEdit_qua->text();
            QString type=ui->lineEdit_type_->currentText();
            QString prix=ui->lineEdit_prix->text();
            QString montant=ui->lineEdit_montant->text();
            QString id_col=ui->lineEdit_id_col->text();

            vente v(id_v,date_,qua,type,prix,montant,id_col);
            bool test=v.modifier(v.getid_v(),v.getdate_(),v.getqua(),v.gettype(),v.getprix(),v.getmontant(),v.getid_col());
            if (test)
            {
                ui->tab_vente->setModel(v.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("modifier avec succes.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->lineEdit_id_v->clear();



             }
            else
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("modifier non effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);        }
        else if (query.value(0).toString()=="supprimer"){
            vente v1; v1.setid_v(ui->le_id_v_supp->text().toInt());
            bool test=v1.supprimer(v1.getid_v());
               QMessageBox msgBox;

               if(test)
                  { msgBox.setText("supp avec succes");
                   ui->tab_vente->setModel(v.afficher());
                  }
               else
                   msgBox.setText("Echec de supp");
                   msgBox.exec();
        }
        else {
            qDebug()<<"try again";

        }
    }
    }

void MainWindow::on_pb_ajouter_clicked()
{
    if(re==1){
    int id_v=ui->le_id_v->text().toInt();
    QString date_=ui->le_date_->text();
    QString qua=ui->le_qua->text();
    QString type=ui->le_type->currentText();
    QString prix=ui->le_prix->text();
    QString montant=ui->le_montant->text();
    QString id_col=ui->le_id_col->text();

    vente v(id_v,date_,qua,type,prix,montant,id_col);
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
}}





void MainWindow::on_pb_supprimer_clicked()
{
      if(re==1){
  vente v1; v1.setid_v(ui->le_id_v_supp->text().toInt());
  bool test=v1.supprimer(v1.getid_v());
     QMessageBox msgBox;

     if(test)
        { msgBox.setText("supp avec succes");
         ui->tab_vente->setModel(v.afficher());
        }
     else
         msgBox.setText("Echec de supp");
         msgBox.exec();
}}






void MainWindow::on_pb_modifier_clicked()
{
      if(re==1){
    int id_v=ui->lineEdit_id_v->text().toInt();
    QString date_=ui->DateEdit_date->text();
    QString qua=ui->lineEdit_qua->text();
    QString type=ui->lineEdit_type_->currentText();
    QString prix=ui->lineEdit_prix->text();
    QString montant=ui->lineEdit_montant->text();
    QString id_col=ui->lineEdit_id_col->text();

    vente v(id_v,date_,qua,type,prix,montant,id_col);
    bool test=v.modifier(v.getid_v(),v.getdate_(),v.getqua(),v.gettype(),v.getprix(),v.getmontant(),v.getid_col());
    if (test)
    {
        ui->tab_vente->setModel(v.afficher());
    QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("modifier avec succes.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui->lineEdit_id_v->clear();



     }
    else
    QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                QObject::tr("modifier non effectue.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}}


void MainWindow::on_pb_rechercher_clicked()
{

    int idToSearch = ui->lineEdit_rech->text().toInt();

    qDebug()<<"idToSearch"<<idToSearch;
    QSqlQueryModel* model = v.rechercherParId(ui->lineEdit_rech->text().toInt());
    qDebug()<<"idToSearch"<<idToSearch;

        if (model->rowCount() > 0)//nb ligne
        {    qDebug()<<"idToSearchhhh"<<model;

            ui->tab_vente->setModel(model);
        }
        else
        {
            QMessageBox::information(this, "No Records", "No records found for the entered ID.");
        }

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
{
        QFile file("mypdf.pdf");
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



void MainWindow::on_pb_stat_clicked()
{
   QChartView *chartView = v.stat();
        chartView->show();
}

void MainWindow::on_pb_actualiser_clicked()
{
  ui->tab_vente->setModel((v.afficher()));
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
        ui->tab_vente->setModel(v.Excel());

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

/*void MainWindow::on_send_clicked()
{
    sms s;
     const QString msg = ui->sms->toPlainText();

    const QString recipient_phone_number = "+216"+ ui->phone->text();

   s.sendSMS(recipient_phone_number, msg);
}
*/
