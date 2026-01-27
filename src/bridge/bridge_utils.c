/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:00:00 by carbon-m          #+#    #+#             */
/*   Updated: 2026/01/22 13:53:14 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

void	copy_textures(t_carbon_map *cmap, t_parse_bridge *bridge)
{
	ft_strlcpy(bridge->texture_paths[0], cmap->textures.north, 256);
	ft_strlcpy(bridge->texture_paths[1], cmap->textures.south, 256);
	ft_strlcpy(bridge->texture_paths[2], cmap->textures.west, 256);
	ft_strlcpy(bridge->texture_paths[3], cmap->textures.east, 256);
}

void	copy_colors_and_player(t_carbon_map *cmap, t_parse_bridge *bridge)
{
	bridge->floor_rgb[0] = cmap->floor.r;
	bridge->floor_rgb[1] = cmap->floor.g;
	bridge->floor_rgb[2] = cmap->floor.b;
	bridge->ceiling_rgb[0] = cmap->ceiling.r;
	bridge->ceiling_rgb[1] = cmap->ceiling.g;
	bridge->ceiling_rgb[2] = cmap->ceiling.b;
	bridge->player_x = cmap->player.x;
	bridge->player_y = cmap->player.y;
	bridge->player_angle = cmap->player.angle;
	bridge->width = cmap->width;
	bridge->height = cmap->height;
}

void	copy_map_grid(t_carbon_map *cmap, t_parse_bridge *bridge)
{
	int		i;
	int		j;

	i = -1;
	while (++i < CARBON_MAX_ROWS)
	{
		j = -1;
		while (++j < CARBON_MAX_COLUMS)
			bridge->grid[i][j] = cmap->map_grids[i][j];
	}
}

int	is_floor_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	populate_colors(t_parse_bridge *bridge, t_map *alcarril_map)
{
	alcarril_map->floor_color[0] = bridge->floor_rgb[0];
	alcarril_map->floor_color[1] = bridge->floor_rgb[1];
	alcarril_map->floor_color[2] = bridge->floor_rgb[2];
	alcarril_map->ceiling_color[0] = bridge->ceiling_rgb[0];
	alcarril_map->ceiling_color[1] = bridge->ceiling_rgb[1];
	alcarril_map->ceiling_color[2] = bridge->ceiling_rgb[2];
	alcarril_map->floor_color_hex = rgb_to_hex(bridge->floor_rgb[0],
			bridge->floor_rgb[1], bridge->floor_rgb[2]);
	alcarril_map->ceiling_color_hex = rgb_to_hex(bridge->ceiling_rgb[0],
			bridge->ceiling_rgb[1], bridge->ceiling_rgb[2]);
}
