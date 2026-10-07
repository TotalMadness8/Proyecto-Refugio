#ifndef MENU_H
#define MENU_H
#include <string>
#include "refugio.h"
#include "animal.h"

std::string leerTexto(const std::string& msg);

int leerEntero(const std::string& msg);

int leerOpcion(const std::string& msg, int min, int max);

EstadoDeSalud leerEstadoSalud();

void registrarPerro(Refugio& r);

void registrarGato(Refugio& r);

void registrarAdoptante(Refugio& r);

void buscarPorId(Refugio& r);

void verPorPosicion(Refugio& r);

void crearSolicitud(Refugio& r);

void mostrarInstancias();

void mostrarMenu();

#endif