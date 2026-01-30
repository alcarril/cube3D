/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:22:40 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:36:27 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	render_walls(t_mlx *mlx)
{
	if (mlx->frame->textures_onoff == ON)
	{
		if (mlx->frame->ambiance_onoff == OFF)
		{
			if (mlx->frame->boost == OFF)
				render_walls_tex(mlx);
			else
				render_walls_tex_speed(mlx);
		}
		else
			render_walls_ambiance(mlx);
	}
	else
		render_walls_no_textures(mlx);
}

void	render_walls_tex(t_mlx *mlx)
{
	int		n_ray;
	t_ray	*ray;
	t_wall	*wall;

	ray = mlx->frame->rays;
	wall = mlx->frame->walls;
	n_ray = 0;
	while (n_ray < mlx->win_width)
	{
		draw_wall_column_tex(mlx, n_ray, &wall[n_ray], &ray[n_ray]);
		n_ray++;
	}
}

void	render_walls_no_textures(t_mlx *mlx)
{
	int		n_ray;
	t_ray	*ray;
	t_wall	*wall;

	ray = mlx->frame->rays;
	wall = mlx->frame->walls;
	n_ray = 0;
	while (n_ray < mlx->win_width)
	{
		draw_wall_column(mlx, n_ray, &wall[n_ray], &ray[n_ray]);
		n_ray++;
	}
}

void	render_walls_tex_speed(t_mlx *mlx)
{
	int		n_ray;
	t_ray	*ray;
	t_wall	*wall;

	ray = mlx->frame->rays;
	wall = mlx->frame->walls;
	n_ray = 0;
	while (n_ray < mlx->win_width)
	{
		drawwallcoltexspeed(mlx, n_ray, &wall[n_ray], &ray[n_ray]);
		n_ray++;
	}
}

void	render_walls_ambiance(t_mlx *mlx)
{
	int		n_ray;
	t_ray	*ray;
	t_wall	*wall;

	ray = mlx->frame->rays;
	wall = mlx->frame->walls;
	n_ray = 0;
	while (n_ray < mlx->win_width)
	{
		drawinglopp_tex_amb(mlx, n_ray, &wall[n_ray], &ray[n_ray]);
		n_ray++;
	}
}
