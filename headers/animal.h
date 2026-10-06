#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>
#include <string>

// enum para usar a modo de etiqueta
enum class EstadoDeSalud
{
    Saludable,
    EnRecuperacion,
    Enfermo
};

class Animal
{
protected:
    int id;
    std::string nombre;
    int edad;                           // Atributos
    bool adopcion = false;              // True = Adoptado
    EstadoDeSalud estado;

    public:

    Animal();                                                                 // Constructor por defecto
    Animal(int ide, std::string nom, int age, bool adopt, EstadoDeSalud est); // Constructor
    Animal(const Animal& otro);                                               // Constructor de copia
    virtual ~Animal();                                                        // Destructor virtual

    //Metodos

    int getId() const;
    std::string getNombre() const;
    bool estaAdoptado() const;
    void setAdopcion(bool valor);

    //Operadores
    bool operator==(const Animal& otro) const;
    bool operator!() const;

    //Metodos virtuales puros
    virtual void mostrarInfo() const = 0;
    virtual Animal* clonar() const = 0;     //Es para la copia profunda, perro y gato la re-definen
};

#endif              //Evita errores de include multiples