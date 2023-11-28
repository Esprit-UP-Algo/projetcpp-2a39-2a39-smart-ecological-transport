#include "collecte.h"
#include "mainwindow.h"
#include<QtDebug>
#include<QSqlError>
#include<QMessageBox>
#include<QSqlQuery>
#include<QObject>
#include<QMessageBox>



collect::collect ( QString id_c, QString empp,QString  quantit,QString qua,QDate date_po,QString rfid)
{
    this->id_c=id_c;this->empp=empp ;this->quantit=quantit ; this->qua=qua ;this->date_po=date_po ; this->rfid=rfid;
}

QString collect:: getid_c(){return id_c ;}
QString  collect::getemp(){return empp ;}
QString  collect::getquantit(){return quantit ;}
QString  collect::getqua(){return qua ;}
QDate  collect::getdate_po(){return date_po;}
QString  collect::getrfid(){return rfid;}

void collect::setid_c(QString id_c){this->id_c=id_c;}
void collect::setempp(QString empp){this->empp=empp;}
void collect::setquantit(QString quantit){this->quantit=quantit;}
void collect::setqua(QString qua){this->qua=qua;}
void collect::setdate_po(QDate date_po){this->date_po=date_po;}
void collect::setrfid(QString rfid){this->rfid=rfid;}



bool collect::ajouter()
{
    QSqlQuery query;


        query.prepare("INSERT INTO COLLECTE (ID_COL, EMPLACEMENT, QUANTITE,QUALITE,DATE_DE_COLLECTE) "
                            "VALUES (:id_c, :empp, :quantit ,:qua,:date_po)");
            query.bindValue(0, id_c);
            query.bindValue(1, empp);
            query.bindValue(2, quantit);
            query.bindValue(3, qua);
            query.bindValue(4, date_po);


 return query.exec();//bech naaweth el bool

}

QSqlQueryModel *collect::afficher()
{
   QSqlQueryModel *model=new QSqlQueryModel();
   model->setQuery("select * from COLLECTE");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_COL"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("EMPLACEMENT"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("QUANTITE"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("QUALITE"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATE_DE_COLLECTE"));

   return model;

}

bool collect::supprimer(QString id_c)
{

    QSqlQuery query;

    query.prepare("Delete from COLLECTE where ID_COL= :id_c ");

          query.bindValue(":id_c", id_c);
            return  query.exec();



}
