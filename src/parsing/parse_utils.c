/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alejandro         #+#    #+#             */
/*   Updated: 2025/12/29 17:01:31 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/carbon.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	init_map(t_map *map)
{
	if (!map)
		return (0);
	
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	
	map->textures.north = NULL;
	map->textures.south = NULL;
	map->textures.west = NULL;
	map->textures.east = NULL;
	
	map->floor.r = 0;
	map->floor.g = 0;
	map->floor.b = 0;
	map->floor.rgb = 0;
	
	map->ceiling.r = 0;
	map->ceiling.g = 0;
	map->ceiling.b = 0;
	map->ceiling.rgb = 0;
	
	map->player.x = 0;
	map->player.y = 0;
	map->player.direction = '\0';
	map->player.angle = 0;
	
	return (1);
}

void	cleanup_map(t_map *map)
{
	int	i;

	if (!map)
		return;
	
	if (map->grid)
	{
		i = 0;
		while (i < map->height && map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	
	if (map->textures.north)
		free(map->textures.north);
	if (map->textures.south)
		free(map->textures.south);
	if (map->textures.west)
		free(map->textures.west);
	if (map->textures.east)
		free(map->textures.east);
}