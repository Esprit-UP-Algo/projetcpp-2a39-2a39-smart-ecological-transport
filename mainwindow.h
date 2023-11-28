#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QLineEdit>
#include<QPushButton>
#include <QMainWindow>
#include<QTableView>
#include<QTableWidget>
#include<QDate>
#include<QComboBox>
#include<QObject>
#include <QPrinter>
#include <QPrintDialog>
#include"collecte.h"
#include <QAbstractItemModel>
#include <QStandardItem>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_MOC_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  explicit  MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

void input();
    void on_pb_ajouter_clicked();



    void on_le_id_c_supp_clicked();

    void on_pushButton_update_clicked();

    void on_t_c_activated(const QModelIndex &index);



    void on_pushButton_rechercher_clicked();

    void on_pushButton_retourner_clicked();

    void on_pushButton_trier_clicked();



    void on_pushButton_exporter_clicked();

    void on_pushButton_clicked();
     void  print(QPrinter *printer);
     int calculerNombreCollecteJanvier(int mois);

     void on_pushButton_enregistrer_clicked();

     void on_calendarWidget_selectionChanged();

     void on_calendarWidget_clicked(const QDate &date);

     void on_pushButton_STAT_clicked();

     void on_ajoutmain_clicked();

     void on_suppmain_clicked();

     void on_updatemain_clicked();

     void on_calendriemain_clicked();

     void on_pushButton_statistique_clicked();



     void on_pushButton_statistique_2_clicked();

     void on_lineEdit_idcol_rechercher_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    collect Etmp;
private:
    Arduino A; // objet temporaire
    QByteArray data;
    struct NoteEntry
        {
            QDate date;
            QString note;
        };

        QVector<NoteEntry> notes; // Liste des notes

};
#endif // MAINWINDOW_H
