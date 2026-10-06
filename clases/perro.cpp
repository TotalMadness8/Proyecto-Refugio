#include "perro.h"

Perro::Perro(int id, std::string nom, int age, bool adopt, EstadoDeSalud est, std::string raz, Tamanio tam)
    : Animal(id, nom, age, adopt, est), raza(raz), size(tam) {}

void Perro::mostrarInfo() const
{
    std::cout << "[Perro] ";

    Animal::mostrarInfo(); // Muestra la info general del animal

    std::cout << " | Raza: " << raza
              << " | " << "Tamanio: "; // Muestra la info especifica del perro

    switch (size)
    {
    case Tamanio::Chico:    std::cout << "Chico";   break;
    case Tamanio::Mediano:  std::cout << "Mediano"; break;
    case Tamanio::Grande:   std::cout << "Grande";  break;
    }
    std::cout << std::endl;
}

Animal *Perro::clonar() const { return new Perro(*this); }