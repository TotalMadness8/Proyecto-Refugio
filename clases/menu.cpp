#include "menu.h"
#include <iostream>
#include <cstdlib>           // std::exit
#include "perro.h"
#include "gato.h"
#include "adoptante.h"
#include "solicitudAdopcion.h"
#include "coleccion.h"
#include "excepciones.h"

// Funciones de entrada

std::string leerTexto(const std::string& msg) {
    std::cout << msg;
    std::string linea;
    if (!std::getline(std::cin, linea)) {
        std::cout << "\nEntrada cerrada. Saliendo.\n";
        std::exit(0);
    }
    return linea;
}

int leerEntero(const std::string& msg) {
    while (true) {
        std::string linea = leerTexto(msg);
        try {
            std::size_t pos = 0;
            int valor = std::stoi(linea, &pos);      // lanza invalid_argument si no es un numero
            if (pos == linea.size()) return valor; 
        } catch (const std::exception&) {
        }
        std::cout << "Entrada invalida, por favor, ingrese un numero entero.\n";
    }
}

// Pide un entero y repite hasta que este entre min y max (del menu)
int leerOpcion(const std::string& msg, int min, int max) {
    while (true) {
        int v = leerEntero(msg);
        if (v >= min && v <= max) return v;
        std::cout << "Valor fuera de rango, Ingrese una opcion del menu, (entre " << min << " y " << max << ")." << ".\n";
    }
}

EstadoDeSalud leerEstadoSalud() {
    int o = leerOpcion("Ingrese el estado de salud del animal. | -> | 1. Saludable, 2. En recuperacion, 3. Enfermo: ", 1, 3);
    if (o == 1) return EstadoDeSalud::Saludable;
    if (o == 2) return EstadoDeSalud::EnRecuperacion;
    return EstadoDeSalud::Enfermo;
}

// Funciones del Menu

void registrarPerro(Refugio& r) {
    std::string nombre = leerTexto("Ingrese el nombre del perro: ");
    int edad = leerOpcion("Ingrese la edad: ", 0, 50);
    EstadoDeSalud salud = leerEstadoSalud();
    std::string raza = leerTexto("Ingrese la raza: ");
    int t = leerOpcion("Que tamanio tiene? | -> | 1. Chico, 2. Mediano, 3. Grande: ", 1, 3);
    Tamanio tam = (t == 1) ? Tamanio::Chico : (t == 2) ? Tamanio::Mediano : Tamanio::Grande;

    Perro p(nombre, edad, false, salud, raza, tam);
    int idNuevo = r.registrarAnimal(p);
    std::cout << "Perro registrado!\n" 
              << "ID del perro: " << idNuevo << ".\n";
}

void registrarGato(Refugio& r) {
    std::string nombre = leerTexto("Ingrese el nombre del gato: ");
    int edad = leerOpcion("Ingrese la edad: ", 0, 40);
    EstadoDeSalud salud = leerEstadoSalud();
    std::string pelaje = leerTexto("De que color es su pelaje?: ");
    int c = leerOpcion("Es un gato de interior o exterior? | -> | 1. Interior, 2. Exterior: ", 1, 2);
    Condicion cond = (c == 1) ? Condicion::Interior : Condicion::Exterior;

    Gato g(nombre, edad, false, salud, pelaje, cond);
    int idNuevo = r.registrarAnimal(g);
    std::cout << "Gato registrado!\n" 
              << "ID del gato: " << idNuevo << ".\n";
}

void registrarAdoptante(Refugio& r) {
    int id = leerEntero("Ingrese la ID del adoptante: ");
    std::string nombre = leerTexto("Ingrese el nombre del adoptante: ");
    std::string contacto = leerTexto("Ingrese un metodo de contacto (correo / telefono): ");
    int v = leerOpcion("Ingrese la situacion de vivienda | -> | 1. Casa, 2. Departamento: ", 1, 2);
    Tipodevivienda tipo = (v == 1) ? Tipodevivienda::Casa : Tipodevivienda::Departamento;

    r.registrarAdoptante(Adoptante(id, nombre, contacto, tipo));
    std::cout << "Adoptante registrado!\n";
}

void buscarPorId(Refugio& r) {
    int id = leerEntero("Ingrese el ID del animal que quiere buscar: ");
    Animal& a = r(id);           // operador()(int): busca por ID, lanza NoEncontradoException si no esta
    a.mostrarInfo();
    if (!a)                      // operador! = "no disponible"
        std::cout << "(Este animal NO esta disponible para adopcion)\n";
}

void verPorPosicion(Refugio& r) {
    int pos = leerEntero("Ingrese la posicion del arreglo que quiera consultar (0 = primera posicion): ");
    r[pos].mostrarInfo();        // operator[](int): lanza std::out_of_range si la posicion no existe
}

void crearSolicitud(Refugio& r) {
    int idAdop = leerEntero("ID del adoptante: ");
    int idAnim = leerEntero("ID del animal: ");
    int idSol = r.crearSolicitud(idAdop, idAnim);
    std::cout << "Solicitud creada!\n"
              <<"ID de la solicitud: " << idSol << ".\n";
}

void mostrarInstancias() {
    std::cout << "Cantidad de 'Coleccion<Adoptante>' activas:        " << Coleccion<Adoptante>::getInstancias() << "\n"
              << "Cantidad de 'Coleccion<SolicitudAdopcion>' activas: " << Coleccion<SolicitudAdopcion>::getInstancias() << "\n";
}

void mostrarMenu() {
    std::cout << "\n===== REFUGIO ANGELITOS =====\n"
              << "---------------------------------------\n"
              << "===== FUNCIONES DEL REFUGIO =====\n"
              << " 1. [Registrar un perro]\n"
              << " 2. [Registrar un gato]\n"
              << " 3. [Listar todos los animales del refugio]\n"
              << " 4. [Listar solo los animales disponibles]\n"
              << " 5. [Registrar un adoptante]\n"
              << " 6. [Buscar animal por ID]\n"
              << " 7. [Crear una solicitud de adopcion]\n"
              << " 8. [Confirmar una solicitud de adopcion]\n"
              << " 9. [Cancelar una solicitud de adopcion]\n"
              << "10. [Devolver un animal]\n"
              << "11. [Mostrar todas las solicitudes]\n"
              << "12. [Mostrar historial de adopciones / devoluciones]\n"
              << "============ MISCELANEO =============\n"
              << "13. [Ver animal por posicion (operator[])\n"
              << "14. [Ver instancias de Coleccion (miembro estatico)]\n"
              << " 0. [Salir del sistema]\n";
}