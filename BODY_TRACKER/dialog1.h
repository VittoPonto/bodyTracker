/*
 * dialog1.h
 *
 *  Created on: 24 jun. 2022
 *      Author: vittorio
 */

#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>

namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = nullptr);
    ~Dialog1();
    // retorna valor del marcador
    bool ReturnMarker(int i){return markers[i];};

private:
    Ui::Dialog1 *ui;
    bool markers[16]={false};
    // setea todos los marcadores en falso al inicio
    void setMarkersFalse();

public slots:
    // chequea estado final de los marcadores
    void checkMarkersList();
    // chequea cambio de estado de los marcadores; muestra marcador en imagen
    void paintLabel1(int);
    void paintLabel2(int);
    void paintLabel3(int);
    void paintLabel4(int);
    void paintLabel5(int);
    void paintLabel6(int);
    void paintLabel7(int);
    void paintLabel8(int);
    void paintLabel9(int);
    void paintLabel10(int);
    void paintLabel11(int);
    void paintLabel12(int);
    void paintLabel13(int);
    void paintLabel14(int);
    void paintLabel15(int);
    void paintLabel16(int);

    void paintLabelAll(int);

};

#endif // DIALOG1_H
