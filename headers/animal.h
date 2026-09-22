#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>

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

    virtual void mostrarInfo() const; // La re-definen perro y gato

};

#endif              //Evita errores de include multiples