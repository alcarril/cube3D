/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:00:00 by carbon-m          #+#    #+#             */
/*   Updated: 2026/01/22 13:53:14 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"
#include <string.h>

int	extract_parse_data(t_carbon_map *cmap, t_parse_bridge *bridge)
{
	copy_textures(cmap, bridge);
	copy_colors_and_player(cmap, bridge);
	copy_map_grid(cmap, bridge);
	return (1);
}

static void	copy_grid_data(t_parse_bridge *bridge, t_map *alcarril_map)
{
	int		i;
	int		j;

	i = -1;
	while (++i < (int)alcarril_map->max_rows && i < CARBON_MAX_ROWS)
	{
		j = -1;
		while (++j < (int)alcarril_map->max_columns && j < CARBON_MAX_COLUMS)
		{
			if (bridge->grid[i][j] == '1')
				alcarril_map->map_grids[i][j] = 1;
			else if (is_floor_char(bridge->grid[i][j]))
				alcarril_map->map_grids[i][j] = 0;
			else
				alcarril_map->map_grids[i][j] = 1;
		}
	}
}

int	populate_game_structures(t_parse_bridge *bridge,
		t_map *alcarril_map, t_player *alcarril_player)
{
	int			i;

	i = -1;
	while (++i < 4)
	{
		alcarril_map->texture_paths[i] = ft_strdup(bridge->texture_paths[i]);
		if (!alcarril_map->texture_paths[i])
			return (0);
	}
	populate_colors(bridge, alcarril_map);
	alcarril_map->max_columns = bridge->width;
	alcarril_map->max_rows = bridge->height;
	copy_grid_data(bridge, alcarril_map);
	alcarril_player->pos_x = bridge->player_x;
	alcarril_player->pos_y = bridge->player_y;
	alcarril_player->angle = bridge->player_angle;
	return (1);
}

int	integrate_parsing_to_game(char *map_file,
		t_map *alcarril_map, t_player *alcarril_player)
{
	t_carbon_map	carbon_map;
	t_parse_bridge	bridge;

	if (parse_map_file(map_file, &carbon_map) != 1)
	{
		cleanup_map(&carbon_map);
		return (0);
	}
	if (extract_parse_data(&carbon_map, &bridge) != 1)
	{
		cleanup_map(&carbon_map);
		return (0);
	}
	if (populate_game_structures(&bridge, alcarril_map,
			alcarril_player) != 1)
	{
		cleanup_map(&carbon_map);
		return (0);
	}
	cleanup_map(&carbon_map);
	return (1);
}
