
#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QFontDatabase>
#include <QMessageBox>
#include <QDesktopWidget>
#include <iostream>
#include <QDialog>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow L;
    connection c;


    bool test=c.createconnection();
    if(test)
    {L.show();


}
    return a.exec();
}
