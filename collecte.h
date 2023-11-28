#ifndef COLLECT_H
#define COLLECT_H

#include<QString>
#include<QDate>
#include<QSqlQueryModel>

class collect
{
private:
    QString id_c,empp,qua,  quantit,rfid;
    QDate  date_po;

public:
    collect(){}//constructeur:yaamel initialisation fi 0
    collect(QString,QString,QString,QString,QDate,QString);//constructeure paremetri


    QString  getid_c();
    QString  getquantit();
    QString  getemp();
    QString  getqua();
    QDate  getdate_po();
    QString getrfid();


    void setid_c(QString);
    void setquantit(QString);
    void setempp(QString);
    void setqua(QString);
    void setdate_po(QDate);
    void setrfid(QString);


    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString id_c);

QSqlQueryModel*  rechercherParDate(const QDate& date);





};

#endif // COLLECT_H
