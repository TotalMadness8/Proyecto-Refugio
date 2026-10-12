#include "gato.h"

Gato::Gato(std::string nom, int age, bool adopt, EstadoDeSalud est, std::string pelaj, Condicion cond) 
    : Animal(nom, age, adopt, est), pelaje(pelaj), condicion(cond){}                                           //Parametrizado


void Gato::mostrarInfo() const {
    std::cout << "\n--------------------------------------------------------------------------------------------------------------------\n [Gato] ";
    Animal::mostrarInfo();                  //Muestra la info general del animal
    std::cout << "\n Pelaje: " << pelaje
              << " | Tipo: " << (condicion == Condicion::Interior ? "Interior" : "Exterior") <<
               "\n--------------------------------------------------------------------------------------------------------------------\n";        //Muestra la info especifica del gato
}

Animal* Gato::clonar() const { return new Gato(*this); }
