#ifndef ADOPTANTE_H
#define ADOPTANTE_H
#include <iostream>

//enum para usar a modo de etiqueta
enum class Tipodevivienda {
    Casa,
    Departamento
};

class Adoptante {
    protected:
    int id;
    std::string nombre;                         //Atributos
    std::string contacto;
    Tipodevivienda vivienda;

    public: 
    Adoptante(int ide, std::string nom, std::string phone, Tipodevivienda tipo);                //Constructor
    
};

#endif ADOPTANTE_H              //Esta linea y las 2 primeras evitan que el archivo sea incluido multiples veces por error