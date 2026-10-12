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
    Perro perro2("Grafit",9,false,EstadoDeSalud::Saludable,"Bulldog Frances",Tamanio::Chico);
    Gato gato2("Morcilla",2,false,EstadoDeSalud::EnRecuperacion,"Negro",Condicion::Interior);
    Perro perro3("Koga",5,false,EstadoDeSalud::Saludable,"Golden Retriever", Tamanio::Mediano);

    refugio.registrarAnimal(perro1);
    refugio.registrarAnimal(perro2);
    refugio.registrarAnimal(perro3);
    refugio.registrarAnimal(gato1);
    refugio.registrarAnimal(gato2);

    //Adoptantes pre-cargados
    Adoptante adopt1(1,"Manu","noronamanu@gmail.com",Tipodevivienda::Casa);
    Adoptante adopt2(2,"Delfi","3584318822",Tipodevivienda::Departamento);
    Adoptante adopt3(3,"Anett","kuroi@baelz.hakos",Tipodevivienda::Casa);

    refugio.registrarAdoptante(adopt1);
    refugio.registrarAdoptante(adopt2);
    refugio.registrarAdoptante(adopt3);
   

    while (opcion != 0) {
        mostrarMenu();
        opcion = leerOpcion("\n Opcion: ", 0, 18);

        // El try esta dentro del while: si algo falla, el catch muestra el error
        // y el while sigue con la siguiente vuelta, asi el menu nunca se cae.
        try {
            switch (opcion) {
                case 1:  registrarPerro(refugio);          break;
                case 2:  registrarGato(refugio);           break;
                case 3:  registrarAdoptante(refugio);      break;
                case 4:  refugio.listarAnimales();         break;
                case 5:  refugio.listarDisponibles();      break;
                case 6:  refugio.listarAdoptantes();       break;
                case 7:  buscarPorId(refugio);             break;
                case 8:  buscarPorIdAdop(refugio);         break;
                case 9:  actualizarSalud(refugio);         break; 
                case 10: crearSolicitud(refugio);          break; 
                case 11: refugio.mostrarSolicitudes();     break;
                case 12: refugio.mostrarSolicitudesPendientes();    break;
                case 13: refugio.confirmarSolicitud(leerEntero(" ID de la solicitud: "));
                         std::cout  << "\n--------------------------------------------------------------------------------------------------------------------\n"
                                    << " Solicitud confirmada."
                                    << "\n--------------------------------------------------------------------------------------------------------------------\n"; break;
                case 14:  refugio.cancelarSolicitud(leerEntero(" ID de la solicitud: "));
                         std::cout  << "\n--------------------------------------------------------------------------------------------------------------------\n"
                                    << " Solicitud cancelada."
                                    << "\n--------------------------------------------------------------------------------------------------------------------\n";  break;
                case 15: refugio.devolverAnimal(leerEntero(" ID del animal: "));
                         std::cout  << "\n--------------------------------------------------------------------------------------------------------------------\n"
                                    << " Animal devuelto."
                                    << "\n--------------------------------------------------------------------------------------------------------------------\n"; break;
                case 16: refugio.mostrarHistorial();       break;
                case 17: verPorPosicion(refugio);          break;
                case 18: mostrarInstancias();              break;
                case 0:  std::cout << "\n Hasta luego!\n"; break;
            }
        }
        // Multiples catch, por referencia, y constantes, evita que excepcion se copie por accidente
        // Se evaluan en orden y entra el primero que coincide, por eso van de lo mas especifico
        // a lo mas general.
        catch (const IdRepetidoException& e)          { std::cout << "\n [Error: ID repetido] " << e.what() << "\n"; }
        catch (const AnimalNoDisponibleException& e)  { std::cout << "\n [Error: Animal no disponible] " << e.what() << "\n"; }
        catch (const NoEncontradoException& e)        { std::cout << "\n [Error: No encontrado] " << e.what() << "\n"; }
        catch (const SolicitudRepetidaException& e)   { std::cout << "\n [Error: Solicitud Repetida] " << e.what() << "\n"; }
        catch (const OperacionInvalidaException& e)   { std::cout << "\n [Error: Operacion invalida] " << e.what() << "\n"; }
        catch (const std::out_of_range& e)            { std::cout << "\n [Error: Indice invalido] " << e.what() << "\n"; }
        catch (const std::exception& e)               { std::cout << "\n [Error] " << e.what() << "\n"; }
    }
    return 0;
}