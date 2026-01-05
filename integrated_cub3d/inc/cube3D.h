/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 00:00:00 by carbon            #+#    #+#             */
/*   Updated: 2026/01/04 17:46:16 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H

/*
	LIBRERIAS EXTERNAS:
*/

// Self created APIs
#include "../libs/libft/libft.h"
#include "../libs/libft/get_next_line_bonus.h"

// System APIs
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>

// MiniLibx APIs
#include "../libs/minilibx-linux/mlx.h"
#include "../libs/minilibx-linux/mlx_int.h"

/*
	DEFINES Y CONSTANTES:
*/

#define	WIDTH 640
#define	HEIGHT 480

#define	ESC 65307
#define	W 119
#define	A 97
#define	S 115
#define	D 100
#define	LEFT 65361
#define	RIGHT 65363
#define	UP 65362
#define	DOWN 65364

#define	MAX_ROWS 100
#define	MAX_COLUMS 150

// Constantes de parsing
#define MAX_LINE_LENGTH 1024

// Defines adicionales del motor gráfico
#define MINI_WIDTH 4
#define MINI_HEIGHT 4

#define WALL 1
#define FLOOR 0

#define X 1
#define Y 0

#define VERTICAL 1
#define HORIZONTAL 0

#define PI 3.14159265
#define EPSILON 0.15f
#define FRICTION 0.7f

/*
	ESTRUCTURAS DE DATOS:
*/

/**
 * @brief Estructura que contiene información del jugador
 * Incluye posición, ángulo, velocidades y estados de teclas
 */
typedef struct	s_player_data
{
	int		origin[2]; //default WITH/2 && HEIGHT/2 -> fix_map_inital position
	float	pos_x; //t0 = origin[0]
	float	pos_y; //t0 = origin[1]
	float	angle; //grades
	float	speed; //h o modul del vector de movimiento
	float	r_speed; //spin angle speed
	
	// on/off keys
	bool	move_up;
	bool	move_down;
	bool	move_left;
	bool	move_right;
	bool	r_counterclockwise;
	bool	r_clockwise;

	//on /off mouse
	//rotaciones
	//rueda de raton para zoom minimapa

	//cvision data
    double	*fov_distances; // Array de distancias hasta las paredes
    float	fov;            // Campo de visión del jugador (en grados)
	bool	fish_eye;
	bool	euclidean;
}	t_player;

/**
 * @brief Estructura que contiene el mapa del juego
 * Incluye la grilla de caracteres, texturas y colores
 */
typedef struct	s_map
{
	unsigned int	max_columns; //x
	unsigned int	max_rows; //y
	char map_grids[MAX_ROWS][MAX_COLUMS];
	
	// Texturas parseadas del archivo .cub
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;
	char	*texture_east;
	
	// Colores parseados del archivo .cub (RGB)
	int		floor_color[3];		// R, G, B
	int		ceiling_color[3];	// R, G, B
}	t_map;

/**
 * @brief Estructura principal que contiene todos los componentes de MLX
 */
typedef struct	s_mlx_api_components
{
	void	*mlx_var;
	void	*mlx_window;
	void	*mlx_img;
	char	*win_name;

	//offsetinfo
	char	*bit_map_address;
	char	*bit_map_address_copy;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	//
	t_player	*player;
	t_map		*map;

}	t_mlx;

/**
 * @brief Estructura para datos de frame (futura implementación)
 */
typedef struct	s_frame_data
{
	//minimap width
	//minimap height
	//person epsilon
	// minimap scale
	//minimap on/off
	//minimap zoom
	//minimap traslation

	//map cells
	//win cords

	//exta utils
	

}	t_frame;

/**
 * @brief Estructura para rayos en el raycasting
 */
typedef struct	s_ray
{
	float			raydir[2];
	float			delta[2];
	float			sidedist[2];
	int				map[2];
	unsigned int	step[2];
	float			perp_wall_dist;
	
	
}	t_ray;

/*
	PROTOTIPOS DE FUNCIONES - MLX Y RENDERING:
*/

void	buffering_pixel(int x, int y, t_mlx *mlx, int color);
int 	render_frame2D(t_mlx *mlx);
int		close_handler(t_mlx *mlx);
int		key_press(int keysym, t_mlx *mlx);
int		key_release(int keysym, t_mlx *mlx);
void	move_player(t_mlx *mlx);
void	rotate_player(t_mlx	*mlx);
char	init_mlx_components(t_mlx *mlx);
void	create_hooks(t_mlx *mlx);
void	destroy_mlx_componets(int (*f)(), int (*g)(), int (*t)(), t_mlx *mlx);
void 	setup_player(t_mlx *mlx);
int		throw_rays(t_mlx *mlx);

/*
	PROTOTIPOS DE FUNCIONES - PARSING:
*/

int		parse_cub_file(char *filename, t_map *map, t_player *player);
int		validate_cub_map(t_map *map, t_player *player);
void	free_map_textures(t_map *map);

#endif