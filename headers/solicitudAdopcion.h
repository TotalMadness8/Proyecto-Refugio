#ifndef ADOPCION_H
#define ADOPCION_H
#include "headers/perro.h"
#include "headers/gato.h"
#include "headers/adoptante.h"
#include <iostream>

template <typename animal>

class Solicitud {
    private:
    Adoptante adopt;            // Atributos
    animal anim;
    
    public:

    Solicitud(Adoptante& adopt, animal& anim);          // Constructor

    

};

#endif // evita errores de multiples include