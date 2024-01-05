/*
 * articulacion.cpp
 *
 *  Created on: 29 jun. 2022
 *      Author: vittorio
 */

#include "articulacion.h"

/*articulacion::articulacion(int artNum)
{
    //id = artNum;
    //habilitado = true;
}*/

void Articulacion::guardaDatos(float X, float Y, float Z)
{
    x.push_back(X);
    y.push_back(Y);
    z.push_back(Z);
}

std::vector<float>::iterator Articulacion::devuelveBegin(char coord)
{
    if (coord == 'x') return x.begin();
    if (coord == 'y') return y.begin();
    if (coord == 'z') return z.begin();
    //if (coord == 't') return t.begin();
}

std::vector<float>::iterator Articulacion::devuelveEnd(char coord)
{
    if (coord == 'x') return x.end();
    if (coord == 'y') return y.end();
    if (coord == 'z') return z.end();
    //if (coord == 't') return t.end();
}

std::ofstream& operator<<(std::ofstream& os, const Articulacion& art)
{

    std::vector<float>::const_iterator ix, iy, iz;
    std::vector<int>::const_iterator it;

    os << "marcador: " << art.id << '\n';

    //  Escribe posiciones x y z
    os << "posiciones x y z" << '\n';

    iy = art.y.begin();
    iz = art.z.begin();
    it = art.t.begin();
    for (ix = art.x.begin(); ix != art.x.end(); ix++){
        std::string linea;
        std::ostringstream osx, osy, osz, ost;

        osx << *ix;
        linea = osx.str();
        linea += '\t';

        osy << *iy;
        linea += osy.str();
        linea += '\t';

        osz << *iz;
        linea += osz.str();
        linea += '\t';

        ost << *it;
        linea += ost.str();

        //os << *ix << '\t' << *iy << '\t' << *iz << '\t' << *it << '\n';

        os << linea << '\n';

        iy++;
        iz++;
        it++;
    }

    os << std::endl;

    //os << '\n';

    return os;
}


