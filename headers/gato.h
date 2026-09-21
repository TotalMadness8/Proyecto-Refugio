#include <iostream>
#include "headers/animal.h"

enum class Condicion {
    Exterior,
    Interior
};

class Gato : protected Animal {
    private:
    std::string pelaje;
    Condicion condicion;

Gato(int ide, std::string nom, int age, bool adopt, EstadoDeSalud est, std::string pelaj, Condicion cond); 
    
};