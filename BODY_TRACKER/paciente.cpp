/*
 * paciente.cpp
 *
 *  Created on: 2/7 jul. 2022
 *      Author: vittorio
 */

#include "paciente.h"


// constructor para cuando el archivo del paciente ya existe
Paciente::Paciente(std::string n, std::string s, int a, float h, float w, int cantT)
{
    name = n;
    surname = s;
    age = a;
    height = h;
    weight = w;
    cantTest = cantT;

    for (int i=0; i<cantT; i++){
       // pruebas = new Test(i);
    }
}

// constructor para cuando se quiere comenzar a trabajar sobre un nuevo paciente
Paciente::Paciente ()
{
    cantTest = 0;
}

Paciente::~Paciente()
{
    for (int i=0; i<cantTest; i++){
        delete pruebas[i];
    }
}

void Paciente::addTest(std::string name)
{
    // hago pedido de memoria para un nuevo Test
    // primer prueba sera prueba con nroPrueba = 0
    pruebas[cantTest] = new Test(cantTest);

    // agrego titulo a la nueva prueba
    TestName(name,cantTest);

    cantTest++;
}

void Paciente::TestName(std::string name, int id)
{
    pruebas[id]->getTitle(name);
}

std::ofstream& operator<<(std::ofstream& os, const Paciente &p)
{
    os << "PATIENT DATA:" << std::endl;

    os << p.name << std::endl;
    os << p.surname << std::endl;
    os << p.age << std::endl;
    os << p.height << std::endl;
    os << p.weight << std::endl;
    os << p.cantTest << std::endl;
    os << std::endl;

    return os;
}

void Paciente::guardaPaciente()
{
    std::string pathName = path + "/DATA.txt";
    std::ofstream outputFile(pathName.c_str());
    try{
        if (!outputFile){
            throw MiExcepcion( std::string( "Error creando el archivo!!!") );     // El archivo de datos no existe!
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
