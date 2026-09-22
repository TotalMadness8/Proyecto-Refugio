#ifndef GATO_H
#define GATO_H
#include <iostream>
#include "animal.h"

enum class Condicion {
    Exterior,
    Interior
};

class Gato : public Animal {
    private:
    std::string pelaje;
    Condicion condicion;

    public:

    Gato(int ide, std::string nom, int age, bool adopt, EstadoDeSalud est, std::string pelaj, Condicion cond); //Constructor

    void mostrarInfo() const override;  //Heredado de Animal
    
};

#endif