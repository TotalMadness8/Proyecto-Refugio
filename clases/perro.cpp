#include <iostream>
#include "clases/animal.cpp"

enum class Tamanio {
    Grande,
    Mediano,
    Chico
};

class Perro : protected Animal {
    private:
    std::string raza;
    Tamanio size;
};