#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStandardItemModel>
#include <QMainWindow>
#include <QTableView>
#include"vente.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_rechercher_clicked();

    void on_pb_trier_clicked();

    void on_pb_pdf_clicked();

    void on_pb_stat_clicked();

    void on_pb_actualiser_clicked();

    void on_pb_excel_clicked();
    


private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    vente v;
};

#endif // MAINWINDOW_H
