/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 00:00:00 by carbon-m          #+#    #+#             */
/*   Updated: 2026/01/22 13:53:14 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "alcarril.h"
# include "carbon.h"

/*
	LIBRERIAS:
*/

//Self created APIs
# include "../libs/libft/libft.h"
# include "../libs/libft/get_next_line_bonus.h"
//Sistem APIs
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <math.h>
//MiniLibx APIS
# include "../libs/minilibx-linux/mlx.h"
# include "../libs/minilibx-linux/mlx_int.h"

/*
	BRIDGE STRUCTURES:
*/

typedef struct s_parse_bridge
{
	char	texture_paths[4][256];
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	char	grid[CARBON_MAX_ROWS][CARBON_MAX_COLUMS];
	float	player_x;
	float	player_y;
	float	player_angle;
	int		width;
	int		height;
}	t_parse_bridge;

/*
	BRIDGE FUNCTIONS:
*/

// Extrae datos de t_carbon_map a estructura puente
int		extract_parse_data(t_carbon_map *cmap, t_parse_bridge *bridge);

// Convierte estructura puente a t_map y t_player de alcarril
int		populate_game_structures(t_parse_bridge *bridge,
			t_map *alcarril_map, t_player *alcarril_player);

// Función principal de integración
int		integrate_parsing_to_game(char *map_file,
			t_map *alcarril_map, t_player *alcarril_player);

// Bridge utility functions
void	copy_textures(t_carbon_map *cmap, t_parse_bridge *bridge);
void	copy_colors_and_player(t_carbon_map *cmap, t_parse_bridge *bridge);
void	copy_map_grid(t_carbon_map *cmap, t_parse_bridge *bridge);
int		is_floor_char(char c);
void	populate_colors(t_parse_bridge *bridge, t_map *alcarril_map);

#endif
