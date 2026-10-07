#ifndef PERRO_H
#define PERRO_H
#include "animal.h"

// enum para usar a modo de etiquerta
enum class Tamanio {
    Grande,
    Mediano,
    Chico
};

class Perro : public Animal {
    private:
    std::string raza;               // Atributos
    Tamanio size;

    public:
    Perro(std::string nom, int age, bool adopt, EstadoDeSalud est, std::string raz, Tamanio tam);   // constructor

    void mostrarInfo() const override;
    Animal* clonar() const override;
};


#endif //Evita errores de include multiples