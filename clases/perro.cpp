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

    public:
    Perro(int id,std::string nom, bool adopt, EstadoDeSalud est, std::string raz, Tamanio tam) : Animal(id,nom,adopt,est), size(tam), raza(raz){
        raza = raz;
        size = tam;
    }

};