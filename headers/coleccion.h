#ifndef COLECCION_H
#define COLECCION_H
#include <iostream>
#include <stdexcept>

template <typename T>
class Coleccion {
private:
    T* datos;      // array dinamico de objetos T
    int cant;      // cuantos elementos hay
    int cap;       // cuantos entran sin agrandar

    static int instancias;

    void agrandar() {                      // duplica la capacidad
        int nuevaCap = cap * 2;
        T* nuevo = new T[nuevaCap];
        for (int i = 0; i < cant; i++) nuevo[i] = datos[i];
        delete[] datos;
        datos = nuevo;
        cap = nuevaCap;
    }

public:
    explicit Coleccion(int capInicial = 10)
        : datos(nullptr), cant(0), cap(capInicial < 1 ? 1 : capInicial)
    {
        datos = new T[cap];
        ++instancias;
    }

    // Constructor de copia
    Coleccion(const Coleccion& otro) : datos(nullptr), cant(otro.cant), cap(otro.cap) {
        datos = new T[cap];
        for (int i = 0; i < cant; i++) datos[i] = otro.datos[i];
        ++instancias;                      
    }

    // Operador de asignacion: se usa en  a = b;  (ambos ya existen)
    Coleccion& operator=(const Coleccion& otro) {
        if (this == &otro) return *this;   // autoasignacion
        T* nuevo = new T[otro.cap];        // copia...
        for (int i = 0; i < otro.cant; i++) nuevo[i] = otro.datos[i];
        delete[] datos;                    // libero lo viejo
        datos = nuevo;
        cant = otro.cant;
        cap = otro.cap;
        return *this;                     
    }

    ~Coleccion() {
        delete[] datos;
        --instancias;
    }

    void agregar(const T& elem) {
        if (cant == cap) agrandar();
        datos[cant++] = elem;
    }

    int cantidad() const { return cant; }

    // Si el indice es invalido lanza una excepcion.
    // Hay dos versiones: la const (para leer desde metodos const) y la normal (para modificar).
    T& operator[](int i) {
        if (i < 0 || i >= cant) throw std::out_of_range("Indice invalido: " + std::to_string(i));
        return datos[i];
    }
    const T& operator[](int i) const {
        if (i < 0 || i >= cant) throw std::out_of_range("Indice invalido: " + std::to_string(i));
        return datos[i];
    }

    static int getInstancias() { return instancias; }
};


template <typename T>
int Coleccion<T>::instancias = 0;


template <typename T>
void mostrarTodos(const Coleccion<T>& c, const std::string& msgVacio) {
    if (c.cantidad() == 0) { std::cout << msgVacio; return; }
    for (int i = 0; i < c.cantidad(); i++)
        c[i].mostrarInfo();
}

#endif