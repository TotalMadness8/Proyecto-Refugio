#ifndef REFUGIO_H
#define REFUGIO_H
#include <iostream>
#include <string>
#include "animal.h"
#include "adoptante.h"
#include "solicitudAdopcion.h"
#include "coleccion.h"
#include "excepciones.h"


class Refugio {
private:
std::string nombre;

    Animal** animales;               // array dinamico de punteros a Animal
    int cantAnimales;
    int capAnimales;

    Coleccion<Adoptante> adoptantes;
    Coleccion<SolicitudAdopcion> solicitudes;

    int proximoIdSolicitud;          // los IDs de solicitud los genera el refugio
    int proximoIdAnimal;
    // Metodos internos
    void agrandarAnimales();
    int indiceAnimal(int id) const;       // -1 si no existe
    int indiceAdoptante(int id) const;
    int indiceSolicitud(int id) const;

    public:
    Refugio();                                              // por defecto
    Refugio(const std::string& nom, int capacidadInicial);  // parametrizado
    Refugio(const Refugio& otro);                           // copia profunda
    Refugio& operator=(const Refugio& otro);
    ~Refugio();                                             // libera todo
    
    Animal& operator()(int id) const;       //acceso por posicion
    Animal& operator[](int pos) const;      //busca por ID
    
    // Animales
    int registrarAnimal(const Animal& a);
    void listarAnimales() const;             
    void listarDisponibles() const;
    Animal* buscarAnimal(int id) const;      // nullptr si no existe (no liberar este puntero)

    // Adoptantes
    void registrarAdoptante(const Adoptante& ad);
    const Adoptante* buscarAdoptante(int id) const;
    void listarAdoptantes() const;

    // Solicitudes
    int  crearSolicitud(int idAdoptante, int idAnimal);   // devuelve el ID de la nueva solicitud
    void confirmarSolicitud(int idSolicitud);
    void cancelarSolicitud(int idSolicitud);
    void devolverAnimal(int idAnimal);
    void mostrarSolicitudes() const;
    void mostrarHistorial() const;

    // Getters
    std::string getNombre() const;
    int getCantAnimales() const;
    int getCantAdoptantes() const;
    int getCantSolicitudes() const;

};

#endif