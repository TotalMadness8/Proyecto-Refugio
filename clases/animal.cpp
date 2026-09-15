#include <iostream>
#include <string>

enum class EstadoDeSalud
{
    Saludable,
    EnRecuperacion,
    Enfermo
};

class Animal
{
protected:
    int id;
    std::string nombre;
    int edad;
    bool adopcion = false;
    EstadoDeSalud estado;

    public:

    Animal(int ide, std::string nom, bool adopt, EstadoDeSalud est) : id(ide), nombre(nom), adopcion(adopt), estado(est){
        id = ide;
        nombre = nom;
        adopcion = adopt;
        estado = est;
    }
};