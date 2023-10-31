#ifndef COLLECT_H
#define COLLECT_H

#include<QString>
#include<QDate>
#include<QSqlQueryModel>

class collect
{
public:
    collect();
    collect(QString,QDate,QString,QString,QDate);
    QString  getid_c();
    QDate  getdate_c();
    QString  getemp();
    QString  getqua();
    QDate  getdate_p();
    void setid_c(QString);
    void setdate_co(QDate);
    void setempp(QString);
    void setqua(QString);
    void setdate_po(QDate);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
private:
    QString id_c,empp,qua;
    QDate    date_co,date_po;
};

#endif // COLLECT_H
