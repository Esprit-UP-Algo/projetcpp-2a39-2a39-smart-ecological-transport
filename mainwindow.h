#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dechets.h"

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
    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_6_clicked(); // bouton ajouter

    void on_pushButton_7_clicked(); // bouton supprimer

    void on_pushButton_8_clicked(); // bouton modifier

private:
    Ui::MainWindow *ui;
    Dechets d;
};
#endif // MAINWINDOW_H
