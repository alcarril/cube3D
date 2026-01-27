overview
Demo
techstack used (tecnologies suited for the proyect)
requiriments and fetures (explicacion)

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


