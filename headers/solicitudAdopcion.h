#ifndef ADOPCION_H
#define ADOPCION_H
#include "perro.h"
#include "gato.h"
#include "adoptante.h"
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