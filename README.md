# Proyecto Cub3D Unificado

Este proyecto integra el sistema de parsing de mapas (carbon) con el motor gráfico (alcarril) del proyecto cub3D de 42.

## Estructura del Proyecto

```
cub3d_unified/
├── inc/                    # Headers
│   ├── carbon.h           # Header de parsing (sin modificar)
│   ├── alcarril.h         # Header del motor gráfico (sin modificar)
│   └── cube3D.h           # Header con funciones puente
├── src/
│   ├── parsing/           # Código de parsing (carbon)
│   ├── render/            # Renderizado (alcarril)
│   ├── moves/             # Movimiento (alcarril)
│   ├── events/            # Eventos (alcarril)
│   ├── ambiances/         # Ambientes (alcarril)
│   ├── mlx_init_close/    # Inicialización MLX (alcarril)
│   ├── bridge/            # Funciones de integración
│   │   └── bridge.c       # 4 funciones puente
│   └── mains/
│       └── main_unified.c # Main integrado
├── libs/                   # Librerías
│   ├── libft/
│   └── minilibx-linux/
├── assets/                 # Recursos
│   ├── textures/
│   └── maps/
├── obj/                    # Archivos objeto
├── Makefile               # Makefile unificado
└── README.md              # Este archivo
```

## Funciones Puente

Las funciones en `bridge.c` conectan ambas partes sin modificar el código original:

1. **extract_parse_data()**: Extrae datos de carbon.t_map a t_parse_data
2. **populate_game_structures()**: Convierte t_parse_data a alcarril.t_map y alcarril.t_player
3. **rgb_to_hex()**: Convierte RGB a hexadecimal
4. **integrate_parsing_to_game()**: Función principal que coordina la integración

## Compilación

```bash
make
```

## Ejecución

```bash
./cub3D test_map.cub
```

## Características

- ✅ **Código original intacto**: Carbon y alcarril sin modificaciones
- ✅ **Funciones bridge mínimas**: Solo 4 funciones de integración
- ✅ **Compatible con norminette**: Todas las funciones ≤25 líneas
- ✅ **Parsing completo**: Validación de mapas .cub
- ✅ **Motor gráfico completo**: Renderizado 3D, controles, texturas

## Flujo de Ejecución

1. Main recibe argumento de archivo .cub
2. `integrate_parsing_to_game()` llama a `parse_map_file()` (carbon)
3. `extract_parse_data()` extrae datos a estructura puente
4. `populate_game_structures()` llena estructuras de alcarril
5. El motor gráfico inicia con los datos parseados
6. El juego se ejecuta normalmente

## Notas

- Las texturas deben estar en rutas relativas desde el ejecutable
- Los mapas deben cumplir con la norma de cub3D de 42
- El proyecto compila con flags `-Wall -Wextra -Werror`
