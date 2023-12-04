#include "conteneur.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QPdfWriter>
#include <QPainter>
#include "connection.h"
using namespace std;
conteneur::conteneur(int id,int niveau,int capacite)
{
    this->id=id;
    this->niveau=niveau;
    this->capacite=capacite;

}
int conteneur::get_id()
{
    return id;
}
int conteneur::get_niveau()
{
    return niveau;
}int conteneur::get_capacite()
{
    return capacite;
}
void conteneur::setid(int id)
{
    this->id=id;
}
void conteneur::setniveau(int niveau)
{
    this->niveau=niveau;
}
void conteneur::setcapacite(int capacite)
{
    this->capacite=capacite;
}

QSqlQueryModel * conteneur::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CONTENEUR");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NIVEAU"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("CAPACITE"));


    return model;
}
bool conteneur::ajouter()
{
    QString res =QString::number(id);
    QString res1 =QString::number(niveau);
    QString res2 =QString::number(capacite);

    QSqlQuery query;
    query.prepare("INSERT INTO CONTENEUR (ID,NIVEAU,CAPACITE)"
                  "VALUES (:id,:niveau,:capacite)");
    query.bindValue(":id",res);
    query.bindValue(":niveau",res1);
    query.bindValue(":capacite",res2);

   return query.exec();

}
bool conteneur::supprimer(int id)
{

    QSqlQuery query;

    query.prepare("Delete from CONTENEUR where ID=:id");
    query.bindValue(":id",id);
    return query.exec();
}
bool conteneur::modifier(int id,int niveau,int capacite)

{
    QSqlQuery query;
    QString res =QString::number(id);
    QString res1 =QString::number(niveau);
    QString res2 =QString::number(capacite);


    query.prepare("update CONTENEUR SET ID= :id,NIVEAU= :niveau,CAPACITE= :capacite where ID=:id");

    query.bindValue(":id",res);

    query.bindValue(":niveau",res1);

    query.bindValue(":capacite",res2);


        return    query.exec();


    }
void conteneur::pdfprinter()
{
QPdfWriter pdf("C:/conteneur/conteneur.pdf");

       QPainter painter(&pdf);


      painter.setPen(Qt::red);
      painter.setFont(QFont("Arial", 50));
      painter.drawText(2000,1000,"CONTENEUR");
      painter.setPen(Qt::red);


      painter.setFont(QFont("Arial",6));
      painter.drawText(500,3300,"ID");
      painter.drawText(1400,3300,"NIVEAU");
      painter.drawText(2250,3300,"CAPACITE");



      QSqlQuery query;
      int i = 4000;

       query.prepare("select * from CONTENEUR");
       query.exec();
    while (query.next())
      {
          painter.setPen(Qt::black);
          painter.setFont(QFont("Arial", 6));
          painter.drawText(500,i,query.value(0).toString());
          painter.drawText(1400,i,query.value(1).toString());
          painter.drawText(2250,i,query.value(2).toString());




          i = i +500;
      }
}
QSqlQueryModel * conteneur::trie_id()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CONTENEUR ORDER BY ID ASC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("niveau"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("capacite"));
    return model;
}
QSqlQueryModel* conteneur::chercherid(int)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM CONTENEUR where ID=:id");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NIVEAU"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("CAPACITE"));

    return model;
}

