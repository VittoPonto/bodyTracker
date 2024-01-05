#include "dialog2.h"
#include "ui_dialog2.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    this->setWindowTitle("New test...");

    QObject::connect(this, SIGNAL(accepted()), this, SLOT(saveTitle()));
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::saveTitle()
{
    TestTitle = (ui->lineEdit->text().toLocal8Bit().constData());
}
