# Cub3D Integrated Project

Este es el proyecto cub3d integrado que combina la funcionalidad de parsing de carboncub con el sistema de renderizado de alexpruebas.

## ¿Qué se hizo?

1. **Se preservó todo el código de alexpruebas sin modificaciones** - La carpeta `integrated_cub3d` es una copia completa de alexpruebas.

2. **Se implementó un sistema de parsing completo** que puede leer archivos `.cub` con el formato estándar:
   - Texturas para las paredes (NO, SO, WE, EA)
   - Colores del suelo y techo (F, C) 
   - Mapa con paredes (1), espacios (0) y posición inicial del jugador (N/S/E/W)

3. **Se creó un sistema de conversión** que traduce el mapa parseado al formato que espera el sistema de alexpruebas.

## Estructura del proyecto integrado

```
integrated_cub3d/
├── Makefile                    # Actualizado para incluir archivos de parsing
├── cube3D                      # Ejecutable final
├── inc/
│   ├── alcarril.h             # Headers de alexpruebas (sin cambios)
│   ├── carbon.h               # Actualizado con estructuras de parsing
│   └── cube3D.h               # Header principal (sin cambios)
├── libs/                      # Librerías (copiadas de alexpruebas)
├── assets/                    # Mapas y texturas de prueba
├── src/
│   ├── events/                # Sistema de eventos (sin cambios)
│   ├── mains/
│   │   ├── main.c             # Main actualizado para usar parsing
│   │   └── main_debug.c       # Versión debug para probar parsing
│   ├── mlx_init_close/        # Sistema MLX (sin cambios)
│   ├── parsing/               # NUEVOS archivos de parsing
│   │   ├── map_parser.c       # Parser de archivos .cub
│   │   └── map_converter.c    # Conversor a formato del juego
│   ├── render/                # Sistema de renderizado (sin cambios)
│   └── testing/
└── obj/                       # Archivos objeto compilados
```

## Archivos nuevos añadidos

- `src/parsing/map_parser.c` - Parsea archivos .cub
- `src/parsing/map_converter.c` - Convierte mapas parseados al formato del juego
- `src/mains/main_debug.c` - Versión debug para testing
- `inc/carbon.h` actualizado con estructuras de parsing

## Uso

### Compilación
```bash
make
```

### Ejecución
```bash
./cube3D <archivo_mapa.cub>
```

Ejemplo:
```bash
./cube3D assets/maps/good/other/works.cub
```

### Testing del parser
También se puede compilar una versión debug que solo testea el parser:
```bash
cc -Wall -Wextra -Werror -Iinc/ src/mains/main_debug.c src/parsing/map_parser.c src/parsing/map_converter.c -Llibs/libft -lft -o debug_parser
./debug_parser assets/maps/good/other/works.cub
```

## Formato de archivos .cub

Los archivos de mapa deben seguir este formato:

```
NO textures/north_texture.xpm
SO textures/south_texture.xpm  
WE textures/west_texture.xpm
EA textures/east_texture.xpm

F 220,100,0
C 225,30,0

1111111111111
1000000000001
1000N00000001
1000000000001
1111111111111
```

Donde:
- `NO/SO/WE/EA` son las texturas para cada dirección
- `F` es el color del suelo en RGB
- `C` es el color del techo en RGB  
- El mapa usa `1` para paredes, `0` para espacios, y `N/S/E/W` para la posición inicial del jugador

## Controles

- `W/A/S/D` - Movimiento del jugador
- `Flecha izquierda/derecha` - Rotación
- `ESC` - Salir del programa

## Integración realizada

1. **Sistema de parsing**: Implementado desde cero para leer archivos .cub estándar
2. **Conversión de coordenadas**: El parser convierte las coordenadas del mapa al sistema de coordenadas que usa el renderizador de alexpruebas
3. **Preservación del código existente**: Todo el código de renderizado, eventos y MLX de alexpruebas se mantiene intacto
4. **Sistema de validación**: Valida que el mapa tenga formato correcto, un solo jugador, texturas válidas, etc.

## Tested con

Los siguientes mapas han sido probados exitosamente:
- `assets/maps/good/other/works.cub`
- `assets/maps/good/other/subject_map.cub`
- Otros mapas en la carpeta `assets/maps/good/`

## Notas técnicas

- El sistema de coordenadas del jugador se convierte de píxeles de pantalla a coordenadas de celda del mapa
- Las texturas y colores se parsean correctamente pero el sistema de renderizado actual usa colores sólidos  
- El mapa se adapta automáticamente al tamaño máximo definido en las constantes `MAX_ROWS` y `MAX_COLUMS`
- Se preserva toda la funcionalidad de movimiento y colisiones del sistema original

## 🔧 Installation

### Cloning the Repository

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/cube3D.git
   ```

2. **Navigate to the project directory**:
   ```bash
   cd cube3D
   ```

3. **Initialize and update submodules**: This is necesary to download miniLibx dependencys.
   ```bash
   git submodule update --init --recursive
   ```

---

### Cloning with Submodules (Alternative Method)

1. **Clone the repository along with its submodules**:
   ```bash
   git clone --recurse-submodules https://github.com/your-username/cube3D.git
   ```

2. **Navigate to the project directory**:
   ```bash
   cd cube3D
   ```

---

Now you are ready to proceed with the next steps of the project setup!

## usage
proyect strcuture
bonus features and improvements
expliacion de raycasting y renderizacion (resources)
contribution
license


## MiniLibX, Xlib y el servidor X11

El **servidor X11** es una subcapa del sistema operativo **Linux/UNIX** encargada de la gestión del entorno gráfico. Su función principal es manejar la comunicación entre el hardware gráfico, el sistema operativo y las aplicaciones y procesos **clientes**, proporcionando servicios como la creación de ventanas, la gestión de eventos de entrada (teclado y ratón) y el renderizado básico en pantalla.

La **MiniLibX** es una **API gráfica** construida sobre la **API de Xlib**, la biblioteca que permite al **cliente X11** (proceso o aplicacion) comunicarse directamente con el **servidor X11**, que actúa como el **servidor gráfico**.

En este contexto, nuestro programa actúa como un **cliente X11**, y mediante la **MiniLibX**, que abstrae y simplifica el uso de Xlib, podemos **manipular los componentes del sistema X11** —como ventanas, buffers de imagen y eventos— para llevar a cabo el **proceso de renderizado**. Esta capa de abstracción nos permite centrarnos en la lógica del motor gráfico y en el cálculo del renderizado, sin interactuar directamente con las complejidades de la API nativa de Xlib.


