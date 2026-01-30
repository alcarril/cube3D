/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:26:17 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:35:28 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

bool	touch_wall(t_mlx *mlx, float x, float y)
{
	if (x < 0 || y < 0 || x >= mlx->map->max_columns || y >= mlx->map->max_rows)
		return (1);
	if (mlx->map->map_grids[(unsigned int)y][(unsigned int)x] == WALL)
		return (1);
	return (0);
}

void	draw_rays2d(t_mlx *mlx, float *scal_z)
{
	float	diferencial[2];
	float	fov_half;
	float	rad_pos;
	float	rad_dif;
	float	rad_end;

	fov_half = mlx->player->rad_fov / 2;
	rad_pos = (mlx->player->rad_angle - fov_half);
	rad_end = (mlx->player->rad_angle + fov_half);
	rad_dif = (mlx->player->rad_fov / (mlx->frame->mm_widht));
	while (rad_pos <= rad_end)
	{
		diferencial[X] = mlx->player->pos_x;
		diferencial[Y] = mlx->player->pos_y;
		draw_ray2d(mlx, diferencial, rad_pos, scal_z);
		rad_pos += rad_dif;
	}
}

void	draw_ray2d(t_mlx *mlx, float *differencial, float rad, float *scal_z)
{
	int		window[2];
	float	frame_offset[2];
	float	step;

	step = 0.1f;
	frame_offset[X] = mlx->frame->mm_offset[X];
	frame_offset[Y] = mlx->frame->mm_offset[Y];
	while (!touch_wall(mlx, differencial[X], differencial[Y]))
	{
		differencial[X] += step * cos(rad);
		differencial[Y] += step * -sin(rad);
		window[X] = (differencial[X] - frame_offset[X]) * scal_z[X];
		window[Y] = (differencial[Y] - frame_offset[Y]) * scal_z[Y];
		if (window[X] >= 0 && window[X] < mlx->frame->mm_widht
			&& window[Y] >= 0 && window[Y] < mlx->frame->mm_height)
		{
			buffering_pixel(window[X], window[Y], mlx, 0x00FF00);
		}
	}
}
