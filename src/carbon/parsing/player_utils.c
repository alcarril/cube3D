/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/25 08:54:12 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/carbon.h"

int	check_multiple_players(t_carbon_map *map)
{
	if (map->player_found)
	{
		printf("Error: Multiple players found\n");
		return (0);
	}
	return (1);
}

int	validate_player_space(t_carbon_map *map, int x, int y)
{
	int	open_spaces;

	open_spaces = 0;
	
	// Check all adjacent positions (up, down, left, right)
	if (y > 0 && (map->map_grids[y-1][x] == '0' || 
		map->map_grids[y-1][x] == 'N' || map->map_grids[y-1][x] == 'S' ||
		map->map_grids[y-1][x] == 'E' || map->map_grids[y-1][x] == 'W'))
		open_spaces++;
		
	if (y < map->height - 1 && (map->map_grids[y+1][x] == '0' ||
		map->map_grids[y+1][x] == 'N' || map->map_grids[y+1][x] == 'S' ||
		map->map_grids[y+1][x] == 'E' || map->map_grids[y+1][x] == 'W'))
		open_spaces++;
		
	if (x > 0 && (map->map_grids[y][x-1] == '0' ||
		map->map_grids[y][x-1] == 'N' || map->map_grids[y][x-1] == 'S' ||
		map->map_grids[y][x-1] == 'E' || map->map_grids[y][x-1] == 'W'))
		open_spaces++;
		
	if (x < map->width - 1 && (map->map_grids[y][x+1] == '0' ||
		map->map_grids[y][x+1] == 'N' || map->map_grids[y][x+1] == 'S' ||
		map->map_grids[y][x+1] == 'E' || map->map_grids[y][x+1] == 'W'))
		open_spaces++;
	
	if (open_spaces == 0)
	{
		printf("Error: Player is isolated in a 1x1 space at (%d, %d)\n", x, y);
		return (0);
	}
	
	return (1);
}

void	set_player_data(t_carbon_map *map, int i, int y, char direction)
{
	map->player.x = i + 0.5;
	map->player.y = y + 0.5;
	map->player.direction = direction;
	set_player_angle(&map->player);
	map->player_found = 1;
}

int	find_player_position(char *line, t_carbon_map *map, int y)
{
	int	i;

	if (!line || !map)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (!check_multiple_players(map))
				return (0);
			set_player_data(map, i, y, line[i]);
			line[i] = '0';
		}
		i++;
	}
	return (1);
}

void	set_player_angle(t_carbon_player *player)
{
	if (!player)
		return ;
	if (player->direction == 'N')
		player->angle = 90.0;
	else if (player->direction == 'S')
		player->angle = 270.0;
	else if (player->direction == 'E')
		player->angle = 0.0;
	else if (player->direction == 'W')
		player->angle = 180.0;
}
