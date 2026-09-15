#include <iostream>

enum class Tipodevivienda {
    Casa,
    Departamento
};

class Adoptante {
    protected:
    int id;
    std::string nombre;
    int contacto;
    Tipodevivienda vivienda;
};