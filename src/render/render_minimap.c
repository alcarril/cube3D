/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:45:15 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:35:57 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int	render_frame2d(t_mlx *mlx)
{
	int		win[2];
	float	scaled_zoom[2];

	update_center_minimap_offset(mlx, scaled_zoom);
	win[Y] = 0;
	while (win[Y] <= mlx->frame->mm_height)
	{
		win[X] = 0;
		buffering_line(win[Y], 0xFFFFFFFF, mlx, mlx->frame->mm_widht);
		while (win[X] <= mlx->frame->mm_widht)
		{
			draw_mini_pixel_offset(mlx, win, scaled_zoom);
			win[X]++;
		}
		win[Y]++;
	}
	if (mlx->frame->minimap_showrays == true)
		draw_rays2d(mlx, scaled_zoom);
	return (1);
}

void	update_center_minimap_offset(t_mlx *mlx, float *escaled_zoom)
{
	t_frame		*f;
	float		pl_pos[2];
	float		zoom;

	f = mlx->frame;
	pl_pos[X] = mlx->player->pos_x;
	pl_pos[Y] = mlx->player->pos_y;
	zoom = mlx->frame->mm_zoom_factor;
	escaled_zoom[X] = f->mm_scale[X] * zoom;
	escaled_zoom[Y] = f->mm_scale[Y] * zoom;
	f->mm_offset[X] = pl_pos[X] - (f->mm_widht / 2) / (f->mm_scale[X] * zoom);
	f->mm_offset[Y] = pl_pos[Y] - (f->mm_height / 2) / (f->mm_scale[Y] * zoom);
}

void	draw_mini_pixel_offset(t_mlx *mlx, int *win, float *scaled_zoom)
{
	t_frame		*f;
	float		map[2];

	f = mlx->frame;
	map[X] = f->mm_offset[X] + (float)win[X] / (scaled_zoom[X]);
	map[Y] = f->mm_offset[Y] + (float)win[Y] / (scaled_zoom[Y]);
	if ((unsigned int)map[Y] < mlx->map->max_rows
		&& (unsigned int)map[X] < mlx->map->max_columns)
	{
		if (is_wall(mlx, map) == true)
			buffering_pixel(win[X], win[Y], mlx, 0xFF8C00);
		else
			buffering_pixel(win[X], win[Y], mlx, 0x969696);
		is_person2d(mlx, win, map);
	}
}

bool	is_wall(t_mlx *mlx, float *map)
{
	unsigned int	map_x;
	unsigned int	map_y;

	map_x = (unsigned int)map[X];
	map_y = (unsigned int)map[Y];
	if (mlx->map->map_grids[map_y][map_x] == WALL)
		return (true);
	return (false);
}

void	is_person2d(t_mlx *mlx, int *window, float *map)
{
	if (fabs(mlx->player->pos_x - map[X]) < mlx->player->volume
		&& fabs(mlx->player->pos_y - map[Y]) < mlx->player->volume)
	{
		buffering_pixel(window[X], window[Y], mlx, 0x000000);
	}
}
