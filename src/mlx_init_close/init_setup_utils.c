/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_setup_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:20:39 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:30:10 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

void	get_minimapscale(t_mlx *mlx, float *scale)
{
	scale[X] = (float)(mlx->frame->mm_widht) / mlx->map->max_columns;
	scale[Y] = (float)(mlx->frame->mm_height) / mlx->map->max_rows;
}

void	init_floor_and_ceiling_colors(t_map *map)
{
	int	floor[3];
	int	ceiling[3];

	ft_memcpy(floor, map->floor_color, sizeof(floor));
	ft_memcpy(ceiling, map->ceiling_color, sizeof(ceiling));
	map->floor_color_hex = rgb_to_hex(floor[0], floor[1], floor[2]);
	map->ceiling_color_hex = rgb_to_hex(ceiling[0], ceiling[1], ceiling[2]);
}

void	setup_window_wh(t_mlx *mlx)
{
	float	rows_per_col;

	rows_per_col = 1;
	if (rows_per_col > 1)
	{
		mlx->win_width = BASE_WIDTH * rows_per_col;
		mlx->win_height = BASE_HEIGHT;
	}
	else
	{
		mlx->win_height = BASE_HEIGHT / rows_per_col;
		mlx->win_width = BASE_WIDTH;
	}
}

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
