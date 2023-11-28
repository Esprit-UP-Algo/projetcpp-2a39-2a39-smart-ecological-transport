#ifndef DECHETS_H
#define DECHETS_H
#include <QString>
#include<QDate>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include <QDate>
#include <QAbstractItemModel>
#include <QPainter>

#include<QtDebug>
#include<QObject>
#include<QString>
#include <QMessageBox>
#include <QApplication>
#include <QtCore>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QChart>
#include <QtCharts>
class Dechets
{
    private :
        QString nom,type,matiere,destinataire,etat;
        float poids,volume;
        QDate Date;

    public:
        Dechets(QString a,QString b ,float c,float d,QString e,QString f,QString g,QDate h);
        Dechets ();
        QString getnom (){return nom;}
        QString gettype (){return type;}
        QString getmatiere (){return matiere;}
        QString getdestinataire (){return destinataire ;}
        QString getetat (){return etat ;}
        float getoids(){return poids;}
        float getvolume(){return volume;}
        QDate getDate(){return Date ;}
        bool ajouter ();
        bool supprimer (int);
        bool modifier(int id, const Dechets& newDechets);
        QSqlQueryModel * afficher ();
        QSqlQueryModel *trier(int test);
        QSqlQueryModel *recherche(QString id);
        QChart * statistique_chart();
        QSqlQueryModel *afficher_historique ();
};

#endif // DECHETS_H
