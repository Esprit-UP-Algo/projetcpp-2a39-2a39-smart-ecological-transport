#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "dechets.h"
#include <smtp.h>
#include"collecte.h"
#include"vente.h"
#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include "conteneur.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QChartView *chartView ;

private slots:





    void on_pushButton_12_clicked();


    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();
void stat();

void on_pushButton_3_clicked();




    void init_button(QWidget *q,QString link);

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


    void on_pb_ajouter_clicked();



    void on_le_id_c_supp_clicked();

    void on_pushButton_update_clicked();






    void on_pushButton_trier_clicked();



    void on_pushButton_exporter_clicked();

     void  print(QPrinter *printer);
     int calculerNombreCollecteJanvier(int mois);

     void on_pushButton_enregistrer_clicked();

     void on_calendarWidget_selectionChanged();

     void on_calendarWidget_clicked(const QDate &date);

     void on_pushButton_STAT_clicked();

     void on_pb_ajouter_2_clicked();

     void on_pb_supprimer_clicked();

     void on_pb_modifier_clicked();


     void on_pb_trier_clicked();

     void on_pb_pdf_clicked();



     void on_pb_excel_clicked();






void on_lineEdit_rech_textChanged(const QString &arg1);

void on_tab_vente_clicked(const QModelIndex &index);

void on_lineEdit_idcol_rechercher_textChanged(const QString &arg1);

void on_t_c_clicked(const QModelIndex &index);
void statistique_chart();

void on_recherche_textChanged(const QString &arg1);
void on_takeImageButton_clicked();
void setCamera(const QCameraInfo &cameraInfo);
void on_pushButton_statistique_2_clicked();
void readyForCapture(bool ready);
void on_pb_ajouter_3_clicked();

void on_pb_modifier_2_clicked();

void on_tab_cont_clicked(const QModelIndex &index);

void on_pb_supprimer_2_clicked();

void on_pb_pdf_2_clicked();

void on_pushButton_9_clicked();

void on_lineEdit_rech_2_textChanged(const QString &arg1);

private:
   Ui::MainWindow *ui;
   Dechets d;
   collect Etmp;
   vente v;
   QCamera *Camera = nullptr;
   QCameraImageCapture *imageCapture = nullptr;
   QMediaRecorder* mediaRecorder = nullptr;

   QImageEncoderSettings imageSettings;
   QAudioEncoderSettings audioSettings;
   QVideoEncoderSettings videoSettings;
   QString videoContainerFormat;
   bool isCapturingImage = false;
   bool applicationExiting = false;
private:
   struct NoteEntry
       {
           QDate date;
           QString note;
       };

       QVector<NoteEntry> notes; // Liste des notes

};
#endif // MAINWINDOW_H
