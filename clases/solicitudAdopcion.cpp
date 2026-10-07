#include "solicitudAdopcion.h"

SolicitudAdopcion::SolicitudAdopcion() : id(0), idAdoptante(0), idAnimal(0), estado(EstadoSolicitud::Pendiente) {}

SolicitudAdopcion::SolicitudAdopcion(int ide, int idAdop, int idAnim, std::string nomAnim, std::string nomAdop)
    : id(ide), idAdoptante(idAdop), idAnimal(idAnim),
         nombreAnimal(nomAnim), nombreAdoptante(nomAdop), estado(EstadoSolicitud::Pendiente) {}

int SolicitudAdopcion::getId() const { return id; }

int SolicitudAdopcion::getIdAdoptante() const { return idAdoptante; }

int SolicitudAdopcion::getIdAnimal() const { return idAnimal; }

EstadoSolicitud SolicitudAdopcion::getEstado() const { return estado; }

void SolicitudAdopcion::setEstado(EstadoSolicitud nuevo) { estado = nuevo; }

void SolicitudAdopcion::mostrarInfo() const
{
    std::cout << "ID Solicitud: " << id << " | Adoptante: " << nombreAdoptante
              << " | Animal: " << nombreAnimal << " | Estado de la solicitud: ";

    switch (estado)
    {
    case EstadoSolicitud::Pendiente:
        std::cout << "Pendiente" << "\n";
        break;

    case EstadoSolicitud::Confirmada:
        std::cout << "Confirmada" << "\n";
        break;

    case EstadoSolicitud::Cancelada:
        std::cout << "Cancelada" << "\n";
        break;

    case EstadoSolicitud::Devuelta:
        std::cout << "Devuelta" << "\n";
        break;
    }
}