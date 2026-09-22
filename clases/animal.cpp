#include "headers/animal.h"

Animal::Animal() : id(0), nombre("Sin nombre"), edad(0), adopcion(false), estado(EstadoDeSalud::Saludable) {}           // Por defecto

Animal::Animal(int ide, std::string nom, int age, bool adopt, EstadoDeSalud est)
    : id(ide), nombre(nom), edad(age), adopcion(adopt), estado(est) {}                                                  // Parametrizado

Animal::Animal(const Animal &otro)
    : id(otro.id), nombre(otro.nombre), edad(otro.edad), adopcion(otro.adopcion), estado(otro.estado) {}                // Copia

Animal::~Animal() {}                                                                                                    // Destructor


//Metodos

int Animal::getId() const { return id; }                                                                                //Devuelve ID

std::string Animal::getNombre() const { return nombre; }                                                                //Devuelve Nombre

bool Animal::estaAdoptado() const { return adopcion; }                                                                  //Devuelve estado de adopción

void Animal::setAdopcion(bool valor) { adopcion = valor; }                                                              //Cambia el estado de adopción

void Animal::mostrarInfo() const {
    std::cout << "Nombre: " << nombre << " | ID: " << id << " | Edad: " << edad << " | Estado de adopcion "
         << (adopcion ? "Adoptado" : "Disponible") << " | Estado de salud: "                                            //Muestra toda la info del animal
         << (estado == EstadoDeSalud::Saludable ? "Saludable" : "Enfermo")
         << std::endl;
}
