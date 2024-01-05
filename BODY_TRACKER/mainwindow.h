/*
 * mainwindow.h
 *
 *  Created on: 21 jun. 2022
 *      Author: vittorio
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>	//opencv
#include <opencv2/calib3d/calib3d.hpp>
#include <QTimer>
#include "Kinect.h"
#include <dialog1.h>
#include <dialog2.h>
#include "articulacion.h"
#include <QPushButton>
#include <QPropertyAnimation>
#include <QLabel>
#include "test.h"
#include <QMessageBox>
#include <QLineEdit>
#include "paciente.h"
#include "MiExcepcion.h"
#include <QComboBox>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //VideoCapture cap; // para mostrar camara en ventana principal
    Mat src_image;
    QTimer *timer = new QTimer(this);
    int timeSet;
    //QImage MatImageToQt (const Mat &src);
    void draw(Mat& img, Joint& r_1, Joint& r_2, ICoordinateMapper* myMapper, int i);
    Dialog1 *ventana1 = new Dialog1(this);
    Dialog2 *ventana2 = new Dialog2(this);
    void saveData(const std::string&);
    std::string fileName;

    bool banderaTimer;  // timer stops
    bool banderaStartTimer; // timer start
    bool banderaStop;
    bool cameraOpenFlag;    // la camara se encuentra abierta y la bandera = true
    QPushButton *startButton;
    QPropertyAnimation *animation;
    Paciente *patientData = new Paciente();
    Test *prueba = new Test(0);
    // menu desplegable
    void refreshComboBox(int cantTests);

    QString currentTestText;


public slots:
    void Select_Markers();
    void RefreshMarkers();
    void kinect_sk();
    void createFile();
    void createPatient();
    void saveDataSlot();
    void openData();
    void levantaFlag(){banderaTimer = true;};
    void setTime(int t){timeSet = t*1000;};
    void startAnimation();
    void takeName();
    void takeSurname();
    void takeAge();
    void takeHeight();
    void takeWeight();
    void New_Test();
    void GetTestTitle();
    void changeCurrentBox(int);

};

#endif // MAINWINDOW_H
