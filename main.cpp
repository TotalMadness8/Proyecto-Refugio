#include "headers/adoptante.h"
#include "headers/animal.h"
#include "headers/refugio.h"
#include "headers/solicitudAdopcion.h"
#include "headers/perro.h"
#include "headers/gato.h"
#include <iostream>

int main(){

Perro perro1(1,"Luna",8,true,EstadoDeSalud::Saludable,"Dalmata",Tamanio::Grande);
Adoptante adopt1(1,"Manuel","888",Tipodevivienda::Casa);
Solicitud<Perro> soli1(adopt1,perro1);
    return 0;
}