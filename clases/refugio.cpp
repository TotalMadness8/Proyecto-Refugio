#include "refugio.h"

Refugio::Refugio() : Refugio("Refugio", 10) {}   // Por defecto

Refugio::Refugio(const std::string& nom, int capacidadInicial)   // Parametrizado
    : nombre(nom), animales(nullptr), cantAnimales(0),
      capAnimales(capacidadInicial < 1 ? 1 : capacidadInicial),
      adoptantes(capacidadInicial), solicitudes(capacidadInicial),   // construyen sus Colecciones
      proximoIdSolicitud(1), proximoIdAnimal(1)
{
    animales = new Animal*[capAnimales];
}

// Copia
Refugio::Refugio(const Refugio& otro)
    : nombre(otro.nombre), animales(nullptr),
      cantAnimales(otro.cantAnimales), capAnimales(otro.capAnimales),
      adoptantes(otro.adoptantes), solicitudes(otro.solicitudes),
      proximoIdSolicitud(otro.proximoIdSolicitud), proximoIdAnimal(otro.proximoIdAnimal)
{
    animales = new Animal*[capAnimales];
    for (int i = 0; i < cantAnimales; i++)
        animales[i] = otro.animales[i]->clonar();   // clonar() devuelve un Perro o Gato nuevo segun corresponda
}

// Operador "="
Refugio& Refugio::operator=(const Refugio& otro)
{
    if (this == &otro) return *this;      // autoasignacion

    // Armo la copia nueva primero
    Animal** nuevo = new Animal*[otro.capAnimales];
    for (int i = 0; i < otro.cantAnimales; i++)
        nuevo[i] = otro.animales[i]->clonar();

    // Libero lo que tenia este refugio
    for (int i = 0; i < cantAnimales; i++) delete animales[i];
    delete[] animales;

    // Me quedo con lo nuevo
    animales = nuevo;
    cantAnimales = otro.cantAnimales;
    capAnimales = otro.capAnimales;
    nombre = otro.nombre;
    adoptantes = otro.adoptantes;
    solicitudes = otro.solicitudes;
    proximoIdSolicitud = otro.proximoIdSolicitud;
    proximoIdAnimal = otro.proximoIdAnimal;
    return *this;
}

Refugio::~Refugio()   // primero borra lo de adentro (cada Animal), luego el array de punteros
{
    for (int i = 0; i < cantAnimales; i++)
        delete animales[i];
    delete[] animales;
    // adoptantes y solicitudes se liberan solos, llama a ~Coleccion() automaticamente
}

// Metodos internos

void Refugio::agrandarAnimales() {
    int nuevaCap = capAnimales * 2;
    Animal** nuevo = new Animal*[nuevaCap];
    for (int i = 0; i < cantAnimales; i++)
        nuevo[i] = animales[i];      // copio los PUNTEROS (los animales en si no se mueven)
    delete[] animales;               // borro solo el array viejo, no los animales
    animales = nuevo;
    capAnimales = nuevaCap;
}

int Refugio::indiceAnimal(int id) const {
    for (int i = 0; i < cantAnimales; i++)
        if (animales[i]->getId() == id) return i;
    return -1;
}

int Refugio::indiceAdoptante(int id) const {
    for (int i = 0; i < adoptantes.cantidad(); i++)
        if (adoptantes[i].getId() == id) return i;
    return -1;
}

int Refugio::indiceSolicitud(int id) const {
    for (int i = 0; i < solicitudes.cantidad(); i++)
        if (solicitudes[i].getId() == id) return i;
    return -1;
}

// Operadores de acceso

Animal& Refugio::operator[](int pos) const {
    if (pos < 0 || pos >= cantAnimales)
        throw std::out_of_range("Posicion invalida: " + std::to_string(pos) +".");
    return *animales[pos];     // devuelvo una referencia al animal y no al puntero
}

Animal& Refugio::operator()(int id) const {
    int i = indiceAnimal(id);
    if (i == -1)
        throw NoEncontradoException("No existe un animal con esa ID " + std::to_string(id) + ".\n");
    return *animales[i];
}

// Animales

int Refugio::registrarAnimal(const Animal& a) {
    if (cantAnimales == capAnimales) agrandarAnimales();
    Animal* copia = a.clonar();
    copia->setId(proximoIdAnimal++);   // el refugio decide el ID
    animales[cantAnimales++] = copia;
    return copia->getId(); 
}

void Refugio::listarAnimales() const {
    if (cantAnimales == 0) { std::cout << "\n [Error] No hay animales registrados.\n"; return; }
    Animal** p   = animales;
    Animal** fin = animales + cantAnimales;
    for (; p < fin; ++p)
        (*p)->mostrarInfo();
}

void Refugio::listarDisponibles() const {
    bool hay = false;
    for (int i = 0; i < cantAnimales; i++) {
        if (!(*animales[i])) continue;             // !animal == "no disponible": lo salteo
        animales[i]->mostrarInfo();
        hay = true;
    }
    if (!hay) std::cout << "\n [Error] No hay animales disponibles.\n";
}

Animal* Refugio::buscarAnimal(int id) const {
    int i = indiceAnimal(id);
    return (i == -1) ? nullptr : animales[i];
}

// Adoptantes

void Refugio::registrarAdoptante(const Adoptante& ad) {
    if (indiceAdoptante(ad.getId()) != -1)
        throw IdRepetidoException("Adoptante no registrado, ya existe un adoptante con esa ID: " + std::to_string(ad.getId()) + ".");
    adoptantes.agregar(ad);
}

const Adoptante* Refugio::buscarAdoptante(int id) const {
    int i = indiceAdoptante(id);
    return (i == -1) ? nullptr : &adoptantes[i];
}

void Refugio::listarAdoptantes() const {
    mostrarTodos(adoptantes, "\n [Error] No hay adoptantes registrados.\n");
}

// Solicitudes

int Refugio::crearSolicitud(int idAdoptante, int idAnimal) {

    int iad = indiceAdoptante(idAdoptante);
    if (iad == -1) throw NoEncontradoException("No existe un adoptante con esa ID: " + std::to_string(idAdoptante) + ".");

    int ia = indiceAnimal(idAnimal);
    if (ia == -1)
        throw NoEncontradoException("No existe un animal con ID: " + std::to_string(idAnimal));
    if (!(*animales[ia]))                          // operador unario ! : animal NO disponible
        throw AnimalNoDisponibleException("El animal " + std::to_string(idAnimal) + " ya fue adoptado.");

    for (int i = 0; i < solicitudes.cantidad(); i++) {
        if (solicitudes[i].getIdAdoptante() == idAdoptante && solicitudes[i].getIdAnimal() == idAnimal){
            throw SolicitudRepetidaException("Ya hay una solicitud creada entre ese animal y ese adoptante, ID de la solicitud: " + std::to_string(solicitudes[i].getId()) + ".");
        }
    } 
    int nuevoId = proximoIdSolicitud++;

    solicitudes.agregar(SolicitudAdopcion(nuevoId, idAdoptante, idAnimal, animales[ia]->getNombre(), adoptantes[iad].getNombre()));
    return nuevoId;
}

void Refugio::confirmarSolicitud(int idSolicitud) {
    int i = indiceSolicitud(idSolicitud);
    if (i == -1)
        throw NoEncontradoException("No existe la solicitud " + std::to_string(idSolicitud));
    if (solicitudes[i].getEstado() != EstadoSolicitud::Pendiente)
        throw OperacionInvalidaException("La solicitud " + std::to_string(idSolicitud) + " no esta pendiente.");

    Animal* an = buscarAnimal(solicitudes[i].getIdAnimal());
    if (an == nullptr)
        throw NoEncontradoException("El animal de la solicitud ya no existe");
    if (!(*an))
        throw AnimalNoDisponibleException("El animal " + std::to_string(an->getId()) + " ya fue adoptado.");

    an->setAdopcion(true);
    solicitudes[i].setEstado(EstadoSolicitud::Confirmada);

    // Busca otras solicitudes por el mismo animal y las cancela
    for (int j = 0; j < solicitudes.cantidad(); j++)
        if (j != i && solicitudes[j].getIdAnimal() == an->getId()
                   && solicitudes[j].getEstado() == EstadoSolicitud::Pendiente)
            solicitudes[j].setEstado(EstadoSolicitud::Cancelada);
}

void Refugio::cancelarSolicitud(int idSolicitud) {
    int i = indiceSolicitud(idSolicitud);
    if (i == -1)
        throw NoEncontradoException("No existe una solicitud con ID: " + std::to_string(idSolicitud));
    if (solicitudes[i].getEstado() != EstadoSolicitud::Pendiente)
        throw OperacionInvalidaException(" La solicitud con ID: " + std::to_string(idSolicitud) + " no esta pendiente.");
    solicitudes[i].setEstado(EstadoSolicitud::Cancelada);
}

void Refugio::devolverAnimal(int idAnimal) {
    Animal* an = buscarAnimal(idAnimal);
    if (an == nullptr)
        throw NoEncontradoException("No existe un animal con esa ID " + std::to_string(idAnimal));
    if (!an->estaAdoptado())
        throw OperacionInvalidaException("No se puede devolver el animal " + std::to_string(idAnimal) + ", el animal no esta adoptado.");

    an->setAdopcion(false);
    for (int i = 0; i < solicitudes.cantidad(); i++)
        if (solicitudes[i].getIdAnimal() == idAnimal
            && solicitudes[i].getEstado() == EstadoSolicitud::Confirmada)
            solicitudes[i].setEstado(EstadoSolicitud::Devuelta);
}

void Refugio::mostrarSolicitudes() const {
    mostrarTodos(solicitudes, " [Error] No hay solicitudes.\n");
}

void Refugio::mostrarSolicitudesPendientes() const{
    bool hay = false;
    for (int i = 0; i < solicitudes.cantidad(); i++) {
        EstadoSolicitud e = solicitudes[i].getEstado();
        if (e == EstadoSolicitud::Pendiente) {
            solicitudes[i].mostrarInfo();
            hay = true;
        }
    }
    if (!hay) std::cout << "\n No hay solicitudes pendientes. \n";
}

void Refugio::mostrarHistorial() const {
    bool hay = false;
    for (int i = 0; i < solicitudes.cantidad(); i++) {
        EstadoSolicitud e = solicitudes[i].getEstado();
        if (e == EstadoSolicitud::Confirmada || e == EstadoSolicitud::Devuelta || e == EstadoSolicitud::Cancelada) {
            solicitudes[i].mostrarInfo();
            hay = true;
        }
    }
    if (!hay) std::cout << "\n Todavia no hay adopciones.\n";
}

// ---------- Getters ----------
std::string Refugio::getNombre() const { return nombre; }
int Refugio::getCantAnimales() const { return cantAnimales; }
int Refugio::getCantAdoptantes() const { return adoptantes.cantidad(); }
int Refugio::getCantSolicitudes() const { return solicitudes.cantidad(); }