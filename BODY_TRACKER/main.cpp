/*
 * main.cpp
 *
 *  Created on: 21 jun. 2022
 *      Author: vittorio
 */


#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
