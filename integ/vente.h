#ifndef VENTE_H
#define VENTE_H
#include<QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QtCharts>
#include <QChartView>
#include <QPainter>
#include <QAxObject>


class vente
{
public:
    vente();
    vente(int,QString,int,QString,int,int);
    int  getid_v();
    QString  getdate_();
    int  getqua();
    QString  gettype();
    int  getprix();
    int  getmontant();


    void setid_v(int);
    void setdate_(QString);
    void setqua(int);
    void settype(QString);
    void setprix(int);
    void setmontant(int);


    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int,QString,int,QString,int,int);
    bool rechercher(int);
    bool tri(QString);
    QSqlQueryModel*  rechercherParId(int id_v);

    void exportpdf();
    QChartView *stat();
    //void generateInvoiceExcel(const QString& invoiceId);
    QAbstractItemModel* Excel();


private:
    QString date_,type;
    int id_v,qua,prix,montant;

};


#endif // VENTE_H
