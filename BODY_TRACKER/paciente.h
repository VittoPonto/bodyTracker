/*
 * paciente.h
 *
 *  Created on: 2/7 jul. 2022
 *      Author: vittorio
 */

#ifndef PACIENTE_H
#define PACIENTE_H

#include "test.h"
#include "MiExcepcion.h"
#include <QMessageBox>
#include <iostream>

class Paciente
{
public:
    Paciente(std::string n, std::string s, int a, float h, float w, int cantT);
    Paciente();
    ~Paciente();

    // in datos
    void getName(std::string n){name = n;};
    void getSurname(std::string a){surname = a;};
    void getAge(int a){age = a;};
    void getHeight(float h){height = h;};
    void getWeight(float w){weight = w;};
    void addTest(std::string);

    // get de test
    void TestName(std::string, int);
    // returns de test
    std::string returnTestTitle(int id){return pruebas[id]->returnTitle();};

    // returns
    int returnCantTest(){return cantTest;};

    // sobrecarga de operadores
    friend std::ofstream& operator<<(std::ofstream&, const Paciente&);

    // guardado
    void guardaPaciente();
    void getPath(const std::string s){path = s;};
    std::string returnPath(){return path;};

private:
    std::string name, surname;
    int age;
    float height, weight;
    int cantTest;
    Test *pruebas[10];
    // path del paciente
    std::string path;

};

#endif // PACIENTE_H
