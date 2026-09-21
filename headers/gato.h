#include <iostream>
#include "headers/animal.h"

enum class Condicion {
    Exterior,
    Interior
};

class Gato : protected Animal {
    private:
    std::string pelaje;
    Condicion condicion;
};