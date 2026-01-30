/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 21:34:21 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:36:42 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int	game_engine(t_mlx *mlx)
{
	if (mlx->player->mouse.onoff == ON)
		get_mouse_pos_and_move(mlx);
	move_player(mlx);
	if (mlx->frame->raycasting_onoff == ON)
		render_frame3d(mlx);
	if (mlx->frame->minimap_onoff == ON)
		render_frame2d(mlx);
	mlx_put_image_to_window(mlx->mlx_var, mlx->mlx_window, mlx->mlx_img, 0, 0);
	fps_counter_realtime(mlx);
	return (0);
}

void	render_frame3d(t_mlx *mlx)
{
	throw_rays(mlx);
	if (mlx->frame->textures_onoff && mlx->frame->ambiance_onoff)
		render_floor_and_ceiling_amb(mlx);
	else if (mlx->frame->boost && mlx->has_been_mouse_in_window)
		render_floor_and_ceiling_speed(mlx);
	else
		render_floor_and_ceiling(mlx);
	render_walls(mlx);
}

void	buffering_pixel(int x, int y, t_mlx *mlx, int color)
{
	unsigned int	offset;
	static char		*bitmap_address;
	static int		line_length;
	static int		bpp;

	if (bpp == 0)
	{
		bitmap_address = mlx->bit_map_address;
		line_length = mlx->line_length;
		bpp = mlx->bits_per_pixel >> 3;
	}
	offset = (y * line_length) + (x * bpp);
	*(unsigned int *)(bitmap_address + offset) = color;
}

void	buffering_line(int y, int color, t_mlx *mlx, int width)
{
	unsigned int	offset;
	static char		*bitmap_address;
	static int		line_length;
	static int		bpp;

	if (bpp == 0)
	{
		bitmap_address = mlx->bit_map_address;
		line_length = mlx->line_length;
		bpp = mlx->bits_per_pixel >> 3;
	}
	offset = y * line_length;
	ft_memfillboost(bitmap_address + offset, color, width * bpp);
}
