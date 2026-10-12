#include "adoptante.h"

Adoptante::Adoptante() : id(0), nombre("Sin nombre"), contacto(""), vivienda(Tipodevivienda::Casa) {} // Constructor por defecto

Adoptante::Adoptante(int ide, std::string nom, std::string phone, Tipodevivienda tipo) 
        : id(ide), nombre(nom), contacto(phone), vivienda(tipo) {}                      // Constructor Parametrizado


//Metodos

int Adoptante::getId() const { return id; } // Devuelve la ID del adoptante

std::string Adoptante::getNombre() const { return nombre; } // Devuelve el nombre del adoptante

void Adoptante::mostrarInfo() const
{
    std::cout << "\n--------------------------------------------------------------------------------------------------------------------\n";    
    std::cout << " [Adoptante] Nombre: " << nombre << " | ID: " << id << " | Contacto: " << contacto << "\n Tipo de vivienda: "
              << (vivienda == Tipodevivienda::Casa ? "Casa" : "Departamento") 
              << "\n--------------------------------------------------------------------------------------------------------------------\n";                             // Muestra toda la info del adoptante
}