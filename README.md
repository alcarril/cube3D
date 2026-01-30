# cub3D

*This project has been created as part of the 42 curriculum by carbon-m, alcarril.*

## Description

**cub3D** is a 3D graphics project inspired by the legendary Wolfenstein 3D game, the first FPS (First Person Shooter) in gaming history. This project is a comprehensive introduction to raycasting algorithms and real-time graphics programming using the MiniLibX graphics library.

The goal of cub3D is to create a dynamic 3D graphical representation of a maze from a first-person perspective. The player can navigate through the maze using keyboard controls and mouse movement, experiencing a pseudo-3D environment rendered through advanced raycasting techniques.

### Key Features

- **Real-time 3D rendering** using raycasting algorithms
- **Textured walls** with support for different textures based on wall orientation (North, South, East, West)
- **Player movement** with WASD keys and mouse look
- **Minimap display** for navigation assistance
- **Customizable floor and ceiling colors**
- **Advanced physics system** including gravity and air deceleration
- **Atmospheric effects** with fog and desaturation shaders
- **Performance optimizations** with vectorized operations and memory management enhancements
- **Map validation** ensuring proper maze structure and player positioning

### Technical Architecture

The project is structured in three main components:

1. **Parsing Module (carbon-m)**: Handles map file parsing, validation, and data structure initialization
2. **Graphics Engine (alcarril)**: Manages rendering, raycasting, physics, and user interaction
3. **Bridge Module**: Integrates parsing and graphics components seamlessly

## Instructions

### Prerequisites

- **Operating System**: Linux (tested on Ubuntu/Debian systems)
- **Compiler**: GCC with support for C99 standard
- **Libraries**: X11 development libraries
- **Make**: GNU Make utility

### Installation

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd cube3D
   ```

2. **Install system dependencies** (Ubuntu/Debian):
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential libx11-dev libxext-dev libbsd-dev
   ```

### Compilation

- **Standard version**:
  ```bash
  make
  ```

- **Bonus version** (with additional texture features):
  ```bash
  make bonus
  ```

- **Clean object files**:
  ```bash
  make clean
  ```

- **Complete cleanup**:
  ```bash
  make fclean
  ```

- **Recompile everything**:
  ```bash
  make re
  ```

### Execution

```bash
./cub3D <map_file.cub>
```

**Example**:
```bash
./cub3D assets/maps/good/self/matrix.cub
```

### Map File Format

Map files must have a `.cub` extension and follow this structure:

```
NO textures/path/to/north_texture.xpm
SO textures/path/to/south_texture.xpm
WE textures/path/to/west_texture.xpm
EA textures/path/to/east_texture.xpm

F 220,100,0
C 225,30,0

111111111111
100000000001
100000S00001
111111111111
```

- **Texture paths**: NO (North), SO (South), WE (West), EA (East)
- **Floor color**: F R,G,B (RGB values 0-255)
- **Ceiling color**: C R,G,B (RGB values 0-255)  
- **Map grid**: 
  - `1`: Wall
  - `0`: Empty space
  - `N/S/E/W`: Player starting position and orientation

### Controls

- **Movement**: `W` `A` `S` `D` keys
- **Mouse look**: Move mouse to look around
- **Minimap toggle**: `M` key
- **Graphics settings**: Various keys for fog, shaders, and visual effects
- **Exit**: `ESC` key or close window

## Resources

### Classic References

- **Computer Graphics Programming**:
  - [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)
  - [Ray-Casting Tutorial by F. Permadi](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)

- **Game Development**:
  - *Game Engine Black Book: Wolfenstein 3D* by Fabien Sanglard
  - [Wolfenstein 3D Source Code Analysis](https://github.com/id-Software/wolf3d)

- **Mathematical Foundations**:
  - *Real-Time Rendering* by Tomas Akenine-Möller
  - Linear Algebra and Trigonometry fundamentals for 3D graphics

- **MiniLibX Documentation**:
  - [42's MiniLibX Tutorial](https://github.com/42Paris/minilibx-linux)
  - [MLX Event Handling Guide](https://harm-smits.github.io/42docs/libs/minilibx)

### Additional Technical Documentation

For developers interested in extending or understanding the codebase:

- **Parsing Module**: See `src/parsing/` - handles `.cub` file validation and data extraction
- **Rendering Pipeline**: See `src/render/` - implements raycasting and texture mapping
- **Physics System**: See `src/moves/` - manages player movement and collision detection
- **Event System**: See `src/events/` - handles keyboard and mouse input processing
- **Bridge Architecture**: See `src/bridge/` - provides data integration between modules

---

**Project Status**: Completed and optimized  
**42 Project Grade**: Validated with bonus features  
**Performance**: Optimized for real-time rendering at 60+ FPS
