#ifndef MIEXCEPCION_H
#define MIEXCEPCION_H

#include <iostream>

class MiExcepcion: public std::runtime_error
{
public:
    MiExcepcion(const std::string& _message)
        : std::runtime_error(_message)
    {}
    ~MiExcepcion(){};

};

#endif // MIEXCEPCION_H
