#include "headers/perro.h"

Perro::Perro(int id, std::string nom, int age, bool adopt, EstadoDeSalud est, std::string raz, Tamanio tam)
    : Animal(id, nom, age, adopt, est), raza(raz), size(tam){

    }