/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by carbon-m         #+#    #+#             */
/*   Updated: 2025/12/29 00:00:00 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/carbon.h"

void	print_map_info(t_map *map)
{
	int	i;

	if (!map)
		return;
	
	printf("=== MAP INFO ===\n");
	printf("Dimensions: %dx%d\n", map->width, map->height);
	printf("Player: (%.1f, %.1f) facing %c (angle: %.2f)\n", 
		map->player.x, map->player.y, map->player.direction, map->player.angle);
	printf("Floor: RGB(%d,%d,%d) = 0x%06X\n", 
		map->floor.r, map->floor.g, map->floor.b, map->floor.rgb);
	printf("Ceiling: RGB(%d,%d,%d) = 0x%06X\n", 
		map->ceiling.r, map->ceiling.g, map->ceiling.b, map->ceiling.rgb);
	printf("Textures:\n");
	printf("  North: %s\n", map->textures.north ? map->textures.north : "NULL");
	printf("  South: %s\n", map->textures.south ? map->textures.south : "NULL");
	printf("  West:  %s\n", map->textures.west ? map->textures.west : "NULL");
	printf("  East:  %s\n", map->textures.east ? map->textures.east : "NULL");
	
	printf("Map grid:\n");
	i = 0;
	while (i < map->height && map->grid[i])
	{
		printf("%2d: |%s|\n", i, map->grid[i]);
		i++;
	}
	printf("================\n");
}

void	print_parse_progress(char *step, int success)
{
	if (success)
		printf("%s completed successfully\n", step);
	else
		printf("%s failed\n", step);
}

void	print_texture_info(t_texture *textures)
{
	if (!textures)
		return;
	printf("=== TEXTURE INFO ===\n");
	printf("North: %s\n", textures->north ? textures->north : "NOT SET");
	printf("South: %s\n", textures->south ? textures->south : "NOT SET");
	printf("West:  %s\n", textures->west ? textures->west : "NOT SET");
	printf("East:  %s\n", textures->east ? textures->east : "NOT SET");
	printf("====================\n");
}

void	print_color_info(t_color *floor, t_color *ceiling)
{
	if (!floor || !ceiling)
		return;
	printf("=== COLOR INFO ===\n");
	printf("Floor:   RGB(%d,%d,%d) = 0x%06X\n", 
		floor->r, floor->g, floor->b, floor->rgb);
	printf("Ceiling: RGB(%d,%d,%d) = 0x%06X\n", 
		ceiling->r, ceiling->g, ceiling->b, ceiling->rgb);
	printf("==================\n");
}

void	print_player_info(t_player *player)
{
	if (!player)
		return;
	printf("=== PLAYER INFO ===\n");
	printf("Position: (%.1f, %.1f)\n", player->x, player->y);
	printf("Direction: %c\n", player->direction);
	printf("Angle: %.2f radians (%.1f degrees)\n", 
		player->angle, player->angle * 180.0 / 3.14159265359);
	printf("===================\n");
}