#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStandardItemModel>
#include <QMainWindow>
#include <QTableView>
#include"vente.h"
#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include "arduino.h"
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
    void on_takeImageButton_clicked();
    void setCamera(const QCameraInfo &cameraInfo);
    void readyForCapture(bool ready);
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_rechercher_clicked();

    void on_pb_trier_clicked();

    void on_pb_pdf_clicked();
    void input();

    void on_pb_stat_clicked();

    void on_pb_actualiser_clicked();

    void on_pb_excel_clicked();
    


    void on_send_clicked();


private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    vente v;
    QString ref;
    QCamera *Camera = nullptr;
    QCameraImageCapture *imageCapture = nullptr;
    QMediaRecorder* mediaRecorder = nullptr;

    QImageEncoderSettings imageSettings;
    QAudioEncoderSettings audioSettings;
    QVideoEncoderSettings videoSettings;
    QString videoContainerFormat;
    bool isCapturingImage = false;
    bool applicationExiting = false;
    QByteArray data; // variable contenant les données reçues

           Arduino A;
};

#endif // MAINWINDOW_H
