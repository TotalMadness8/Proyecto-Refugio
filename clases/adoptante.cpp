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

    public: 
    Adoptante(int ide, std::string nom, int phone, Tipodevivienda tipo) : id(ide), nombre(nom), contacto(phone), vivienda(tipo){
        id = ide;
        nombre = nom;
        contacto = phone;
        vivienda = tipo;
    }
};