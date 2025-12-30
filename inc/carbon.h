/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carbon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:15:03 by alejandro         #+#    #+#             */
/*   Updated: 2025/12/29 17:01:31 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CARBON_H
#define CARBON_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "../libs/libft/libft.h"
// #include "../libs/minilibx-linux/mlx.h"

/*
	DEFINES:
*/

/*
	STRUCTS:
*/

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	rgb;
}	t_color;

typedef struct s_player
{
	double	x;
	double	y;
	char	direction;
	double	angle;
}	t_player;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	t_texture	textures;
	t_color		floor;
	t_color		ceiling;
	t_player	player;
}	t_map;

typedef struct s_parse
{
	int		fd;
	char	*line;
	char	**file_content;
	int		texture_count;
	int		color_count;
	int		map_started;
	char	*filename;
}	t_parse;

// Parse main functions
int		parse_map_file(char *filename, t_map *map);
int		init_parse_data(t_parse *data, char *filename);
int		cleanup_parse(t_parse *data, int success);

// File reading functions
int		read_file_content(t_parse *data);
int		count_file_lines(int fd);

// Element parsing functions
int		parse_elements(t_parse *data, t_map *map);
int		parse_texture(char *line, t_map *map);
int		parse_color(char *line, t_map *map);
int		parse_map_grid(t_parse *data, t_map *map, int start_line);

// Validation functions
int		is_texture_line(char *line);
int		is_color_line(char *line);
int		is_empty_line(char *line);
int		validate_rgb_values(t_color *color);
int		validate_map(t_map *map);
int		validate_map_walls(t_map *map);
int		validate_map_characters(t_map *map);
int		validate_player_found(t_map *map);

// Map processing functions
char	*normalize_map_line(char *line, int width);
int		find_max_width(char **content, int start_line);
int		find_player_position(char *line, t_player *player, int y);
void	set_player_angle(t_player *player);

// Utility functions
void	free_split(char **split);
int		init_map(t_map *map);
void	cleanup_map(t_map *map);

// Debug functions (debug_utils.c)
void	print_map_info(t_map *map);
void	print_parse_progress(char *step, int success);
void	print_texture_info(t_texture *textures);
void	print_color_info(t_color *floor, t_color *ceiling);
void	print_player_info(t_player *player);

#endif