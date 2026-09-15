#include "clases/adoptante.cpp"
#include "clases/animal.cpp"
#include "clases/refugio.cpp"
#include "clases/solicitudAdopcion.cpp"
#include "clases/perro.cpp"
#include "clases/gato.cpp"
#include <iostream>

int main(){

Perro perro1(1,"Luna",true,EstadoDeSalud::Saludable,"Dalmata",Tamanio::Grande);
Adoptante adopt1(1,"Manuel",888,Tipodevivienda::Casa);
Solicitud<Perro> soli1(adopt1,perro1);
    return 0;
}