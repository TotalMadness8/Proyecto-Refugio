#include <iostream>
#include <string>
#include <cstdlib>
#include "adoptante.h"
#include "animal.h"
#include "gato.h"
#include "perro.h"
#include "refugio.h"
#include "solicitudAdopcion.h"
#include "coleccion.h"
#include "excepciones.h"
#include "menu.h"



int main() {
    Refugio refugio("Refugio Angelitos", 2);
    int opcion = -1;

    //Animales pre-cargados
    Perro perro1("Luna",8,false,EstadoDeSalud::Saludable,"Dalmata",Tamanio::Grande);
    Gato  gato1("Lulu",11,false,EstadoDeSalud::Saludable,"Naranja",Condicion::Interior);
    Perro perro2("Toby",2,false,EstadoDeSalud::EnRecuperacion,"Mestizo",Tamanio::Chico);
    Gato gato2("Morcilla",2,false,EstadoDeSalud::Saludable,"Negro",Condicion::Interior);

    refugio.registrarAnimal(perro1);
    refugio.registrarAnimal(perro2);
    refugio.registrarAnimal(gato1);
    refugio.registrarAnimal(gato2);

    //Adoptantes pre-cargados
    Adoptante adopt1(1,"Manuel","noronamanu@gmail.com",Tipodevivienda::Casa);
    Adoptante adopt2(2,"Delfi","3584318822",Tipodevivienda::Departamento);

    refugio.registrarAdoptante(adopt1);
    refugio.registrarAdoptante(adopt2);
   

    while (opcion != 0) {
        mostrarMenu();
        opcion = leerOpcion("Opcion: ", 0, 14);

        // El try esta dentro del while: si algo falla, el catch muestra el error
        // y el while sigue con la siguiente vuelta, asi el menu nunca se cae.
        try {
            switch (opcion) {
                case 1:  registrarPerro(refugio);          break;
                case 2:  registrarGato(refugio);           break;
                case 3:  refugio.listarAnimales();         break;
                case 4:  refugio.listarDisponibles();      break;
                case 5:  registrarAdoptante(refugio);      break;
                case 6:  buscarPorId(refugio);             break;
                case 7:  crearSolicitud(refugio);          break;
                case 8:  refugio.confirmarSolicitud(leerEntero("ID de la solicitud: "));
                         std::cout << "Solicitud confirmada.\n"; break;
                case 9:  refugio.cancelarSolicitud(leerEntero("ID de la solicitud: "));
                         std::cout << "Solicitud cancelada.\n";  break;
                case 10: refugio.devolverAnimal(leerEntero("ID del animal: "));
                         std::cout << "Animal devuelto.\n"; break;
                case 11: refugio.mostrarSolicitudes();     break;
                case 12: refugio.mostrarHistorial();       break;
                case 13: verPorPosicion(refugio);          break;
                case 14: mostrarInstancias();              break;
                case 0:  std::cout << "Hasta luego!\n";    break;
            }
        }
        // Multiples catch, por referencia, y constantes, evita que excepcion se copie por accidente
        // Se evaluan en orden y entra el primero que coincide, por eso van de lo mas especifico
        // a lo mas general.
        catch (const IdRepetidoException& e)          { std::cout << "[ID repetido] " << e.what() << "\n"; }
        catch (const AnimalNoDisponibleException& e)  { std::cout << "[Animal no disponible] " << e.what() << "\n"; }
        catch (const NoEncontradoException& e)        { std::cout << "[No encontrado] " << e.what() << "\n"; }
        catch (const OperacionInvalidaException& e)   { std::cout << "[Operacion invalida] " << e.what() << "\n"; }
        catch (const std::out_of_range& e)            { std::cout << "[Indice invalido] " << e.what() << "\n"; }
        catch (const std::exception& e)               { std::cout << "[Error] " << e.what() << "\n"; }
    }
    return 0;
}