#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H
#include <stdexcept>
#include <iostream>

class RefugioException : public std::runtime_error {
public:
    explicit RefugioException(const std::string& msg) : std::runtime_error(msg) {}
};

// Se lanza al registrar un animal o adoptante con un ID que ya existe
class IdRepetidoException : public RefugioException {
public:
    explicit IdRepetidoException(const std::string& msg) : RefugioException(msg) {}
};

// Se lanza cuando se busca un animal, adoptante o solicitud que no existe
class NoEncontradoException : public RefugioException {
public:
    explicit NoEncontradoException(const std::string& msg) : RefugioException(msg) {}
};

// Se lanza al intentar adoptar un animal que ya fue adoptado
class AnimalNoDisponibleException : public RefugioException {
public:
    explicit AnimalNoDisponibleException(const std::string& msg) : RefugioException(msg) {}
};

// Se lanza cuando la operacion no corresponde al estado actual
// (ej: confirmar una solicitud que ya no esta pendiente, devolver un animal que no esta adoptado)
class OperacionInvalidaException : public RefugioException {
public:
    explicit OperacionInvalidaException(const std::string& msg) : RefugioException(msg) {}
};


#endif