/*
 * test.cpp
 *
 *  Created on: 2/7 jul. 2022
 *      Author: vittorio
 */

#include "test.h"
#include <QFile>
#include <QMessageBox>
#include "MiExcepcion.h"

Test::Test(int nro)
{
    nroPrueba = nro;
    cantArt = 0;
    cargada = false;
}

Test::~Test()
{
    for (int i=0; i<cantArt; i++){
        delete joint[i];
    }
}

void Test::askForMem(int identif)
{
    joint[cantArt] = new Articulacion(identif);
    cantArt++;
}

void Test::capturaPos(float X, float Y, float Z, int T, int id)
{

    joint[id]->guardaDatos(X,Y,Z);
    joint[id]->getTime(T);

}

std::ofstream& operator<<(std::ofstream& os, const Test &prueba)
{
    os << "PRUEBA N°" << prueba.nroPrueba << '\n' << std::endl;

    for (int j=0; j<prueba.cantArt; j++){
        os << *prueba.joint[j];
    }

    os << std::endl;
    os << std::endl;
    os << std::endl;

    return os;
}

/*Test& Test::operator= (const Test& prueba)
{
    //
}*/

