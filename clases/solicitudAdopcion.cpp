#include "headers/solicitudAdopcion.h"

SolicitudAdopcion::SolicitudAdopcion() : id(0), idAdoptante(0), idAnimal(0), estado(EstadoSolicitud::Pendiente) {}

SolicitudAdopcion::SolicitudAdopcion(int ide, int idAdop, int idAnim)
    : id(ide), idAdoptante(idAdop), idAnimal(idAnim), estado(EstadoSolicitud::Pendiente) {}

int SolicitudAdopcion::getId() const { return id; }

int SolicitudAdopcion::getIdAdoptante() const { return idAdoptante; }

int SolicitudAdopcion::getIdAnimal() const { return idAnimal; }

EstadoSolicitud SolicitudAdopcion::getEstado() const { return estado; }

void SolicitudAdopcion::setEstado(EstadoSolicitud nuevo) { estado = nuevo; }

void SolicitudAdopcion::mostrarInfo() const {
    std::cout << "Solicitud " << id << " | Adoptante " << idAdoptante
              << " | Animal " << idAnimal << " | " 
              << (estado == EstadoSolicitud::Pendiente ? "Pendiente" : "Devuelta")  << "\n";
}