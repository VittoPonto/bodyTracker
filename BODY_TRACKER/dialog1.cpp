/*
 * dialog1.cpp
 *
 *  Created on: 24 jun. 2022
 *      Author: vittorio
 */

#include "dialog1.h"
#include "ui_dialog1.h"
#include <QCheckBox>
#include <QDialog>
#include "mainwindow.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
    this->setWindowTitle("Select Markers");

    // simboliza punto rojo en cada marcador seleccionado
    QObject::connect(ui->m_head, SIGNAL(stateChanged(int)),this,SLOT(paintLabel1(int)));
    QObject::connect(ui->m_shldC, SIGNAL(stateChanged(int)),this,SLOT(paintLabel2(int)));
    QObject::connect(ui->m_shldR, SIGNAL(stateChanged(int)),this,SLOT(paintLabel3(int)));
    QObject::connect(ui->m_shldL, SIGNAL(stateChanged(int)),this,SLOT(paintLabel4(int)));
    QObject::connect(ui->m_elbowR, SIGNAL(stateChanged(int)),this,SLOT(paintLabel5(int)));
    QObject::connect(ui->m_elbowL, SIGNAL(stateChanged(int)),this,SLOT(paintLabel6(int)));
    QObject::connect(ui->m_wristR, SIGNAL(stateChanged(int)),this,SLOT(paintLabel7(int)));
    QObject::connect(ui->m_wristL, SIGNAL(stateChanged(int)),this,SLOT(paintLabel8(int)));
    QObject::connect(ui->m_spine, SIGNAL(stateChanged(int)),this,SLOT(paintLabel9(int)));
    QObject::connect(ui->m_hipC, SIGNAL(stateChanged(int)),this,SLOT(paintLabel10(int)));
    QObject::connect(ui->m_hipR, SIGNAL(stateChanged(int)),this,SLOT(paintLabel11(int)));
    QObject::connect(ui->m_hipL, SIGNAL(stateChanged(int)),this,SLOT(paintLabel12(int)));
    QObject::connect(ui->m_kneeR, SIGNAL(stateChanged(int)),this,SLOT(paintLabel13(int)));
    QObject::connect(ui->m_kneeL, SIGNAL(stateChanged(int)),this,SLOT(paintLabel14(int)));
    QObject::connect(ui->m_footR, SIGNAL(stateChanged(int)),this,SLOT(paintLabel15(int)));
    QObject::connect(ui->m_footL, SIGNAL(stateChanged(int)),this,SLOT(paintLabel16(int)));

    // opcion para marcar todos los marcadores
    QObject::connect(ui->all, SIGNAL(stateChanged(int)),this,SLOT(paintLabelAll(int)));

    //  al terminar el dialogo chequea estado final de los marcadores
    QObject::connect(this, SIGNAL(accepted()), this, SLOT(checkMarkersList()));
}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::setMarkersFalse(){
    for (int i=0; i<16; i++)
        markers[i]=false;
}

void Dialog1::checkMarkersList()
{
    setMarkersFalse();
    if (ui->m_head->checkState())   markers[0]=true;
    if (ui->m_shldC->checkState())   markers[1]=true;
    if (ui->m_shldR->checkState())   markers[2]=true;
    if (ui->m_shldL->checkState())   markers[3]=true;
    if (ui->m_elbowR->checkState())   markers[4]=true;
    if (ui->m_elbowL->checkState())   markers[5]=true;
    if (ui->m_wristR->checkState())   markers[6]=true;
    if (ui->m_wristL->checkState())   markers[7]=true;

    if (ui->m_spine->checkState())   markers[8]=true;
    if (ui->m_hipC->checkState())   markers[9]=true;
    if (ui->m_hipR->checkState())   markers[10]=true;
    if (ui->m_hipL->checkState())   markers[11]=true;
    if (ui->m_kneeR->checkState())   markers[12]=true;
    if (ui->m_kneeL->checkState())   markers[13]=true;
    if (ui->m_footR->checkState())   markers[14]=true;
    if (ui->m_footL->checkState())   markers[15]=true;
}

void Dialog1::paintLabel1(int i){
    // i = 2 es checkbox seleccionado; i = 0 es desseleccionado
    if (i == 2)
        ui->led1->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led1->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel2(int i){
    if (i == 2)
        ui->led2->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led2->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel3(int i){
    if (i == 2)
        ui->led3->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led3->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel4(int i){
    if (i == 2)
        ui->led4->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led4->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel5(int i){
    if (i == 2)
        ui->led5->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led5->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel6(int i){
    if (i == 2)
        ui->led6->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led6->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel7(int i){
    if (i == 2)
        ui->led7->setStyleSheet("background-color: red; border-radius: 4px; min-height: 8px; min-width: 8px;");
    else ui->led7->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel8(int i){
    if (i == 2)
        ui->led8->setStyleSheet("background-color: red; border-radius: 4px; min-height: 8px; min-width: 8px;");
    else ui->led8->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel9(int i){
    if (i == 2)
        ui->led9->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led9->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel10(int i){
    if (i == 2)
        ui->led10->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led10->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel11(int i){
    if (i == 2)
        ui->led11->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led11->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel12(int i){
    if (i == 2)
        ui->led12->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led12->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel13(int i){
    if (i == 2)
        ui->led13->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led13->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel14(int i){
    if (i == 2)
        ui->led14->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led14->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel15(int i){
    if (i == 2)
        ui->led15->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led15->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabel16(int i){
    if (i == 2)
        ui->led16->setStyleSheet("background-color: red; border-radius: 5px; min-height: 10px; min-width: 10px;");
    else ui->led16->setStyleSheet("background-color: rgba(0,0,0,0%)");
}

void Dialog1::paintLabelAll(int i){
    if (i == 2){
        ui->m_head->setChecked(true);
        ui->m_shldC->setChecked(true);
        ui->m_shldR->setChecked(true);
        ui->m_shldL->setChecked(true);
        ui->m_elbowR->setChecked(true);
        ui->m_elbowL->setChecked(true);
        ui->m_wristR->setChecked(true);
        ui->m_wristL->setChecked(true);
        ui->m_spine->setChecked(true);
        ui->m_hipC->setChecked(true);
        ui->m_hipR->setChecked(true);
        ui->m_hipL->setChecked(true);
        ui->m_kneeR->setChecked(true);
        ui->m_kneeL->setChecked(true);
        ui->m_footR->setChecked(true);
        ui->m_footL->setChecked(true);
    }
    else{
        ui->m_head->setChecked(false);
        ui->m_shldC->setChecked(false);
        ui->m_shldR->setChecked(false);
        ui->m_shldL->setChecked(false);
        ui->m_elbowR->setChecked(false);
        ui->m_elbowL->setChecked(false);
        ui->m_wristR->setChecked(false);
        ui->m_wristL->setChecked(false);
        ui->m_spine->setChecked(false);
        ui->m_hipC->setChecked(false);
        ui->m_hipR->setChecked(false);
        ui->m_hipL->setChecked(false);
        ui->m_kneeR->setChecked(false);
        ui->m_kneeL->setChecked(false);
        ui->m_footR->setChecked(false);
        ui->m_footL->setChecked(false);
    }
}
