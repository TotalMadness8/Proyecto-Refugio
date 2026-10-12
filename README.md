# Proyecto Refugio: Sistema de Gestión de un Refugio de Animales

**Programación Orientada a Objetos, 2026.** Prof. Lic. Diego L. Mattana
**Integrantes:** Vicente Galetto, Manuel Norona
**Lenguaje:** C++17

## 1. Descripción

Es un programa de consola para administrar el Refugio "Angelitos". Permite registrar perros, gatos y adoptantes, crear, confirmar y cancelar solicitudes de adopción, devolver animales y consultar listados e historial.

Al iniciar, el programa precarga 5 animales (Luna, Lulu, Grafit, Morcilla y Koga) y 3 adoptantes (Manu, Delfi y Anett).

## 2. Por qué el problema se adapta a la POO?

El problema tiene entidades con estado y comportamiento propios (animales, adoptantes, solicitudes) que se modelan como clases.

- Los atributos están encapsulados: solo cambian mediante métodos que validan las reglas del refugio.
- Perro y Gato heredan de Animal, lo común, y agregan lo suyo.
- Gracias al polimorfismo, el refugio recorre un único catálogo de `Animal*` sin necesidad de saber el tipo de cada uno.
- El Refugio compone a las demás entidades y controla su ciclo de vida.

Agregar un tipo nuevo de animal no requiere modificar el Refugio.

## 3. Requisitos, estructura y compilación

### Requisitos mínimos

- Compilador de C++: `g++`, compatible con C++17 o superior.
- Herramienta de automatización `make` (en Windows se llama `mingw32-make`).

**Cómo verificar que `make` está instalado:** en una consola de PowerShell o en una terminal de Visual Studio Code, ejecutar:

```bash
mingw32-make --version
```

Si muestra una versión, la herramienta funciona correctamente. Si no, revisar las variables de entorno o instalarla desde la consola de MSYS2 ingresando:

```bash
pacman -S mingw-w64-ucrt-x86_64-make
```

Si pide confirmación, escribir `y` y presionar Enter. Al terminar, volver a verificar la versión.

### Estructura del proyecto

- `main.cpp`: punto de entrada de la aplicación.
- `headers/`: archivos de cabecera (`.h`).
- `clases/`: implementación de las clases (`.cpp`).
- `docs/diagramas/`: diagramas de flujo, de estados y de clases.

### Compilación y ejecución

No hace falta configurar extensiones ni archivos de configuración en el editor. Basta con abrir una terminal en la raíz del proyecto y ejecutar:

```bash
mingw32-make      # o solo "make", si renombraste el alias o el ejecutable en MSYS2. Crea el .exe
./main.exe        # ejecuta el programa
```

## 4. Uso

Se elige un número del menú y se presiona Enter. El menú sigue activo hasta elegir [0].

| Opción | Acción |
| 1 | Registrar perro
| 2 | Registrar gato
| 3 | Registrar un adoptante
| 4 | Listar todos los animales
| 5 | Listar solo los disponibles
| 6 | Listar adoptantes
| 7 | Buscar animal por ID
| 8 | Buscar adoptante por ID
| 9 | Actualizar la salud de un animal
| 10 | Crear una solicitud 
| 11 | Listar todas las solicitudes
| 12 | Listar solo las solicitudes pendientes
| 13 | Confirmar solicitud
| 14 | Cancelar solicitud
| 15 | Devolver un animal
| 16 | Mostral historial de adopciones
| 17 | Buscar un animal por posicion usando el operador []
| 18 | Ver la cantidad de instancias en Coleccion (Miembro estatico)
| 0 | Salir 

- El refugio asigna automáticamente los IDs de animales y de solicitudes.
- El ID del adoptante lo ingresa el usuario (porque sino no la excepcion de IDs repetidos que se pide no tendria sentido): tiene que ser un número positivo y no se puede repetir.
- Si se escribe texto en lugar de un número, un valor fuera de rango o una entrada vacía, el programa vuelve a pedir el dato.
- No se pueden crear dos solicitudes con el mismo adoptante y el mismo animal.

## 5. Diseño

| Clase | Responsabilidad |

| `Animal` (abstracta) | Contiene los datos comunes y define la interfaz `mostrarInfo()` y `clonar()` |

| `Perro`, `Gato` | Agregan sus atributos (raza y tamaño; pelaje e interior o exterior) y redefinen los métodos virtuales |

| `Adoptante` | Guarda ID, nombre, contacto y tipo de vivienda |

| `SolicitudAdopcion` | Relaciona un adoptante con un animal mediante sus IDs y sus nombres y guarda el estado: Pendiente, Confirmada, Cancelada o Devuelta |

| `Coleccion<T>` | Arreglo dinámico genérico con crecimiento automático y acceso validado |

| `Refugio` | Es dueño del catálogo y de las colecciones, y aplica las reglas del negocio |

| `menu.cpp` | Lee y valida la entrada del usuario. Mantiene la consola separada de la lógica |

**Decisiones de diseño principales:**

- **`registrarAnimal()` guarda un clon.** Recibe el animal como `const Animal&` y guarda un clon creado con `clonar()`, así el refugio es el único dueño de sus animales. `clonar()` funciona como un constructor de copia virtual: crea un `Perro` o un `Gato` según el tipo real del objeto.
- **Las solicitudes guardan IDs y no punteros.** Los punteros quedarían inválidos cuando `Coleccion` agranda su arreglo o cuando se copia el Refugio.
- **Confirmar una solicitud cancela las demás pendientes de ese animal.** Devolver el animal pasa la solicitud a "Devuelta", así el historial queda registrado.
- **El `try` está dentro del `while` del menú**, de modo que ningún error cierra el programa.

## 6. Memoria dinámica

Quien crea y quien libera espacios de memoria:

| Bloque | Quien lo crea | Quien lo libera |

| `Animal** animales` (arreglo de punteros) | Constructor de `Refugio` | `~Refugio()`, con `delete[]` |

| Cada `Perro` o `Gato` | `registrarAnimal()`, mediante `clonar()` | `~Refugio()`, con `delete animales[i]` |

| Arreglo agrandado (el doble de capacidad) | `agrandarAnimales()` y `Coleccion::agrandar()` | El mismo método, que hace `delete[]` solo del arreglo viejo |

| `T* datos` de `Coleccion<T>` | Constructor de `Coleccion` | `~Coleccion()`, que se llama automáticamente al destruir el Refugio |

`~Refugio()` libera primero cada animal y después el arreglo. Si lo hiciera al revés, perdería las direcciones de los animales.

El puntero que devuelve `buscarAnimal()` es "prestado": quien lo recibe no debe liberarlo.

**Regla de los Tres.** `Refugio` y `Coleccion<T>` implementan constructor de copia, `operator=` y destructor, todos con copia profunda: el Refugio clona cada animal. Con una copia superficial, dos refugios compartirían los mismos animales y al destruirse harían un doble `delete`. `operator=` protege la autoasignación y arma la copia nueva antes de liberar la vieja.

**Aritmética de punteros.** Se usa en `listarAnimales()`:

```cpp
for (Animal** p = animales; p < animales + cantAnimales; ++p)
    (*p)->mostrarInfo();
```

## 7. Operadores, herencia y polimorfismo

| Operador | Clase | Significado |

| `==` | `Animal` | Dos animales son iguales si tienen el mismo ID |

| `!` | `Animal` | `!a` es `true` si el animal no está disponible |

| `[]` | `Refugio` | Accede a un animal por posición. Si no existe, lanza `out_of_range` |

| `()` | `Refugio` | Busca un animal por ID. Si no existe, lanza `NoEncontradoException` |

| `[]`, `=` | `Coleccion<T>` | Acceso validado y asignación con copia profunda |

- `Animal` es abstracta: tiene `mostrarInfo()` y `clonar()` como virtuales puras.
- Su destructor es virtual, para que `delete` sobre un `Animal*` también ejecute `~Perro()` o `~Gato()`.
- `Perro` y `Gato` usan herencia pública y `override`, y llaman a `Animal::mostrarInfo()` para reutilizar la parte común.
- La ligadura dinámica se ve en `(*p)->mostrarInfo()`: el método que se ejecuta se decide en tiempo de ejecución.

## 8. Templates y miembro estático

- **`Coleccion<T>`** tiene `agregar()`, `cantidad()` y `operator[]`. Se instancia con **`Adoptante`** y con **`SolicitudAdopcion`**.
- **Miembro estático `instancias`:** cuenta las colecciones vivas. Se incrementa en los constructores y se decrementa en el destructor. Cada instanciación del template es una clase distinta, así que `Coleccion<Adoptante>` y `Coleccion<SolicitudAdopcion>` tienen contadores independientes. Por eso la opción 18 muestra 1 y 1.
- **Función genérica `mostrarTodos<T>()`:** se usa con `Adoptante` en `listarAdoptantes()` y con `SolicitudAdopcion` en `mostrarSolicitudes()`.

## 9. Excepciones

`RefugioException` hereda de `std::runtime_error`, y de ella heredan:

| Excepción | Situación |
|---|---|
| `IdRepetidoException` | Registrar un adoptante con un ID que ya existe |

| `NoEncontradoException` | El animal, el adoptante o la solicitud no existe |

| `AnimalNoDisponibleException` | Solicitar o confirmar un animal ya adoptado |

| `OperacionInvalidaException` | Confirmar o cancelar una solicitud que no está pendiente, o devolver un animal que no está adoptado |

| `SolicitudRepetidaException` | Crear una solicitud con el mismo animal y el mismo adoptante que una solicitud existente |

| `std::out_of_range` | Posición o índice inválido |

En `main` se usan varios `catch` por referencia constante, ordenados de lo más específico a lo más general (`std::exception` va al final). La referencia evita copias y slicing, y `const` indica que solo se lee el mensaje.

## 10. Pseudocódigo

```
MENÚ PRINCIPAL
  Crear refugio y precargar datos
  MIENTRAS opcion ≠ 0
      Mostrar menú; leer opción válida (0..18)
      INTENTAR  ejecutar la opción elegida
      CAPTURAR  error → mostrar mensaje
  FIN MIENTRAS

CREAR SOLICITUD (idAdoptante, idAnimal)
  SI no existe el adoptante o el animal → lanzar NoEncontrado
  SI el animal está adoptado          → lanzar AnimalNoDisponible
  SI ya existe una solicitud con el mismo adoptante y animal → error
  Agregar solicitud nueva en estado PENDIENTE y devolver su ID

CONFIRMAR SOLICITUD (id)
  SI no existe → NoEncontrado;  SI no está PENDIENTE → OperacionInvalida
  SI el animal ya está adoptado → AnimalNoDisponible
  Animal ← adoptado;  solicitud ← CONFIRMADA
  Las otras solicitudes PENDIENTES de ese animal ← CANCELADA

DEVOLVER ANIMAL (id)
  SI no existe → NoEncontrado;  SI no está adoptado → OperacionInvalida
  Animal ← disponible;  su solicitud CONFIRMADA ← DEVUELTA
```

## 11. Diagramas de flujo

Los diagramas están en la carpeta `docs/diagramas/`, en formato PNG:

| Archivo | Contenido |
|---|---|
| `00_menu_principal.png` | Menú principal (incluye la opción 0, Salir) |
| `01_registrar_perro.png` | Opción 1: Registrar perro |
| `02_registrar_gato.png` | Opción 2: Registrar gato |
| `03_listar_animales.png` | Opción 3: Listar todos los animales |
| `04_listar_disponibles.png` | Opción 4: Listar disponibles |
| `05_registrar_adoptante.png` | Opción 5: Registrar adoptante |
| `06_buscar_por_id.png` | Opción 6: Buscar por ID |
| `07_crear_solicitud.png` | Opción 7: Crear solicitud |
| `08_confirmar_solicitud.png` | Opción 8: Confirmar solicitud |
| `09_cancelar_solicitud.png` | Opción 9: Cancelar solicitud |
| `10_devolver_animal.png` | Opción 10: Devolver animal |
| `11_mostrar_solicitudes.png` | Opción 11: Mostrar solicitudes |
| `12_historial.png` | Opción 12: Historial |
| `13_ver_por_posicion.png` | Opción 13: Ver por posición |
| `14_instancias.png` | Opción 14: Ver instancias |
| `15_proceso_adopcion.png` | Proceso de adopción (estados de una solicitud) |
| `16_diagrama_clases.png` | Diagrama de clases |

## 12. Casos de prueba

Cada prueba indica el caso, el comportamiento esperado y el obtenido. Cuando el resultado no fue el esperado o no fue satisfactorio, se aplicó una corrección (Fix) y se volvió a probar.

**T1. Expansión de arreglos**
- **Caso:** el refugio se crea con capacidad 2 y el programa precarga más de 2 animales y más de 2 adoptantes.
- **Esperado:** los arreglos se expanden.
- **Obtenido:** los arreglos se expanden. ✔

**T2. Sistema de ID automático**
- **Caso:** el programa precarga 3 animales, que reciben los IDs 1, 2 y 3. Después se vuelve a registrar el primer animal desde el código.
- **Esperado:** el animal se registra de nuevo con los mismos datos, pero con el ID 4.
- **Obtenido:** el animal se registra con el ID 4. ✔

**T3. Detección de ID repetido con try/catch**
- **Caso:** el programa precarga 2 adoptantes con el mismo ID. Los adoptantes son el único caso sin ID automático.
- **Esperado:** se registra el primero y el segundo da error.
- **Obtenido:** se registra el primer adoptante, el segundo no se registra y la consola muestra un mensaje de error personalizado. ✔

**T4. Valores no numéricos como ID**
- **Caso:** al crear un adoptante durante la ejecución, el usuario ingresa un ID no numérico.
- **Esperado:** se muestra un error y se vuelve a pedir el ID.
- **Obtenido:** se muestra el error y el ID se vuelve a pedir hasta que se ingrese un número entero. ✔

**T5. Valores negativos como ID**
- **Caso:** al crear un adoptante durante la ejecución, el usuario ingresa un ID negativo.
- **Esperado:** se muestra un error y se vuelve a pedir el ID.
- **Obtenido:** el adoptante se creaba con el ID negativo. ✘
- **Fix:** se modificó la función que verifica que el valor sea numérico para que también verifique que sea positivo.
- **Nuevo resultado:** se muestra un error y el ID se vuelve a pedir hasta que se ingrese un número positivo. ✔

**T6. Valores fuera de rango en las opciones de un enum (Adoptante, Perro, Gato)**
- **Caso:** al pedir, por ejemplo, el estado de salud, el usuario ingresa un valor no numérico o fuera del rango indicado.
- **Esperado:** se muestra un error y se vuelve a pedir el dato.
- **Obtenido:** el dato se volvía a pedir hasta que fuera válido, pero los mensajes de error eran distintos: uno para los valores no numéricos o negativos, y otro para los valores mayores al rango.
- **Fix:** la función que verifica valores numéricos dejó de verificar si son negativos. Esa verificación pasó a la función que crea adoptantes, que es la única que no usa un rango de valores.
- **Nuevo resultado:** los mensajes de error son coherentes entre funciones. Los enum solo verifican que el valor sea numérico y esté dentro del rango, y el ID del adoptante verifica que sea numérico y positivo. El dato se vuelve a pedir hasta que sea válido. ✔

**T7. Búsqueda de un ID inexistente**
- **Caso:** el usuario ingresa un ID que no existe en el arreglo.
- **Esperado:** el `catch` atrapa el error y lo muestra por pantalla.
- **Obtenido:** la consola muestra un error personalizado y el programa sigue funcionando. ✔

**T8. Solicitudes con IDs inválidos**
- **Caso:** se crean solicitudes con el ID del animal, el del adoptante o ambos vacíos o inválidos.
- **Esperado:** el `catch` atrapa el error y lo muestra por pantalla.
- **Obtenido:** se muestra el error por consola. Si los dos IDs son inválidos, el mensaje solo indica el primer ID invalido que encuentra, que es el del adoptante. ✔

**T9. Entradas vacías**
- **Caso:** se crean perros, gatos o adoptantes dejando entradas vacías.
- **Esperado:** las entradas numéricas muestran un error y piden un valor numérico. Las de texto quedan vacías.
- **Obtenido:** las entradas numéricas exigen un valor, pero las de texto aceptaban entradas vacías.
- **Fix:** se modificó la función de entrada de texto para que repita el pedido hasta recibir un texto no vacío.
- **Nuevo resultado:** ninguna entrada puede quedar vacía. ✔

**T10. Lógica de adopción: operaciones repetidas**
- **Caso:** se adopta dos veces el mismo animal y se lo devuelve dos veces.
- **Esperado:** en ambos casos, la primera operación tiene éxito y la segunda da error.
- **Obtenido:** la primera operación se realiza con éxito, y en cada segundo intento el `catch` atrapa el error y muestra un mensaje. ✔

**T11. Lógica de adopción: varias solicitudes por el mismo animal**
- **Caso:** se crean varias solicitudes por el mismo animal y se intenta confirmar todas.
- **Esperado:** se confirma la primera y las demás se cancelan automáticamente.
- **Obtenido:** se confirma la primera y las demás se cancelan automáticamente. ✔

**T12. Lógica de adopción: solicitudes duplicadas**
- **Caso:** se crean varias solicitudes entre el mismo animal y el mismo adoptante.
- **Esperado:** se crea la primera y las demás dan error.
- **Obtenido:** se creaban todas las solicitudes, con IDs correctos, y se comportaban como cualquier otra. ✘
- **Fix:** antes de crear una solicitud, se verifica que no exista otra con los mismos datos.
- **Nuevo resultado:** se crea la primera y las demás dan error. ✔

**T13. Copia profunda y liberación de memoria.** 
Se probó con un `main` auxiliar, copiando el main original y agregando el fragmento a continuación:

```cpp
Refugio copia(refugio);      // constructor de copia
copia(1).setAdopcion(true);   // se modifica el estado de adopcion
Refugio asignado; asignado = refugio; asignado = asignado;
refugio(1).mostrarInfo();
copia(1).MostrarInfo();
```

| Prueba | Resultado |
|---|---|
| ¿Luna está en la misma dirección de memoria en el original y en la copia? | `NO`: es un objeto distinto ✔ |
| Se adopta a Luna solo en la copia | El original sigue con Luna disponible ✔ |
| Se agrega un perro a `asignado` | El original tiene 2 animales y `asignado` tiene 3. La autoasignación no rompe nada ✔ |
| Contador estático (Coleccion)| Pasa de 1 a 2 con la copia viva y vuelve a 1 cuando se destruye ✔ |

Tanto este programa como una sesión completa del menú se ejecutaron con `valgrind --leak-check=full`. El resultado fue `All heap blocks were freed -- no leaks are possible` y `0 errors`: toda la memoria se libera y no hay dobles `delete`.

## 13. Limitaciones del proyecto

- Los datos no se guardan al cerrar el programa, solo los animales y adoptantes hardcodeados.
- Una vez creados, no se pueden eliminar animales, adoptantes o solicitudes del catálogo.
