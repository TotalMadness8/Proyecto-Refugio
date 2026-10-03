#include "adoptante.h"
#include "animal.h"
#include "refugio.h"
#include "solicitudAdopcion.h"
#include "gato.h"
#include "perro.h"
#include <iostream>


int main(){

Perro perro1(1,"Luna",8,true,EstadoDeSalud::Saludable,"Dalmata",Tamanio::Grande);
Adoptante adopt1(1,"Manuel","888",Tipodevivienda::Casa);
perro1.mostrarInfo();
adopt1.mostrarInfo();
    return 0;
}