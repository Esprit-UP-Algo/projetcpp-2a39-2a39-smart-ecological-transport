#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "arduino.h"

#include <QMainWindow>
#include "dechets.h"
#include <smtp.h>

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

    void on_pushButton_6_clicked(); // bouton ajouter

    void on_pushButton_7_clicked(); // bouton supprimer

    void on_pushButton_8_clicked(); // bouton modifier

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_PDF_clicked();

    void on_Afficher_activated(const QModelIndex &index);
    void mailSentt(QString status);
    void  sendMaill();

    void on_pushButton_4_clicked();

    void on_nomdechet_activated(const QString &arg1);

    void on_vendre_clicked();
    void input();

private:
    Ui::MainWindow *ui;
    Dechets d;
    Arduino A;
    QByteArray data;

};
#endif // MAINWINDOW_H
