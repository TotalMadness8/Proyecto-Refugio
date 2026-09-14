#include <iostream>
#include <string>

enum class EstadoDeSalud{
    Saludable, EnRecuperacion, Enfermo
};

class Animal {
    protected:

    int id;
    std::string nombre;
    int edad;
    bool adopcion = false;
    EstadoDeSalud estado;
};