#ifndef SOLICITUD_ADOPCION_H
#define SOLICITUD_ADOPCION_H
#include <iostream>

enum class EstadoSolicitud {
    Pendiente,
    Confirmada,
    Cancelada,
    Devuelta
};

class SolicitudAdopcion{
    private:
    int id;
    int idAdoptante;
    int idAnimal;
    EstadoSolicitud estado;

    public:
    SolicitudAdopcion();
    SolicitudAdopcion(int ide, int idadop, int idanim);

    int getId() const;
    int getIdAdoptante() const;
    int getIdAnimal() const;
    EstadoSolicitud getEstado() const;
    void setEstado(EstadoSolicitud nuevo);
    void mostrarInfo() const;
};

#endif // evita errores de multiples include