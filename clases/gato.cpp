#include <iostream>
#include "clases/animal.cpp"

enum class Condicion {
    Exterior,
    Interior
};

class Gato : protected Animal {
    private:
    std::string pelaje;
    Condicion condicion;
};