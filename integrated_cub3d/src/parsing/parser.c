/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:00:00 by integrated        #+#    #+#             */
/*   Updated: 2026/01/04 12:42:58 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

static char	*ft_strtrim_all(char *str)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	start = str;
	while (*start == ' ' || *start == '\t')
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, start, len + 1);
	return (result);
}

static int	parse_color_direct(char *line, int color_array[3])
{
	char	**rgb_parts;
	int		i;

	if (!line || !color_array)
		return (0);
	rgb_parts = ft_split(line, ',');
	if (!rgb_parts)
		return (0);
	i = 0;
	while (rgb_parts[i])
		i++;
	if (i != 3)
	{
		while (--i >= 0)
			free(rgb_parts[i]);
		free(rgb_parts);
		return (0);
	}
	color_array[0] = ft_atoi(ft_strtrim_all(rgb_parts[0])); // R
	color_array[1] = ft_atoi(ft_strtrim_all(rgb_parts[1])); // G
	color_array[2] = ft_atoi(ft_strtrim_all(rgb_parts[2])); // B
	i = 0;
	while (rgb_parts[i])
		free(rgb_parts[i++]);
	free(rgb_parts);
	return ((color_array[0] >= 0 && color_array[0] <= 255) &&
			(color_array[1] >= 0 && color_array[1] <= 255) &&
			(color_array[2] >= 0 && color_array[2] <= 255));
}

static int	parse_texture_direct(char *line, t_map *map)
{
	char	*trimmed;
	char	*texture_path;

	if (!line || !map)
		return (0);
	trimmed = ft_strtrim_all(line);
	if (!trimmed)
		return (0);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
	{
		texture_path = ft_strtrim_all(trimmed + 3);
		if (map->texture_north)
			free(map->texture_north);
		map->texture_north = texture_path;
	}
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
	{
		texture_path = ft_strtrim_all(trimmed + 3);
		if (map->texture_south)
			free(map->texture_south);
		map->texture_south = texture_path;
	}
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
	{
		texture_path = ft_strtrim_all(trimmed + 3);
		if (map->texture_west)
			free(map->texture_west);
		map->texture_west = texture_path;
	}
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
	{
		texture_path = ft_strtrim_all(trimmed + 3);
		if (map->texture_east)
			free(map->texture_east);
		map->texture_east = texture_path;
	}
	else
	{
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}

static int	parse_color_line_direct(char *line, t_map *map)
{
	char	*trimmed;
	char	*color_values;

	if (!line || !map)
		return (0);
	trimmed = ft_strtrim_all(line);
	if (!trimmed)
		return (0);
	if (ft_strncmp(trimmed, "F ", 2) == 0)
	{
		color_values = ft_strtrim_all(trimmed + 2);
		if (!parse_color_direct(color_values, map->floor_color))
		{
			free(color_values);
			free(trimmed);
			return (0);
		}
		free(color_values);
	}
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
	{
		color_values = ft_strtrim_all(trimmed + 2);
		if (!parse_color_direct(color_values, map->ceiling_color))
		{
			free(color_values);
			free(trimmed);
			return (0);
		}
		free(color_values);
	}
	else
	{
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || 
			c == 'E' || c == 'W' || c == ' ');
}

static int	is_map_line(char *line)
{
	int	i;
	char	*trimmed;

	if (!line)
		return (0);
	trimmed = ft_strtrim_all(line);
	if (!trimmed || ft_strlen(trimmed) == 0)
	{
		if (trimmed)
			free(trimmed);
		return (0);
	}
	i = 0;
	while (trimmed[i])
	{
		if (!is_valid_map_char(trimmed[i]))
		{
			free(trimmed);
			return (0);
		}
		i++;
	}
	free(trimmed);
	return (1);
}

static void	init_map_direct(t_map *map, t_player *player)
{
	int	i, j;

	if (!map || !player)
		return ;
	// Inicializar texturas
	map->texture_north = NULL;
	map->texture_south = NULL;
	map->texture_west = NULL;
	map->texture_east = NULL;
	
	// Inicializar colores (valores inválidos para detectar si se han seteado)
	map->floor_color[0] = -1;
	map->floor_color[1] = -1; 
	map->floor_color[2] = -1;
	map->ceiling_color[0] = -1;
	map->ceiling_color[1] = -1;
	map->ceiling_color[2] = -1;
	
	// Limpiar mapa con muros
	i = 0;
	while (i < MAX_ROWS)
	{
		j = 0;
		while (j < MAX_COLUMS)
		{
			map->map_grids[i][j] = WALL;
			j++;
		}
		i++;
	}
	
	map->max_columns = 0;
	map->max_rows = 0;
	
	// Inicializar player con valores inválidos
	player->pos_x = -1.0f;
	player->pos_y = -1.0f;
	player->angle = 0.0f;
}

static float	get_player_angle_direct(char direction)
{
	if (direction == 'N')
		return (270.0f);
	else if (direction == 'S')
		return (90.0f);
	else if (direction == 'E')
		return (0.0f);
	else if (direction == 'W')
		return (180.0f);
	return (0.0f);
}

static int	process_map_direct(char **map_lines, int map_count, t_map *map, t_player *player)
{
	int	y, x, max_width;
	int	player_count;
	char player_char;

	max_width = 0;
	player_count = 0;
	
	// Primera pasada: encontrar jugador y calcular dimensiones
	y = 0;
	while (y < map_count)
	{
		int len = ft_strlen(map_lines[y]);
		if (len > max_width)
			max_width = len;
		x = 0;
		while (map_lines[y][x])
		{
			if (map_lines[y][x] == 'N' || map_lines[y][x] == 'S' ||
				map_lines[y][x] == 'E' || map_lines[y][x] == 'W')
			{
				player->pos_x = x + 0.5f;  // Centro de la celda
				player->pos_y = y + 0.5f;  // Centro de la celda
				player->origin[0] = x;
				player->origin[1] = y;
				player_char = map_lines[y][x];
				player->angle = get_player_angle_direct(player_char);
				player_count++;
			}
			x++;
		}
		y++;
	}
	
	if (player_count != 1)
		return (0);  // Debe haber exactamente un jugador
	
	// Segunda pasada: llenar el mapa
	y = 0;
	while (y < map_count && y < MAX_ROWS)
	{
		x = 0;
		while (x < (int)ft_strlen(map_lines[y]) && x < MAX_COLUMS)
		{
			if (map_lines[y][x] == '1' || map_lines[y][x] == ' ')
				map->map_grids[y][x] = WALL;
			else if (map_lines[y][x] == '0' || 
					 map_lines[y][x] == 'N' || map_lines[y][x] == 'S' ||
					 map_lines[y][x] == 'E' || map_lines[y][x] == 'W')
				map->map_grids[y][x] = FLOOR;
			x++;
		}
		y++;
	}
	
	map->max_columns = (max_width > MAX_COLUMS) ? MAX_COLUMS : max_width;
	map->max_rows = (map_count > MAX_ROWS) ? MAX_ROWS : map_count;
	
	return (1);
}

int	parse_cub_file(char *filename, t_map *map, t_player *player)
{
	int		fd;
	char	*line;
	char	**map_lines;
	int		map_count;
	int		parsing_map;

	if (!filename || !map || !player)
		return (0);
		
	init_map_direct(map, player);
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
		
	map_lines = malloc(sizeof(char *) * 1024);
	if (!map_lines)
	{
		close(fd);
		return (0);
	}
	
	map_count = 0;
	parsing_map = 0;
	
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strlen(ft_strtrim_all(line)) == 0)
		{
			free(line);
			continue;
		}
		
		if (!parsing_map && is_map_line(line))
			parsing_map = 1;
			
		if (parsing_map)
		{
			if (is_map_line(line))
			{
				map_lines[map_count] = ft_strdup(line);
				map_count++;
			}
		}
		else
		{
			if (!parse_texture_direct(line, map) && 
				!parse_color_line_direct(line, map))
			{
				free(line);
				continue;
			}
		}
		free(line);
	}
	close(fd);
	
	if (map_count == 0)
	{
		free(map_lines);
		return (0);
	}
	
	// Procesar mapa y encontrar jugador
	int result = process_map_direct(map_lines, map_count, map, player);
	
	// Liberar líneas del mapa
	int i = 0;
	while (i < map_count)
	{
		free(map_lines[i]);
		i++;
	}
	free(map_lines);
	
	return (result);
}

int	validate_cub_map(t_map *map, t_player *player)
{
	if (!map || !player)
		return (0);

	// Verificar que tenemos todas las texturas
	if (!map->texture_north || !map->texture_south ||
		!map->texture_west || !map->texture_east)
		return (0);

	// Verificar que tenemos los colores
	if (map->floor_color[0] == -1 || map->ceiling_color[0] == -1)
		return (0);

	// Verificar que tenemos un jugador válido
	if (player->pos_x == -1.0f || player->pos_y == -1.0f)
		return (0);

	return (1);
}

void	free_map_textures(t_map *map)
{
	if (!map)
		return ;
	if (map->texture_north)
		free(map->texture_north);
	if (map->texture_south)
		free(map->texture_south);
	if (map->texture_west)
		free(map->texture_west);
	if (map->texture_east)
		free(map->texture_east);
}