/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:04:35 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:35:17 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	throw_rays(t_mlx *mlx)
{
	float			ray_angle;
	float			rad_dif;
	float			fov_half;
	int				n_ray;
	int				win_width;

	mlx->frame->wall_start_min = mlx->win_height;
	mlx->frame->wall_end_max = 0;
	win_width = mlx->win_width;
	fov_half = mlx->player->fov_half;
	rad_dif = mlx->frame->delta_rays;
	ray_angle = (mlx->player->rad_angle) + fov_half;
	n_ray = 0;
	while (n_ray < win_width)
	{
		cast_ray(mlx, n_ray, ray_angle);
		ray_angle -= rad_dif;
		n_ray++;
	}
}

void	cast_ray(t_mlx *mlx, unsigned int n_ray, float ray_angle)
{
	t_ray	*ray;
	t_wall	*wall;

	ray = &mlx->frame->rays[n_ray];
	wall = &mlx->frame->walls[n_ray];
	set_ray(mlx, ray, ray_angle);
	ray->proyected_wall_dist = get_distance_to_wall(mlx, ray, ray_angle);
	mlx->frame->fov_distances[mlx->win_width - n_ray - 1] = ray->wall_dist;
	scale_wall_phisics(wall, ray->proyected_wall_dist, mlx);
	if (n_ray == 0)
	{
		mlx->frame->wall_start_min = wall->wall_start;
		mlx->frame->wall_end_max = wall->wall_end;
	}
	else
	{
		if (wall->wall_start > mlx->frame->wall_start_min)
			mlx->frame->wall_start_min = wall->wall_start;
		if (wall->wall_end < mlx->frame->wall_end_max)
			mlx->frame->wall_end_max = wall->wall_end;
	}
}

void	set_ray(t_mlx *mlx, t_ray *ray, float ray_angle)
{
	ray->raydir[X] = cos(ray_angle);
	ray->raydir[Y] = -sin(ray_angle);
	ray->map[X] = (int)(mlx->player->pos_x);
	ray->map[Y] = (int)(mlx->player->pos_y);
	if (ray->raydir[X] == 0)
		ray->delta[X] = 1e30;
	else
		ray->delta[X] = fabs(1 / ray->raydir[X]);
	if (ray->raydir[Y] == 0)
		ray->delta[Y] = 1e30;
	else
		ray->delta[Y] = fabs(1 / ray->raydir[Y]);
}

void	scale_wall_phisics(t_wall *wall, float perp_dist, t_mlx *mlx)
{
	static int	win_height;
	int			wallh_half;
	int			pitch;
	float		vo;
	float		camz;

	if (win_height == 0)
		win_height = mlx->win_height;
	pitch = mlx->player->pitch_pix;
	camz = mlx->player->camz;
	wall->vertical_offset = (camz * (win_height >> 1) / perp_dist);
	vo = wall->vertical_offset;
	if (perp_dist <= 0)
		wall->wall_height = win_height;
	else
		wall->wall_height = (int)(win_height / perp_dist);
	wallh_half = wall->wall_height >> 1;
	wall->wall_start = (win_height >> 1) - (wallh_half) + pitch + (int)vo;
	wall->wall_end = (win_height >> 1) + (wallh_half) + pitch + (int)vo;
	if (wall->wall_start < 0)
		wall->wall_start = 0;
	if (wall->wall_end >= win_height)
		wall->wall_end = win_height - 1;
}

void	draw_wall_column(t_mlx *mlx, int column, t_wall *wall, t_ray *ray)
{
	int	i;
	int	wall_end;

	(void)ray;
	wall_end = wall->wall_end;
	i = wall->wall_start;
	while (i <= wall_end)
	{
		buffering_pixel(column, i, mlx, 0xFF8C00);
		i++;
	}
}
