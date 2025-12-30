/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alejandro         #+#    #+#             */
/*   Updated: 2025/12/25 19:10:56 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/carbon.h"

int	parse_map_grid(t_parse *data, t_map *map, int start_line)
{
	int	i;
	int	j;

	if (!data || !map || !data->file_content)
		return (0);
	
	// Contar líneas del mapa
	i = start_line;
	while (data->file_content[i])
		i++;
	map->height = i - start_line;
	
	if (map->height == 0)
	{
		printf("Error: No map found\n");
		return (0);
	}
	
	// Encontrar ancho máximo
	map->width = find_max_width(data->file_content, start_line);
	if (map->width == 0)
	{
		printf("Error: Map has no width\n");
		return (0);
	}
	
	// Crear grid del mapa
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (0);
	
	// Copiar y normalizar líneas del mapa
	j = 0;
	i = start_line;
	while (data->file_content[i])
	{
		map->grid[j] = normalize_map_line(data->file_content[i], map->width);
		if (!map->grid[j])
			return (0);
		if (!find_player_position(map->grid[j], &map->player, j))
			return (0);
		i++;
		j++;
	}
	return (1);
}

char	*normalize_map_line(char *line, int width)
{
	char	*normalized;
	int		i;
	int		len;

	if (!line || width <= 0)
		return (NULL);
	
	normalized = ft_calloc(width + 1, sizeof(char));
	if (!normalized)
		return (NULL);
	
	len = ft_strlen(line);
	i = 0;
	while (i < width)
	{
		if (i < len)
			normalized[i] = line[i];
		else
			normalized[i] = ' ';
		i++;
	}
	return (normalized);
}

int	find_max_width(char **content, int start_line)
{
	int	max_width;
	int	current_width;
	int	i;

	if (!content)
		return (0);
	
	max_width = 0;
	i = start_line;
	while (content[i])
	{
		current_width = ft_strlen(content[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}