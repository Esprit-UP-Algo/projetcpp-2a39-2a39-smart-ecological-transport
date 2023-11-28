#ifndef COLLECT_H
#define COLLECT_H

#include<QString>
#include<QDate>
#include<QSqlQueryModel>
#include<QSqlQuery>

class collect
{
public:
    collect();
    collect(QString,QDate,QString,QString,int);
    QString  getid_c();
    QDate  getdate_c();
    QString  getempp();
    QString  getqua();
    int getQuantite();
    void setid_c(QString);
    void setdate_co(QDate);
    void setempp(QString);
    void setqua(QString);
    void setQuantite(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
private:
    QString id_c,empp,qua;
    QDate    date_co;
    int quantite;
};

#endif // COLLECT_H
