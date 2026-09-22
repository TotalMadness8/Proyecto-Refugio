#include "headers/perro.h"

Perro::Perro(int id, std::string nom, int age, bool adopt, EstadoDeSalud est, std::string raz, Tamanio tam)
    : Animal(id, nom, age, adopt, est), raza(raz), size(tam) { }

void Perro::mostrarInfo() const {
    std::cout << "[Perro] ";
    
    Animal::mostrarInfo();                  //Muestra la info general del animal
    
    std::cout << " | Raza: " << raza
              << " | " << (size == Tamanio::Chico ? "Chico" : "Grande") << std::endl;        //Muestra la info especifica del perro
}