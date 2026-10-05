#ifndef REFUGIO_H
#define REFUGIO_H
#include <iostream>
#include "animal.h"
#include "adoptante.h"
#include "solicitudAdopcion.h"


class Refugio {
private:
std::string nombre;

    Animal** animales;               // array dinamico de punteros a Animal
    int cantAnimales;
    int capAnimales;

    Adoptante* adoptantes;           // array dinamico de objetos Adoptante
    int cantAdoptantes;
    int capAdoptantes;

    SolicitudAdopcion* solicitudes;  // array dinamico de objetos SolicitudAdopcion
    int cantSolicitudes;
    int capSolicitudes;

    int proximoIdSolicitud;          // los IDs de solicitud los genera el refugio

    // Metodos internos
    void agrandarAnimales();
    void agrandarAdoptantes();
    void agrandarSolicitudes();
    int indiceAnimal(int id) const;       // -1 si no existe
    int indiceAdoptante(int id) const;
    int indiceSolicitud(int id) const;

    public:
    Refugio();                                              // por defecto
    Refugio(const std::string& nom, int capacidadInicial);  // parametrizado
    Refugio(const Refugio& otro);                           // copia profunda
    ~Refugio();                                             // libera todo
    Refugio& operator=(const Refugio& otro) = delete;      
    
    // Animales
    bool registrarAnimal(const Animal& a);   // guarda una COPIA propia (clonar)
    void listarAnimales() const;             
    void listarDisponibles() const;
    Animal* buscarAnimal(int id) const;      // nullptr si no existe (no liberar este puntero)

    // Adoptantes
    bool registrarAdoptante(const Adoptante& ad);
    Adoptante* buscarAdoptante(int id) const;
    void listarAdoptantes() const;

    // Solicitudes
    int  crearSolicitud(int idAdoptante, int idAnimal);   // devuelve el ID o -1 si falla
    bool confirmarSolicitud(int idSolicitud);
    bool cancelarSolicitud(int idSolicitud);
    bool devolverAnimal(int idAnimal);
    void mostrarSolicitudes() const;
    void mostrarHistorial() const;

    // Getters
    std::string getNombre() const;
    int getCantAnimales() const;
    int getCantAdoptantes() const;
    int getCantSolicitudes() const;

};

#endif