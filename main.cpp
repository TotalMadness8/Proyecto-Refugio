#include "adoptante.h"
#include "animal.h"
#include "refugio.h"
#include "solicitudAdopcion.h"
#include "gato.h"
#include "perro.h"
#include <iostream>


int main(){
    Refugio refugio("Refugio Angelitos", 2);

    Perro perro1(1,"Luna",8,true,EstadoDeSalud::Saludable,"Dalmata",Tamanio::Grande);
    Gato  gato1(2,"Michi",3,false,EstadoDeSalud::Saludable,"Naranja",Condicion::Interior);
    Perro perro2(3,"Toby",2,false,EstadoDeSalud::EnRecuperacion,"Mestizo",Tamanio::Chico);

    Adoptante adopt1(1,"Manuel","888",Tipodevivienda::Casa);

    refugio.registrarAnimal(perro1);
    refugio.registrarAnimal(gato1);
    refugio.registrarAnimal(perro2); 

    refugio.registrarAdoptante(adopt1);

    int s1 = refugio.crearSolicitud(1, 1);
    int s2 = refugio.crearSolicitud(1, 1);


    refugio.confirmarSolicitud(s1);
    refugio.confirmarSolicitud(s2);

    std::cout << "\n-- Todos --\n";      refugio.listarAnimales();
    std::cout << "\n-- Disponibles --\n"; refugio.listarDisponibles();
    std::cout << "\n-- Solicitudes --\n"; refugio.mostrarSolicitudes();
    std::cout << "\n-- Historial --\n"; refugio.mostrarHistorial();
    std::cout << "\n-- Adoptantes --\n"; refugio.listarAdoptantes();


    return 0;
}