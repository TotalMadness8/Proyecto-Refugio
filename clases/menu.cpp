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
    while(true){
    std::cout << "\n" << msg;
    std::string linea;
    if (!std::getline(std::cin, linea)) {
        std::cout << "\n Entrada cerrada. Saliendo.\n";
        std::exit(0);
    }
    if(!linea.empty()) return linea;

    std::cout << " [Error] La entrada no puede estar vacia.\n";
}
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
        std::cout << " [Error] Entrada invalida, por favor, ingrese un numero entero.\n";
    }
}

// Pide un entero y repite hasta que este entre min y max (del menu)
int leerOpcion(const std::string& msg, int min, int max) {
    while (true) {
        int v = leerEntero(msg);
        if (v >= min && v <= max) return v;
        std::cout << " [Error] Fuera de rango, Ingrese un valor valido: entre " << min << " y " << max << ".\n";
    }
}

EstadoDeSalud leerEstadoSalud() {
    int o = leerOpcion(" Ingrese el estado de salud del animal. | -> | 1. Saludable, 2. En recuperacion, 3. Enfermo: ", 1, 3);
    if (o == 1) return EstadoDeSalud::Saludable;
    if (o == 2) return EstadoDeSalud::EnRecuperacion;
    return EstadoDeSalud::Enfermo;
}

// Funciones del Menu

void registrarPerro(Refugio& r) {
    std::string nombre = leerTexto(" Ingrese el nombre del perro: ");
    int edad = leerOpcion(" Ingrese la edad: ", 0, 50);
    EstadoDeSalud salud = leerEstadoSalud();
    std::string raza = leerTexto(" Ingrese la raza: ");
    int t = leerOpcion(" Que tamanio tiene? | -> | 1. Chico, 2. Mediano, 3. Grande: ", 1, 3);
    Tamanio tam = (t == 1) ? Tamanio::Chico : (t == 2) ? Tamanio::Mediano : Tamanio::Grande;

    Perro p(nombre, edad, false, salud, raza, tam);
    int idNuevo = r.registrarAnimal(p);
    std::cout << "\n--------------------------------------------------------------------------------------------------------------------\n"
              << " Perro registrado!\n" 
              << " ID del perro: " << idNuevo << "."
              << "\n--------------------------------------------------------------------------------------------------------------------\n";
}

void registrarGato(Refugio& r) {
    std::string nombre = leerTexto(" Ingrese el nombre del gato: ");
    int edad = leerOpcion(" Ingrese la edad: ", 0, 40);
    EstadoDeSalud salud = leerEstadoSalud();
    std::string pelaje = leerTexto("De que color es su pelaje?: ");
    int c = leerOpcion(" Es un gato de interior o exterior? | -> | 1. Interior, 2. Exterior: ", 1, 2);
    Condicion cond = (c == 1) ? Condicion::Interior : Condicion::Exterior;

    Gato g(nombre, edad, false, salud, pelaje, cond);
    int idNuevo = r.registrarAnimal(g);
    std::cout << "\n--------------------------------------------------------------------------------------------------------------------\n"
              << " Gato registrado!\n" 
              << " ID del gato: " << idNuevo << "."
              << "\n--------------------------------------------------------------------------------------------------------------------\n";
}

void actualizarSalud(Refugio& r) {
    int id = leerEntero(" Ingrese la ID del animal: ");
    Animal& a = r(id);
    EstadoDeSalud salud = leerEstadoSalud();
    if (salud != a.getEstado()) {
        a.setSalud(salud);
        std::cout << "\n--------------------------------------------------------------------------------------------------------------------\n"
                  << " Estado de salud actualizado!"
                  << "\n--------------------------------------------------------------------------------------------------------------------\n";
    }
    else {
        std::cout << "\n--------------------------------------------------------------------------------------------------------------------\n"
                  << " El estado de salud ingresado es igual al actual."
                  << "\n--------------------------------------------------------------------------------------------------------------------\n"; 
    }
}

void registrarAdoptante(Refugio& r) {
    int id = 0;
    bool opc = false;
    while (opc == false)
    {   
       id = leerEntero(" Ingrese la ID del adoptante: ");
       if (id > 0){opc = true;} else {std::cout << " El valor no puede ser negativo, ingrese un numero positivo.\n";}  
    }
    std::string nombre = leerTexto(" Ingrese el nombre del adoptante: ");
    std::string contacto = leerTexto(" Ingrese un metodo de contacto (correo / telefono): ");
    int v = leerOpcion(" Ingrese la situacion de vivienda | -> | 1. Casa, 2. Departamento: ", 1, 2);
    Tipodevivienda tipo = (v == 1) ? Tipodevivienda::Casa : Tipodevivienda::Departamento;

    r.registrarAdoptante(Adoptante(id, nombre, contacto, tipo));
    std::cout   << "\n--------------------------------------------------------------------------------------------------------------------\n"
                << " Adoptante registrado!"
                << "\n--------------------------------------------------------------------------------------------------------------------\n";
}

void buscarPorId(Refugio& r) {
    int id = leerEntero(" Ingrese el ID del animal que quiere buscar: ");
    Animal& a = r(id);           // operador()(int): busca por ID, lanza NoEncontradoException si no esta
    a.mostrarInfo();
    if (!a)                      // operador! = "no disponible"
        std::cout << "\n [Este animal NO esta disponible para adopcion]\n";
}

void buscarPorIdAdop(Refugio& r){
    int id = leerEntero(" Ingrese el ID del Adoptante que quiere buscar: ");
    const Adoptante* a = r.buscarAdoptante(id);
    a->mostrarInfo();
}

void verPorPosicion(Refugio& r) {
    int pos = leerEntero(" Ingrese la posicion del arreglo que quiera consultar (0 = primera posicion): ");
    r[pos].mostrarInfo();        // operator[](int): lanza std::out_of_range si la posicion no existe
}

void crearSolicitud(Refugio& r) {
    int idAdop = leerEntero(" ID del adoptante: ");
    int idAnim = leerEntero(" ID del animal: ");
    int idSol = r.crearSolicitud(idAdop, idAnim);
    std::cout << "\n--------------------------------------------------------------------------------------------------------------------\n"
              << " Solicitud creada!\n"
              << " ID de la solicitud: " << idSol 
              << "\n--------------------------------------------------------------------------------------------------------------------\n";
}

void mostrarInstancias() {
    std::cout << "\n--------------------------------------------------------------------------------------------------------------------\n"
              << " Cantidad de 'Coleccion<Adoptante>' activas: " << Coleccion<Adoptante>::getInstancias() << "\n"
              << " Cantidad de 'Coleccion<SolicitudAdopcion>' activas: " << Coleccion<SolicitudAdopcion>::getInstancias()
              << "\n--------------------------------------------------------------------------------------------------------------------\n";
}

void mostrarMenu() {
    std::cout << "\n======= REFUGIO ANGELITOS =======\n"
              << "\n"
              << "===== FUNCIONES DEL REFUGIO =====\n"
              << " 1. [Registrar un perro]\n"
              << " 2. [Registrar un gato]\n"
              << " 3. [Registrar un adoptante]\n"
              << " 4. [Listar todos los animales del refugio]\n"
              << " 5. [Listar Solo los animales disponibles del refugio]\n"
              << " 6. [Listar todos los adoptantes registrados]\n"
              << " 7. [Buscar un animal por ID]\n"
              << " 8. [Buscar un adoptante por ID]\n"
              << " 9. [Actualizar la salud de un animal]\n"
              << "10. [Crear una solicitud de adopcion]\n"
              << "11. [Listar todas las solicitudes de adopcion creadas]\n"
              << "12. [Listar solo las solicitudes pendientes]\n"
              << "13. [Confirmar una solicitud de adopcion]\n"
              << "14. [Cancelar una solicitud de adopcion]\n"
              << "15. [Devolver un animal]\n"
              << "16. [Mostrar historial de adopciones]\n"
              << "\n"
              << "========= OTRAS OPCIONES =========\n"
              << "17. [Ver animal por posicion (operador[])\n"
              << "18. [Ver instancias de Coleccion (miembro estatico)]\n"
              << " 0. [Salir del sistema]\n";
}