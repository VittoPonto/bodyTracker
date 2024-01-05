/*
 * articulacion.h
 *
 *  Created on: 29 jun. 2022
 *      Author: vittorio
 */

#ifndef ARTICULACION_H
#define ARTICULACION_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>


class Articulacion
{
public:
    Articulacion(int i){id = i;};
    ~Articulacion(){};

    // gets
    void guardaDatos(float X, float Y, float Z);
    void getTime(int time){t.push_back(time);};

    // devuelve iteradores de los contenedores
    // algunos métodos no se usan pero se crean para futuros usos (para graficas)
    std::vector<float>::iterator devuelveBegin(char);
    std::vector<float>::iterator devuelveEnd(char);
    std::vector<int>::iterator devuelveBeginTime(){return t.begin();};
    std::vector<int>::iterator devuelveEndTime(){return t.end();};

    //std::string int2string(const int& );
    //std::string float2string(const float& );

    // returns
    int returnID(){return id;};

    // sobrecarga para guardado en archivo
    friend std::ofstream& operator<<(std::ofstream&, const Articulacion&);


private:
    // crear vector con las coordenadas x y z
    // tiempo t
    std::vector<float> x, y, z;
    std::vector<int> t;

    // identificador id ; reconoce de que articulacion trata
    int id;

};

/*std::string intTOstring(const int& number)
{
    std::ostringstream oss;
    oss << number;
    return oss.str();
}

std::string floatTOstring(const float& number)
{
    std::ostringstream oss;
    oss << number;
    return oss.str();
}*/

#endif // ARTICULACION_H

