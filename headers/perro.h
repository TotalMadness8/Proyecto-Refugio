#ifndef PERRO_H
#define PERRO_H
#include "headers/animal.h"

enum class Tamanio {
    Grande,
    Mediano,
    Chico
};

class Perro : public Animal {
    private:
    std::string raza;
    Tamanio size;

    public:
    Perro(int id, std::string nom, int age, bool adopt, EstadoDeSalud est, std::string raz, Tamanio tam);

};


#endif //Evita errores de include multiples