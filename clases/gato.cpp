#include "headers/gato.h"

Gato::Gato(int ide, std::string nom, int age, bool adopt, EstadoDeSalud est, std::string pelaj, Condicion cond) 
    : Animal(ide, nom, age, adopt, est), pelaje(pelaj), condicion(cond){}                                           //Parametrizado


void Gato::mostrarInfo() const {
    std::cout << "[Gato] ";
    
    Animal::mostrarInfo();                  //Muestra la info general del animal
    
    std::cout << " | Pelaje: " << pelaje
              << " | " << (condicion == Condicion::Interior ? "Interior" : "Exterior") << std::endl;        //Muestra la info especifica del gato
}