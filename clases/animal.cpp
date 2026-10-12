#include "animal.h"

Animal::Animal() : id(0), nombre("Sin nombre"), edad(0), adopcion(false), estado(EstadoDeSalud::Saludable) {} // Por defecto

Animal::Animal(std::string nom, int age, bool adopt, EstadoDeSalud est)
    : id(0), nombre(nom), edad(age), adopcion(adopt), estado(est) {} // Parametrizado

Animal::Animal(const Animal &otro)
    : id(otro.id), nombre(otro.nombre), edad(otro.edad), adopcion(otro.adopcion), estado(otro.estado) {} // Copia

Animal::~Animal() {} // Destructor

// Metodos
int Animal::getId() const { return id; } // Devuelve ID

std::string Animal::getNombre() const { return nombre; } // Devuelve Nombre del animal

EstadoDeSalud Animal::getEstado() const { return estado; }

bool Animal::estaAdoptado() const { return adopcion; } // Devuelve estado de adopción

void Animal::setAdopcion(bool valor) { adopcion = valor; } // Cambia el estado de adopción

void Animal::setId(int nuevoId) { id = nuevoId; }

void Animal::setSalud(EstadoDeSalud nuevoEstado) { estado = nuevoEstado; }

//Operadores
bool Animal::operator==(const Animal& otro) const { return id == otro.id; }

bool Animal::operator!() const { return adopcion; }

void Animal::mostrarInfo() const
{
    std::cout << "Nombre: " << nombre << " | ID: " << id << " | Edad: " << edad << " | Estado de adopcion: "
              << (adopcion ? "Adoptado" : "Disponible") << " | Estado de salud: ";

    switch (estado)
    {
    case EstadoDeSalud::Saludable:      std::cout << "Saludable";       break;
    case EstadoDeSalud::EnRecuperacion: std::cout << "En Recuperacion"; break;
    case EstadoDeSalud::Enfermo:        std::cout << "Enfermo";         break;
    }
}
