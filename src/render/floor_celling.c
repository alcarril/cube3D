/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_celling_fps.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:45:21 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/09 17:17:03 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	render_floor_and_ceiling(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < mlx->win_height / 2)
	{
		x = 0;
		while (x < mlx->win_width)
		{
			buffering_pixel(x, y, mlx, mlx->map->ceiling_color_hex);
			x++;
		}
		y++;
	}
	while (y < mlx->win_height)
	{
		x = 0;
		while (x < mlx->win_width)
		{
			buffering_pixel(x, y, mlx, mlx->map->floor_color_hex);
			x++;
		}
		y++;
	}
}


void	render_floor_and_ceiling_speed(t_mlx *mlx)
{
	int	y;
	int	offset;
	int	color;

	color = mlx->map->ceiling_color_hex;
	y = 0;
	while (y < mlx->win_height / 2)
	{
		offset = y * mlx->line_length;
		memset(mlx->bit_map_address + offset, color, mlx->win_width * (mlx->bits_per_pixel / 8));
		y++;
	}
	color = mlx->map->floor_color_hex;
	while (y < mlx->win_height)
	{
		offset = y * mlx->line_length;
		memset(mlx->bit_map_address + offset, color, mlx->win_width * (mlx->bits_per_pixel / 8));
		y++;
	}
}

