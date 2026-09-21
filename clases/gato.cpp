#include "headers/gato.h"

Gato::Gato(int ide, std::string nom, int age, bool adopt, EstadoDeSalud est, std::string pelaj, Condicion cond) 
    : Animal(ide, nom, age, adopt, est), pelaje(pelaj), condicion(cond){

    }