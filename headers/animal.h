#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>

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

    Animal(int ide, std::string nom, int age, bool adopt, EstadoDeSalud est);
};

#endif              //Evita errores de include multiples