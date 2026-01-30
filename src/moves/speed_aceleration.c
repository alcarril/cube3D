/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speed_aceleration.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:14:31 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:33:33 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	acelerate_player(t_mlx *mlx, unsigned int vi, long long dt, bool *mo)
{
	float	accel;
	float	speed;
	float	max_speed;
	float	traction;

	speed = mlx->player->speed_dt;
	max_speed = mlx->player->max_speed_dt;
	traction = mlx->phisics.floor_friction * mlx->player->traccion_k;
	accel = mlx->player->aceleration[vi] * traction;
	speed += accel * (float)dt;
	if (speed > max_speed)
		speed = max_speed;
	mlx->player->speed_dt = speed;
	*mo = true;
}

void	decelerate_player(t_mlx *mlx, long long dt, bool mo)
{
	float	speed;
	float	friction;

	speed = mlx->player->speed_dt;
	if (speed <= 0.0f)
		return ;
	friction = mlx->phisics.floor_friction;
	if (mo == false)
		friction *= 10;
	speed -= speed * friction * (float)dt;
	if (speed < SPEEDMIN_MS)
		speed = 0.0f;
	mlx->player->speed_dt = speed;
}

void	acelerate_dukedoom(t_mlx *mlx, unsigned int vi, long long dt, bool *mo)
{
	float	aceleration;
	float	speed[2];
	float	max_speed[2];
	float	traccion;

	speed[X] = mlx->player->speed_a[X];
	speed[Y] = mlx->player->speed_a[Y];
	max_speed[X] = mlx->player->max_speed_a[X];
	max_speed[Y] = mlx->player->max_speed_a[Y];
	traccion = mlx->phisics.floor_friction * mlx->player->traccion_k;
	aceleration = mlx->player->aceleration[vi] * traccion;
	if (speed[X] < max_speed[X])
		speed[X] += dt * aceleration;
	if (speed[Y] < max_speed[Y])
		speed[Y] += dt * aceleration;
	if (speed[X] >= max_speed[X])
		speed[X] = max_speed[X];
	if (speed[Y] >= max_speed[Y])
		speed[Y] = max_speed[Y];
	normalize_vector(speed, max_speed);
	mlx->player->speed_a[X] = speed[X];
	mlx->player->speed_a[Y] = speed[Y];
	*mo = true;
}

void	decelerate_dukedoom(t_mlx *mlx, long long dt, bool mo)
{
	float	speed[2];
	float	friction;

	speed[X] = mlx->player->speed_a[X];
	speed[Y] = mlx->player->speed_a[Y];
	friction = mlx->phisics.floor_friction;
	if (mo == false)
		friction *= 10;
	if (speed[X] > SPEEDMIN_MS)
		speed[X] -= speed[X] * friction * (float)dt;
	if (speed[X] <= SPEEDMIN_MS)
		speed[X] = 0.0f;
	if (speed[Y] > SPEEDMIN_MS)
		speed[Y] -= speed[Y] * friction * (float)dt;
	if (speed[Y] <= SPEEDMIN_MS)
		speed[Y] = 0.0f;
	mlx->player->speed_a[X] = speed[X];
	mlx->player->speed_a[Y] = speed[Y];
}
