/*
 * mainwindow.cpp
 *
 *  Created on: 21 jun. 2022
 *      Author: vittorio
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>
#include <QFile>
#include <fstream>
#include <iostream>
#include <QPalette>
#include <QFrame>

#include <QtOpenGL>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configuracion de la ventana
    resize(1000,700);
    this->setWindowTitle("Body Tracker");
    // seteo imagen de background de ventana principal
    QPixmap background("/build-bodyTracker-Desktop_Qt_6_2_4_MSVC2019_64bit-Release/image/wallpaper.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    // flags
    timeSet = 0;
    banderaStartTimer = false;
    cameraOpenFlag = false;

    // config datos de paciente GUI
    QLabel *titulo = new QLabel(this);
    titulo->setText("PATIENT DATA");
    titulo->setGeometry(QRect(QPoint(70, 30), QSize(165,35)));
    titulo->setStyleSheet("color: rgb(255, 255, 255); font: 700 16pt Segoe UI;");
    titulo->setFrameStyle(QFrame::Panel | QFrame::Raised);
    titulo->setLineWidth(2);

    QLabel *paciente = new QLabel(this);
    paciente->setText("Name:\n\nSurname:\n\nAge:\n\nHeight:\n\nWeight:");
    paciente->setGeometry(QRect(QPoint(50, 75), QSize(100,221)));
    paciente->setStyleSheet("color: rgb(255, 255, 255); font: 13pt Segoe UI; font: 700 13pt Segoe UI;");

    // ingresos de texto ; se completa patient data
    QObject::connect(ui->name,SIGNAL(editingFinished()),this,SLOT(takeName()));
    QObject::connect(ui->surname,SIGNAL(editingFinished()),this,SLOT(takeSurname()));
    QObject::connect(ui->age,SIGNAL(editingFinished()),this,SLOT(takeAge()));
    QObject::connect(ui->height,SIGNAL(editingFinished()),this,SLOT(takeHeight()));
    QObject::connect(ui->weight,SIGNAL(editingFinished()),this,SLOT(takeWeight()));

    // config start button
    QPixmap startIcon("/image/start.png");
    startButton = new QPushButton("", this);
    startButton->setGeometry(QRect(QPoint(70, 600), QSize(200, 79)));
    startButton->setIcon(startIcon);
    startButton->setIconSize(startIcon.rect().size());
    startButton->setStyleSheet("background-color: rgba(0,0,0,0%)");
    animation = new QPropertyAnimation(startButton, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(70, 260, 200, 79));
    animation->setEndValue(QRect(80, 260, 200, 79));

    //
    QObject::connect(ui->actionSelect_Markers,SIGNAL(triggered()),this,SLOT(Select_Markers()));
    QObject::connect(ventana1, SIGNAL(accepted()), this, SLOT(RefreshMarkers()));
    QObject::connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(setTime(int)));
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(levantaFlag()));
    QObject::connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(kinect_sk()));
    QObject::connect(startButton,SIGNAL(pressed()),this,SLOT(startAnimation()));
    QObject::connect(ui->newTestButton,SIGNAL(clicked()),this,SLOT(GetTestTitle()));
    QObject::connect(ventana2, SIGNAL(accepted()), this, SLOT(New_Test()));
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeCurrentBox(int)));

    // manejo del file
    QObject::connect(ui->actionSave_As,SIGNAL(triggered()),this,SLOT(createFile()));
    QObject::connect(ui->actionSimple_Test,SIGNAL(triggered()),this,SLOT(createFile()));
    QObject::connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveDataSlot()));
    QObject::connect(ui->actionOpen_File,SIGNAL(triggered()),this,SLOT(openData()));
    QObject::connect(ui->actionPatient,SIGNAL(triggered()),this,SLOT(createPatient()));

}

MainWindow::~MainWindow()
{
    /*for (int i=0; i<cantArt; i++){
        delete art[i];
    }*/

    delete timer;
    delete startButton;
    delete ventana1;
    delete animation;
    delete patientData;
    delete prueba;

    delete ui;
}

void MainWindow::refreshComboBox(int cantTests){
    if (cantTests != 0){
        for (int i = 0; i < cantTests; i++){
            if (i>=ui->comboBox->count())    ui->comboBox->addItem("TEST N°" + QString::number(i+1));
        }
    } else {
        ui->comboBox->setEnabled(false);
    }
}

void MainWindow::startAnimation(){
    // animation button
    animation->start();
    animation->setStartValue(QRect(80, 600, 200, 79));
    animation->setEndValue(QRect(70, 600, 200, 79));
    animation->start();

    // lógica para que timer arranque una sola vez y no se vea afectado tras varios clicks en START button
    try{
        if (!banderaStartTimer && cameraOpenFlag){
            timer->start(timeSet);
            banderaStartTimer = true;
        }
        else if(!cameraOpenFlag)
            throw MiExcepcion( string( "La camara no se encuentra abierta ") );
    }
    catch(MiExcepcion &ex){
        QMessageBox messageBox;
        QString stringError = QString::fromStdString(ex.what());
        messageBox.warning(0,"Error", stringError);
        messageBox.setFixedSize(500,200);
        return;
    }

}

void MainWindow::Select_Markers()
{
    ventana1->setModal(true);
    ventana1->show();  // es lo mismo que ventana1-> setVisible(true);
}

void MainWindow::RefreshMarkers(){
    // cuenta cuantas articulaciones se quieren crear para luego tomar sus datos
    // también se crean los objetos articulacion
    for (int i=0; i<16; i++){
         if (ventana1->ReturnMarker(i) == true){
             prueba->askForMem(i);
             //art[cantArt] = new Articulacion(i);
             //art[cantArt]->des_habilita(true);
         } //else art[cantArt]->des_habilita(false);
     }
    //ui->lcdNumber->display(prueba->returnCantArt());

    /*
    for (int i=0; i<16; i++){
        if (ventana1->ReturnMarker(i) == true){
            art[i].des_habilita(true);
        } else art[i].des_habilita(false);
    }
    */
    /*unsigned long long tam;
    tam = sizeof(art[2]);
    string tamchar = std::to_string(tam);
    QString str = QString::fromStdString(tamchar);
    ui->label_3->setText(str);*/
}

void MainWindow::draw(Mat& img, Joint& r_1, Joint& r_2, ICoordinateMapper* myMapper, int i)
{
    //

    if (r_1.TrackingState == TrackingState_Tracked && r_2.TrackingState == TrackingState_Tracked)
    {


        ColorSpacePoint t_point;    //
        Point   p_1, p_2;

        myMapper->MapCameraPointToColorSpace(r_1.Position, &t_point);
        p_1.x = t_point.X;
        p_1.y = t_point.Y;
        myMapper->MapCameraPointToColorSpace(r_2.Position, &t_point);
        p_2.x = t_point.X;
        p_2.y = t_point.Y;

        if (banderaStartTimer){
            for (int j=0; j<prueba->returnCantArt(); j++){
                if (i == prueba->returnID(j)){
                    prueba->capturaPos(-1*r_2.Position.X,r_2.Position.Y,r_2.Position.Z,timeSet-timer->remainingTime(),j);
                    circle(img, p_2, 20, Vec3b(0, 0, 255), -1);
                } else circle(img, p_2, 10, Vec3b(255, 0, 0), -1);
            }
        }

        line(img, p_1, p_2, Vec3b(0, 255, 0));
    }
}

void MainWindow::kinect_sk()
{
    // si patientdata no está creado, pido memoria para simple test
    //if (!patientData) prueba = new Test(0);


    IKinectSensor* mySensor = nullptr;

    try{
        HRESULT hr = GetDefaultKinectSensor(&mySensor);
        if (FAILED(hr)){
            throw MiExcepcion( string( "Conecte el sensor a la computadora. ") );
        }

        hr = mySensor->Open();
        if (FAILED(hr)){
            throw MiExcepcion( string( "Conecte el sensor a la computadora. ") );
        }

        BOOLEAN bIsOpen = 0;
        mySensor->get_IsOpen(&bIsOpen);
        if (!bIsOpen ){
            throw MiExcepcion( string( "Conecte el sensor a la computadora. ") );
        }

        /*BOOLEAN isAvailable = 0;
        mySensor->get_IsAvailable(&isAvailable);
        if (!isAvailable ){
            throw MiExcepcion( string( "Conecte el sensor a la computadora. ") );
        }*/
    }
    catch (MiExcepcion &ex){
        QMessageBox messageBox;
        QString stringError = QString::fromStdString(ex.what());
        messageBox.warning(0,"Error", stringError);
        messageBox.setFixedSize(500,200);
        return;
    }


    IColorFrameSource* myColorSource = nullptr;
    mySensor->get_ColorFrameSource(&myColorSource);

    IColorFrameReader* myColorReader = nullptr;
    myColorSource->OpenReader(&myColorReader);

    int colorHeight = 0, colorWidth = 0;
    IFrameDescription* myDescription = nullptr;
    myColorSource->get_FrameDescription(&myDescription);
    myDescription->get_Height(&colorHeight);
    myDescription->get_Width(&colorWidth);

    IColorFrame* myColorFrame = nullptr;
    Mat original(colorHeight, colorWidth, CV_8UC4);

    //*******ColorFrame*********

    IBodyFrameSource* myBodySource = nullptr;
    mySensor->get_BodyFrameSource(&myBodySource);

    IBodyFrameReader* myBodyReader = nullptr;
    myBodySource->OpenReader(&myBodyReader);

    int myBodyCount = 0;
    myBodySource->get_BodyCount(&myBodyCount);

    IBodyFrame* myBodyFrame = nullptr;

    ICoordinateMapper* myMapper = nullptr;
    mySensor->get_CoordinateMapper(&myMapper);

    //cap.open(1);  // abre camara (conectar con qlabel para cameraView

    cameraOpenFlag = true;
    banderaTimer = false;
    banderaStop = false;
    ui->spinBox->setEnabled(false);
    ui->comboBox->setEnabled(false);
    banderaStartTimer = false;

    // seteo la base de tiempo;
    // en caso de no haber sido introducida --> 1 hora
    if (timeSet == 0)
        timeSet = 3600000;

    //*******BodyFrameMapper********
    while (!banderaStop)
    {

        ui->lcdNumber->display(timeSet-timer->remainingTime());

        while (myColorReader->AcquireLatestFrame(&myColorFrame) != S_OK); // PROBAR QUITANDO myColorFrame
        myColorFrame->CopyConvertedFrameDataToArray(colorHeight * colorWidth * 4, original.data, ColorImageFormat_Bgra);
        Mat copy = original.clone();        //

        while (myBodyReader->AcquireLatestFrame(&myBodyFrame) != S_OK); //
        IBody** myBodyArr = new IBody * [myBodyCount];       //
        for (int i = 0; i < myBodyCount; i++)
            myBodyArr[i] = nullptr;

        if (myBodyFrame->GetAndRefreshBodyData(myBodyCount, myBodyArr) == S_OK)     //
            for (int i = 0; i < myBodyCount; i++)
            {


                BOOLEAN     result = true;
                if (myBodyArr[i]->get_IsTracked(&result) == S_OK && result) //
                {

                    //cout << "Detection is work!" << endl;
                    Joint   myJointArr[JointType_Count];

                    if (myBodyArr[i]->GetJoints(JointType_Count, myJointArr) == S_OK)   //
                    {

                        draw(copy, myJointArr[JointType_Neck], myJointArr[JointType_Head], myMapper, 0);    // 0 = head
                        draw(copy, myJointArr[JointType_Neck], myJointArr[JointType_SpineShoulder], myMapper, 1);   // Shoulder Center or Spine Shoulder = 1

                        draw(copy, myJointArr[JointType_SpineShoulder], myJointArr[JointType_ShoulderLeft], myMapper, 3);   // Shoulder Left = 3
                        draw(copy, myJointArr[JointType_SpineShoulder], myJointArr[JointType_SpineMid], myMapper, 8);   // Spine Mid = 8
                        draw(copy, myJointArr[JointType_SpineShoulder], myJointArr[JointType_ShoulderRight], myMapper, 2);  // Shoulder Right = 2

                        draw(copy, myJointArr[JointType_ShoulderLeft], myJointArr[JointType_ElbowLeft], myMapper, 5);   // Elbow Left = 5
                        draw(copy, myJointArr[JointType_SpineMid], myJointArr[JointType_SpineBase], myMapper, 9);   // Hip Center or Spine Base = 9
                        draw(copy, myJointArr[JointType_ShoulderRight], myJointArr[JointType_ElbowRight], myMapper, 4);  // Elbow Right = 4

                        draw(copy, myJointArr[JointType_ElbowLeft], myJointArr[JointType_WristLeft], myMapper, 7);  // Wrist Left = 7
                        draw(copy, myJointArr[JointType_SpineBase], myJointArr[JointType_HipLeft], myMapper, 11); // Hip Left = 11
                        draw(copy, myJointArr[JointType_SpineBase], myJointArr[JointType_HipRight], myMapper, 10);  // Hip Right = 10
                        draw(copy, myJointArr[JointType_ElbowRight], myJointArr[JointType_WristRight], myMapper, 6);    // Wrist Right = 6

                        draw(copy, myJointArr[JointType_WristLeft], myJointArr[JointType_ThumbLeft], myMapper, 16);
                        draw(copy, myJointArr[JointType_WristLeft], myJointArr[JointType_HandLeft], myMapper, 16);
                        draw(copy, myJointArr[JointType_HipLeft], myJointArr[JointType_KneeLeft], myMapper, 13);    // Knee Left = 13
                        draw(copy, myJointArr[JointType_HipRight], myJointArr[JointType_KneeRight], myMapper, 12);  // Knee Right = 12
                        draw(copy, myJointArr[JointType_WristRight], myJointArr[JointType_ThumbRight], myMapper, 16);
                        draw(copy, myJointArr[JointType_WristRight], myJointArr[JointType_HandRight], myMapper, 16);

                        draw(copy, myJointArr[JointType_HandLeft], myJointArr[JointType_HandTipLeft], myMapper, 16);
                        draw(copy, myJointArr[JointType_KneeLeft], myJointArr[JointType_AnkleLeft], myMapper, 15);   // Foot Left = 15
                        draw(copy, myJointArr[JointType_KneeRight], myJointArr[JointType_AnkleRight], myMapper, 14); // Foot Right = 14
                        draw(copy, myJointArr[JointType_HandRight], myJointArr[JointType_HandTipRight], myMapper, 16);

                    }
                }
            }



        delete[]myBodyArr;
        myBodyFrame->Release();
        myColorFrame->Release();

        startWindowThread();
        imshow("TEST", copy);

        if (waitKey(33) == VK_ESCAPE || banderaTimer == true)
            banderaStop = true;

    }

    //banderaStop = false;
    timer->stop();
    ui->spinBox->setEnabled(true);
    ui->comboBox->setEnabled(true);

    myMapper->Release();

    myDescription->Release();
    myColorReader->Release();
    myColorSource->Release();

    myBodyReader->Release();
    myBodySource->Release();
    mySensor->Close();
    mySensor->Release();

    banderaStartTimer = false;
    cameraOpenFlag = false;
    //cap.release();

}

void MainWindow::createFile()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save file");

    // guardo nombre del archivo
    fileName = filename.toLocal8Bit().constData();
    fileName += ".txt";

    saveData(fileName);
}

void MainWindow::createPatient(){

    QString foldername = QFileDialog::getSaveFileName(this, "Create");
    QDir().mkdir(foldername);
    patientData->getPath(foldername.toLocal8Bit().constData());

    // crea archivo de data
    std::string pathName = patientData->returnPath() + "/DATA.txt";
    std::ofstream outputFile(pathName.c_str());
    try{
        if (!outputFile){
            throw MiExcepcion( string( "Error creando el archivo!!!") );     // El archivo de datos no existe!
        }
    }
    catch(MiExcepcion &ex){
        QMessageBox messageBox;
        QString stringError = QString::fromStdString(ex.what());
        messageBox.warning(0,"Error", stringError);
        messageBox.setFixedSize(500,200);
        return;
    }
    outputFile.close();


}

void MainWindow::saveData(const std::string& name)
{

    std::ofstream outputFile(name.c_str(), std::fstream::app);
    // abro archivo
    try{
        if (!outputFile){
            throw MiExcepcion( string( "El archivo " + name + " no existe!") );     // El archivo de datos no existe!
        }
    }
    catch(MiExcepcion &ex){
        QMessageBox messageBox;
        QString stringError = QString::fromStdString(ex.what());
        messageBox.warning(0,"Error", stringError);
        messageBox.setFixedSize(500,200);
        return;
    }

    outputFile << *prueba << std::endl;
    outputFile << '\n';
    outputFile.close();

}

void MainWindow::saveDataSlot()
{
    if (fileName.size() == 0)
        createFile();
    else saveData(fileName);
}

void MainWindow::openData()
{
    // Obtener la ruta del archivo
    QString filename = QFileDialog::getOpenFileName(this, "Open file");

    // guardo nombre del archivo
    fileName = filename.toLocal8Bit().constData();

    // guardo datos
    //pushBackData(fileName);
}

void MainWindow::takeName()
{
    ui->name->setStyleSheet("background-color: rgb(109,185,102)");
    patientData->getName(ui->name->text().toLocal8Bit().constData());
}

void MainWindow::takeSurname()
{
    ui->surname->setStyleSheet("background-color: rgb(109,185,102)");
    patientData->getSurname(ui->surname->text().toLocal8Bit().constData());
}

void MainWindow::takeAge()
{
    ui->age->setStyleSheet("background-color: rgb(109,185,102)");
    patientData->getAge(ui->age->text().toInt());
}

void MainWindow::takeHeight()
{
    ui->height->setStyleSheet("background-color: rgb(109,185,102)");
    patientData->getHeight(ui->height->text().toFloat());
}

void MainWindow::takeWeight()
{
    ui->weight->setStyleSheet("background-color: rgb(109,185,102)");
    patientData->getWeight(ui->weight->text().toFloat());
}

void MainWindow::GetTestTitle()
{
   ventana2->setModal(true);
   ventana2->show();  // es lo mismo que ventana1-> setVisible(true);
}

void MainWindow::New_Test()
{
    prueba->getTitle(ventana2->returnTitle());
    patientData->addTest(ventana2->returnTitle()); // agrega una prueba al paciente

    // cant de pruebas del paciente
    refreshComboBox(patientData->returnCantTest());

    // change label and current combobox
    ui->testName->clear();
    currentTestText = QString::fromStdString(patientData->returnTestTitle(patientData->returnCantTest()-1));
    ui->testName->setText(currentTestText);

    ui->comboBox->setCurrentIndex(patientData->returnCantTest()-1);

}

void MainWindow::changeCurrentBox(int i)
{
    ui->testName->clear();
    if (i>-1) {
        currentTestText = QString::fromStdString(patientData->returnTestTitle(i));
        ui->testName->setText(currentTestText);
    }
}
