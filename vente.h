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
    vente(int,QString,QString,QString,QString,QString,QString);
    int  getid_v();
    QString  getdate_();
    QString  getqua();
    QString  gettype();
    QString  getprix();
    QString  getmontant();
    QString  getid_col();

    void setid_v(int);
    void setdate_(QString);
    void setqua(QString);
    void settype(QString);
    void setprix(QString);
    void setmontant(QString);
    void setid_col(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QString,QString,QString);
    bool rechercher(int);
    bool tri(QString);
    QSqlQueryModel*  rechercherParId(int id_v);

    void exportpdf();
    QChartView *stat();
    //void generateInvoiceExcel(const QString& invoiceId);
    QAbstractItemModel* Excel();


private:
    QString date_,qua,type,prix,montant,id_col;
    int id_v;

};


#endif // VENTE_H
