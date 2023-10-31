#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"collect.h"

#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->t_c->setModel(c.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString  id_c = ui->id->text();
    QDate  date_co = ui->date_c1->date();
    QString  empp = ui->emp->text();
    QString  qua = ui->qan->text();
    QDate  date_po = ui->date_p->date();
    collect c ( id_c,date_co,empp,qua,date_po);
    bool test= c.ajouter();
    if(test)
    {
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("aj successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->t_c->setModel(c.afficher());
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    collect c;
    QString gid_c=ui->sup->text();
    c.setid_c(ui->sup->text());
    bool test= c.supprimer(gid_c);
    if(test)
    {
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("supp successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->t_c->setModel(c.afficher());

    }

}

