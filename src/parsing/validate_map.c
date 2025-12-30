/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alejandro         #+#    #+#             */
/*   Updated: 2025/12/25 19:10:56 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/carbon.h"

int	validate_map(t_map *map)
{
	if (!map)
		return (0);
	if (!validate_player_found(map))
		return (0);
	if (!validate_map_characters(map))
		return (0);
	if (!validate_map_walls(map))
		return (0);
	return (1);
}

int	validate_player_found(t_map *map)
{
	if (!map)
		return (0);
	if (map->player.direction == '\0')
	{
		printf("Error: No player found in map\n");
		return (0);
	}
	return (1);
}

int	validate_map_characters(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->grid)
		return (0);
	i = 0;
	while (i < map->height)
	{
		if (!map->grid[i])
			return (0);
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] != '0' && map->grid[i][j] != '1' && 
				map->grid[i][j] != ' ')
			{
				printf("Error: Invalid character '%c' at position (%d, %d)\n", 
					map->grid[i][j], j, i);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map_walls(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->grid)
		return (0);
	
	// Verificar que el mapa esté cerrado por paredes
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == '0')
			{
				// Verificar si hay un espacio adyacente en los bordes
				if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
				{
					printf("Error: Map not closed - floor at border (%d, %d)\n", j, i);
					return (0);
				}
				// Verificar espacios adyacentes
				if ((map->grid[i-1][j] == ' ') || (map->grid[i+1][j] == ' ') ||
					(map->grid[i][j-1] == ' ') || (map->grid[i][j+1] == ' '))
				{
					printf("Error: Map not closed - floor adjacent to space at (%d, %d)\n", j, i);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}