/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decelerate_air.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:28:39 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:31:06 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	decelerate_player_air(t_mlx *mlx, long long dt)
{
	float	speed;
	float	friction;

	speed = mlx->player->speed_dt;
	if (speed <= 0.0f)
		return ;
	friction = mlx->phisics.air_friction;
	speed -= speed * friction * (float)dt;
	if (speed < SPEEDMIN_MS)
		speed = 0.0f;
	mlx->player->speed_dt = speed;
}

void	decelerate_dukedoom_air(t_mlx *mlx, long long dt)
{
	float	speed[2];
	float	friction;

	speed[X] = mlx->player->speed_a[X];
	speed[Y] = mlx->player->speed_a[Y];
	friction = mlx->phisics.air_friction;
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
