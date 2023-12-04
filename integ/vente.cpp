#include "vente.h"
#include "connection.h"
#include <QObject>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QMessageBox>
#include<QtDebug>
#include <QPainter>
#include <QPdfWriter>
#include <QTextDocument>
#include <QtCharts>
#include <QChartView>
#include <QtCharts/QLineSeries>
#include <QPaintDevice>
#include <QPieSeries>
#include <QTabWidget>
#include <QAbstractItemModel>
vente::vente()
{
    id_v=0;
    date_="";
    qua=0;
    type="";
    prix=0;
    montant=0;


}
vente::vente(int id_v,QString date_, int qua, QString type, int prix, int montant)
{
this->id_v=id_v;
this->date_=date_;
this->qua=qua;
this->type=type;
this->prix=prix;
this->montant=montant;

}

int vente::getid_v(){return id_v;}
QString vente:: getdate_(){return date_ ;}
int vente::getqua(){return  qua;}
QString vente::gettype(){return type;}
int vente::getprix(){return prix;}
int vente::getmontant(){return montant;}


void vente::setid_v(int id_v){this->id_v=id_v;}
void vente::setdate_(QString date_){this->date_=date_;}
void vente::setqua(int qua){this->qua=qua;}
void vente::settype(QString type){this->type=type;}
void vente::setprix(int prix){this->prix=prix;}
void vente::setmontant(int montant){this->montant=montant;}


bool vente::ajouter()
{
    QSqlQuery query;
    QString id_v_string= QString::number(id_v);
        query.prepare("INSERT INTO VENTE_DE_DECHETS (ID_V, DATE_, QUANTITE,TYPE, PRIX, MONTANT, ID_COL)"
                      "VALUES (:id_v, :date_, :qua, :type, :prix, :montant, :id_col)");
        query.bindValue(0, id_v);
        query.bindValue(1, date_);
        query.bindValue(2, qua);
        query.bindValue(3, type);
        query.bindValue(4, prix);
        query.bindValue(5, montant);

        return query.exec();//bech naaweth el bool
}


bool vente::supprimer(int id_v)
{
    QSqlQuery query;
    query.prepare("DELETE FROM VENTE_DE_DECHETS WHERE id_v=:id_v");
    query.bindValue(0, id_v);
    return query.exec();

}


QSqlQueryModel* vente::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
       model->setQuery("SELECT * FROM  VENTE_DE_DECHETS");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_V"));//narjaa mbaad lli aamltou fl DB
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUA"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("MONTANT"));


       return model;
}

bool vente::modifier(int id_v,QString date_, int qua, QString type, int prix, int montant)
{
    QSqlQuery query;
    QString id_v_string= QString::number(id_v);
    query.prepare("UPDATE VENTE_DE_DECHETS SET DATE_=:DATE_,QUANTITE=:QUANTITE,TYPE=:TYPE,PRIX=:PRIX,MONTANT=:MONTANT,ID_COL=:ID_COL WHERE ID_V=:ID_V");
    query.bindValue(":ID_V", id_v);
    query.bindValue(":DATE_",date_);
    query.bindValue(":QUANTITE", qua);
    query.bindValue(":TYPE", type );
    query.bindValue(":PRIX", prix);
    query.bindValue(":MONTANT", montant);

    return query.exec();

}



bool vente::rechercher(int id_v)
{
    QSqlQuery query;
     QString text=QString::number(id_v);
    query.prepare("SELECT ID FROM VENTE_DE_DECHETS WHERE id_v LIKE'%"+text+"%'");
    if (query.exec() && query.next())
    {
        return true;
    }
    return false;// L'ID est unique
}

QSqlQueryModel* vente::rechercherParId(int id_v)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
QString text=QString::number(id_v);
    query.prepare("SELECT * FROM VENTE_DE_DECHETS  WHERE id_v LIKE'%"+text+"%'");

    if (query.exec())
    {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_V"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("MONTANT"));


        //
        if (model->rowCount() == 0)
        {
            qDebug() << "No records found with ID_V:" << id_v;
            delete model;
            return nullptr;
        }

        return model;
    }
    else
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        delete model;
        return nullptr;  // indicate an error
    }
}
void vente::exportpdf()
{

}


/*void vente::pdf()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM VENTE_DE_DECHETS");

    if(query.exec())
    {
        if(query.next())
        {
            QPdfWriter pdfWriter("vente.pdf");
            QPainter painter(&pdfWriter);
            QTextDocument doc;

            QString vente = "<p style='font-size:250pt;'>VENTE_DE_DECHETS: </p>"; //init ch HTML nommée res

            do {// extraire de requet et conv a ch ress

                vente += "<p style='font-size:200pt;'><strong>DATE_: </strong>" + query.value("DATE_").toString() + "</p>";
                vente += "<p style='font-size:200pt;'><strong>QUANTITE: </strong>" + query.value("QUANTITE").toString() + "</p>";
                vente += "<p style='font-size:200pt;'><strong>TYPE: </strong>" + query.value("TYPE").toString() + "</p>";
                vente += "<p style='font-size:200pt;'><strong>PRIX: </strong>" + query.value("PRIX").toString() + "</p>";
                vente += "<p style='font-size:200pt;'><strong>MONTANT: </strong>" + query.value("MONTANT").toString() + "</p>";
                vente += "<p style='font-size:200pt;'><strong>ID_COL: </strong>" + query.value("ID_COL").toString() + "</p>";
            } while (query.next());

            doc.setHtml(vente);
            doc.drawContents(&painter);
        }
        else
        {
            QMessageBox::warning(nullptr, "Warning", "No resources found.");
        }
    }
    else
    {
        qDebug() << "Error generating report: " << query.lastError();
    }
}
*/



QAbstractItemModel* vente::Excel()
{
    QStandardItemModel* model = new QStandardItemModel();


    // Ajouter les en-têtes
    model->setHorizontalHeaderLabels({"ID_V", "Date", "Quantité", "Type", "Prix", "Montant", "ID_Col"});

    // Remplir le modèle avec des données
    for (int row = 0; row < 5; ++row) {
        QList<QStandardItem*> rowData;

        // Exemple : Ajouter des données fictives pour chaque colonne
        QStandardItem* idItem = new QStandardItem(QString::number(row + 1));  // ID_V
        QStandardItem* dateItem = new QStandardItem("01-01-2000");  // Date (exemple)
        QStandardItem* quaItem = new QStandardItem(QString::number(10 + row));  // Quantité (exemple)
        QStandardItem* typeItem = new QStandardItem("mauvais");  // Type (exemple)
        QStandardItem* prixItem = new QStandardItem(QString::number(50.0 + row));  // Prix (exemple)
        QStandardItem* montantItem = new QStandardItem(QString::number((10 + row) * (50.0 + row)));  // Montant (exemple)


        // Ajouter les éléments à la liste rowData
        rowData << idItem << dateItem << quaItem << typeItem << prixItem << montantItem ;

        // Ajouter la ligne au modèle
        model->appendRow(rowData);
    }

    return model;
}

/*QAbstractItemModel* vente::Excel()
{
    QStandardItemModel* model = new QStandardItemModel();

        // Populate the model with data, for example:
        for (int row = 0; row < 5; ++row) {
            QList<QStandardItem*> rowData;
            for (int col = 0; col < 3; ++col) {
                QStandardItem* item = new QStandardItem(QString("Data %1,%2").arg(row).arg(col));
                rowData.append(item);
            }
            model->appendRow(rowData);
        }

        return model;
}*/
/*void vente::generateInvoiceExcel(const QString& invoiceId)
{
    QSqlQuery query;
        query.prepare("SELECT * FROM VENTE_DE_DECHETS WHERE id_v = :id");
        query.bindValue(":id", invoiceId);

        if(query.exec())
        {
            if(query.next())
            {
                // Create Excel application
                QAxObject excel("Excel.Application");
                if (!excel.isNull()) {
                    // Create new workbook
                    QAxObject *workbooks = excel.querySubObject("Workbooks");
                    QAxObject *workbook = workbooks->querySubObject("Add");

                    // Access the active worksheet
                    QAxObject *sheets = workbook->querySubObject("Worksheets");
                    QAxObject *sheet = sheets->querySubObject("Item(int)", 1);

                    // Write header row
                    QStringList headers = {"id_v", "date_", "qua", "type", "prix", "montant", "id_col"};
                    for (int i = 0; i < headers.size(); ++i) {
                        sheet->querySubObject("Cells(int, int)", 1, i + 1)->setProperty("Value", headers.at(i));
                    }

                    int row = 2; // Start from the second row for data

                    do {
                        for (int i = 0; i < headers.size(); ++i) {
                            sheet->querySubObject("Cells(int, int)", row, i + 1)->setProperty("Value", query.value(i).toString());
                        }

                        ++row;
                    } while (query.next());

                    // Save the workbook
                    QString fileName = "invoice_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".xlsx";
                    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName));

                    // Close Excel
                    excel.dynamicCall("Quit()");

                    QMessageBox::information(nullptr, "Success", "Invoice Excel file generated successfully: " + fileName);
                } else {
                    QMessageBox::critical(nullptr, "Error", "Could not create Excel application.");
                }
            }
            else
            {
                QMessageBox::warning(nullptr, "Warning", "No invoice found for id " + invoiceId);
            }
        }
        else
        {
            qDebug() << "Error generating invoice Excel: " << query.lastError();
        }
}*/



