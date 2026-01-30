/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorith.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:07:51 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:34:25 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

float	get_distance_to_wall(t_mlx *mlx, t_ray *ray, float ray_angle)
{
	float	walldist;

	calc_side_dist(mlx, ray);
	dda_loop(mlx, ray);
	if (mlx->frame->euclidean == false)
		ray->wall_dist = get_ray_distance(mlx, ray);
	else
		ray->wall_dist = get_ray_distance_euclidean(mlx, ray);
	if (mlx->frame->fish_eye == false)
		walldist = ray->wall_dist * cos(ray_angle - (mlx->player->rad_angle));
	else
		walldist = ray->wall_dist;
	return (walldist);
}

void	calc_side_dist(t_mlx *mlx, t_ray *ray)
{
	t_player	*pl;

	pl = mlx->player;
	if (ray->raydir[X] < 0)
	{
		ray->step[X] = -1;
		ray->sidedist[X] = (pl->pos_x - ray->map[X]) * ray->delta[X];
	}
	else
	{
		ray->step[X] = 1;
		ray->sidedist[X] = (ray->map[X] + 1.0 - pl->pos_x) * ray->delta[X];
	}
	if (ray->raydir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->sidedist[Y] = (pl->pos_y - ray->map[Y]) * ray->delta[Y];
	}
	else
	{
		ray->step[Y] = 1;
		ray->sidedist[Y] = (ray->map[Y] + 1.0 - pl->pos_y) * ray->delta[Y];
	}
}

void	dda_loop(t_mlx *mlx, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist[X] < ray->sidedist[Y])
		{
			ray->sidedist[X] += ray->delta[X];
			ray->map[X] += ray->step[X];
			ray->side_hit = VERTICAL;
		}
		else
		{
			ray->sidedist[Y] += ray->delta[Y];
			ray->map[Y] += ray->step[Y];
			ray->side_hit = HORIZONTAL;
		}
		if (is_wall_tile(mlx->map->map_grids[ray->map[Y]][ray->map[X]]))
		{
			hit = 1;
			ray->wall_value = mlx->map->map_grids[ray->map[Y]][ray->map[X]];
		}
	}
}

float	get_ray_distance(t_mlx *mlx, t_ray *ray)
{
	float	dist;
	float	wall_dist;
	int		face_compensation;

	if (ray->side_hit == VERTICAL)
	{
		wall_dist = ray->map[X] - mlx->player->pos_x;
		face_compensation = ((1 - ray->step[X]) >> 1);
		dist = (wall_dist + face_compensation) / ray->raydir[X];
	}
	else
	{
		wall_dist = ray->map[Y] - mlx->player->pos_y;
		face_compensation = ((1 - ray->step[Y]) >> 1);
		dist = (wall_dist + face_compensation) / ray->raydir[Y];
	}
	return (dist);
}

float	get_ray_distance_euclidean(t_mlx *mlx, t_ray *ray)
{
	float	fish_eye_dist;

	fish_eye_dist = sqrt(pow(ray->map[X] - mlx->player->pos_x, 2)
			+ pow(ray->map[Y] - mlx->player->pos_y, 2));
	return (fish_eye_dist);
}
