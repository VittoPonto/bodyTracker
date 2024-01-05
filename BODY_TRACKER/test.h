/*
 * test.cpp
 *
 *  Created on: 2/7 jul. 2022
 *      Author: vittorio
 */

#ifndef TEST_H
#define TEST_H

#include <iostream>
#include "articulacion.h"
//#include <fstream>

class Test
{
public:
    Test(int nro);
    Test(){};
    ~Test();

    // crea obj articulacion
    void askForMem(int identif);

    // prueba está cargada o no
    bool returnCarga(){return cargada;};
    void pruebaCargada(bool x){cargada = x;};
   // void cargaDatos();

    // returns
    int returnID(int i){return joint[i]->returnID();};
    int returnCantArt(){return cantArt;};
    std::string returnTitle(){return title;};

    // captura posicicion de la articulacion
    void capturaPos(float,float,float,int,int);
    // captura titulo
    void getTitle(std::string t){title = t;};

    // sobrecarga de operadores
    friend std::ofstream& operator<<(std::ofstream&, const Test&);
    //Test& operator= (const Test&);

private:
    int nroPrueba;
    Articulacion *joint[16];
    int cantArt;
    std::string title;
    bool cargada;
};

#endif // TEST_H



