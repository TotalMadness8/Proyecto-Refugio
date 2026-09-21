#include "headers/solicitudAdopcion.h"

template <typename animal>

Solicitud<animal>::Solicitud(Adoptante& adoptante, animal& animal) : adopt(adoptante), anim(animal){

}