#include "refugio.h"

Refugio::Refugio() : Refugio("Refugio", 10) {}              //Por defecto

Refugio::Refugio(const std::string& nom, int capacidadInicial)                  //Parametrizado
    : nombre(nom), cantAnimales(0), cantAdoptantes(0), cantSolicitudes(0), proximoIdSolicitud(1)
{
    if (capacidadInicial < 1) capacidadInicial = 1;
    capAnimales = capAdoptantes = capSolicitudes = capacidadInicial;

    animales    = new Animal*[capAnimales];
    adoptantes  = new Adoptante[capAdoptantes];
    solicitudes = new SolicitudAdopcion[capSolicitudes];
}

Refugio::Refugio(const Refugio& otro)           //Copia
    : nombre(otro.nombre),
      cantAnimales(otro.cantAnimales), capAnimales(otro.capAnimales),
      cantAdoptantes(otro.cantAdoptantes), capAdoptantes(otro.capAdoptantes),
      cantSolicitudes(otro.cantSolicitudes), capSolicitudes(otro.capSolicitudes),
      proximoIdSolicitud(otro.proximoIdSolicitud)
{
    animales = new Animal*[capAnimales];
    for (int i = 0; i < cantAnimales; i++)
        animales[i] = otro.animales[i]->clonar();

    adoptantes = new Adoptante[capAdoptantes];
    for (int i = 0; i < cantAdoptantes; i++)
        adoptantes[i] = otro.adoptantes[i];

    solicitudes = new SolicitudAdopcion[capSolicitudes];
    for (int i = 0; i < cantSolicitudes; i++)
        solicitudes[i] = otro.solicitudes[i];
}

Refugio::~Refugio() //destructor, primero borra lo de adentro, luego el array
{
    for (int i = 0; i < cantAnimales; i++)
        delete animales[i];       
    delete[] animales;            
    delete[] adoptantes;
    delete[] solicitudes;
}


// Metodos internos

void Refugio::agrandarAnimales() {
    int nuevaCap = capAnimales * 2;
    Animal** nuevo = new Animal*[nuevaCap];
    for (int i = 0; i < cantAnimales; i++)
        nuevo[i] = animales[i];    
    delete[] animales;             
    animales = nuevo;
    capAnimales = nuevaCap;
}

void Refugio::agrandarAdoptantes() {
    int nuevaCap = capAdoptantes * 2;
    Adoptante* nuevo = new Adoptante[nuevaCap];
    for (int i = 0; i < cantAdoptantes; i++)
        nuevo[i] = adoptantes[i];
    delete[] adoptantes;
    adoptantes = nuevo;
    capAdoptantes = nuevaCap;
}

void Refugio::agrandarSolicitudes() {
    int nuevaCap = capSolicitudes * 2;
    SolicitudAdopcion* nuevo = new SolicitudAdopcion[nuevaCap];
    for (int i = 0; i < cantSolicitudes; i++)
        nuevo[i] = solicitudes[i];
    delete[] solicitudes;
    solicitudes = nuevo;
    capSolicitudes = nuevaCap;
}

int Refugio::indiceAnimal(int id) const {
    for (int i = 0; i < cantAnimales; i++)
        if (animales[i]->getId() == id) return i;
    return -1;
}

int Refugio::indiceAdoptante(int id) const {
    for (int i = 0; i < cantAdoptantes; i++)
        if (adoptantes[i].getId() == id) return i;
    return -1;
}

int Refugio::indiceSolicitud(int id) const {
    for (int i = 0; i < cantSolicitudes; i++)
        if (solicitudes[i].getId() == id) return i;
    return -1;
}

//Animales
bool Refugio::registrarAnimal(const Animal& a) {
    if (indiceAnimal(a.getId()) != -1) return false;     // verifica que el ID no sea repetido
    if (cantAnimales == capAnimales) agrandarAnimales();
    animales[cantAnimales] = a.clonar();                 
    cantAnimales++;
    return true;
}

void Refugio::listarAnimales() const {
    if (cantAnimales == 0) { std::cout << "No hay animales registrados.\n"; return; }
    Animal** p   = animales;                 
    Animal** fin = animales + cantAnimales;  
    for (; p < fin; ++p)                     
        (*p)->mostrarInfo();
}

void Refugio::listarDisponibles() const {
    bool hay = false;
    for (int i = 0; i < cantAnimales; i++) {
        if (!animales[i]->estaAdoptado()) {
            animales[i]->mostrarInfo();
            hay = true;
        }
    }
    if (!hay) std::cout << "No hay animales disponibles.\n";
}

Animal* Refugio::buscarAnimal(int id) const {
    int i = indiceAnimal(id);
    return (i == -1) ? nullptr : animales[i];
}

//Adoptantes
bool Refugio::registrarAdoptante(const Adoptante& ad) {
    if (indiceAdoptante(ad.getId()) != -1) return false;
    if (cantAdoptantes == capAdoptantes) agrandarAdoptantes();
    adoptantes[cantAdoptantes] = ad;
    cantAdoptantes++;
    return true;
}

void Refugio::listarAdoptantes() const {
    if (cantAdoptantes == 0) { std::cout << "No hay adoptantes registrados.\n"; return; }
    for (int i = 0; i < cantAdoptantes; i++)
        adoptantes[i].mostrarInfo();
}

//Solicitudes
int Refugio::crearSolicitud(int idAdoptante, int idAnimal) {
    if (indiceAdoptante(idAdoptante) == -1) return -1;   // verifica que el adoptante exista
    Animal* an = buscarAnimal(idAnimal);
    if (an == nullptr || an->estaAdoptado()) return -1;  // verifica que el animal este disponible, o exista

    if (cantSolicitudes == capSolicitudes) agrandarSolicitudes();
    int nuevoId = proximoIdSolicitud++;
    solicitudes[cantSolicitudes] = SolicitudAdopcion(nuevoId, idAdoptante, idAnimal);
    cantSolicitudes++;
    return nuevoId;
}

bool Refugio::confirmarSolicitud(int idSolicitud) {
    int i = indiceSolicitud(idSolicitud);
    if (i == -1 || solicitudes[i].getEstado() != EstadoSolicitud::Pendiente) return false;

    Animal* an = buscarAnimal(solicitudes[i].getIdAnimal());
    if (an == nullptr || an->estaAdoptado()) return false;

    an->setAdopcion(true);
    solicitudes[i].setEstado(EstadoSolicitud::Confirmada);

    // Las otras solicitudes pendientes por el mismo animal ya no tienen sentido
    for (int j = 0; j < cantSolicitudes; j++)
        if (j != i && solicitudes[j].getIdAnimal() == an->getId()
                   && solicitudes[j].getEstado() == EstadoSolicitud::Pendiente)
            solicitudes[j].setEstado(EstadoSolicitud::Cancelada);
    return true;
}

bool Refugio::cancelarSolicitud(int idSolicitud) {
    int i = indiceSolicitud(idSolicitud);
    if (i == -1 || solicitudes[i].getEstado() != EstadoSolicitud::Pendiente) return false;
    solicitudes[i].setEstado(EstadoSolicitud::Cancelada);
    return true;
}

bool Refugio::devolverAnimal(int idAnimal) {
    Animal* an = buscarAnimal(idAnimal);
    if (an == nullptr || !an->estaAdoptado()) return false;
    an->setAdopcion(false);
    for (int i = 0; i < cantSolicitudes; i++)
        if (solicitudes[i].getIdAnimal() == idAnimal
            && solicitudes[i].getEstado() == EstadoSolicitud::Confirmada)
            solicitudes[i].setEstado(EstadoSolicitud::Devuelta);
    return true;
}

void Refugio::mostrarSolicitudes() const {
    if (cantSolicitudes == 0) { std::cout << "No hay solicitudes.\n"; return; }
    for (int i = 0; i < cantSolicitudes; i++)
        solicitudes[i].mostrarInfo();
}

void Refugio::mostrarHistorial() const {
    bool hay = false;
    for (int i = 0; i < cantSolicitudes; i++) {
        EstadoSolicitud e = solicitudes[i].getEstado();
        if (e == EstadoSolicitud::Confirmada || e == EstadoSolicitud::Devuelta) {
            solicitudes[i].mostrarInfo();
            hay = true;
        }
    }
    if (!hay) std::cout << "Todavia no hay adopciones.\n";
}

//getters
std::string Refugio::getNombre() const { return nombre; }
int Refugio::getCantAnimales() const { return cantAnimales; }
int Refugio::getCantAdoptantes() const { return cantAdoptantes; }
int Refugio::getCantSolicitudes() const { return cantSolicitudes; }