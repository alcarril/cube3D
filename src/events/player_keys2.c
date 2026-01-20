/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_keys2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:49:04 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/20 05:58:45 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

void	player_sprint_keypress(t_mlx *mlx)
{
	if (mlx->frame->phisics_onoff == OFF)
	{
		mlx->player->speed += 0.05;
		mlx->player->keys.sprint = true;
		printf("SPRINT ON\n");
	}
	else
	{
		mlx->player->aceleration[FRONT] += mlx->phisics.floor_friction * SPRINT_ACCELERATION_FRONT_FACTOR;
		mlx->player->max_speed_dt = MAX_PLAYER_SPEED_STRINT;
		mlx->player->keys.sprint = true;
		printf("SPRINT ON\n");
	}
}

void	player_sprint_keyrelease(t_mlx *mlx)
{
	if (mlx->frame->phisics_onoff == OFF)
	{
		mlx->player->speed -= 0.05;
		mlx->player->keys.sprint = false;
		printf("SPRINT OFF\n");
	}
	else
	{
		mlx->player->aceleration[FRONT] = mlx->phisics.floor_friction * ACCELERATION_FRONT_FACTOR;
		mlx->player->max_speed_dt = MAX_PLAYER_SPEED;
		mlx->player->keys.sprint = false;
		printf("SPRINT OFF\n");
	}
}




// Tabla de fricción, tracción y aceleración según la superficie:
// | Superficie   | Fricción | Tracción | Aceleración | Sensación                           |
// | ------------ | -------- | -------- | ----------- | ----------------------------------- |
// | Asfalto seco | 0.0020   | 1.0      | 0.020       | Arranque fuerte, frena rápido       |
// | Tierra       | 0.0012   | 0.8      | 0.012       | Algo de derrape                     |
// | Barro        | 0.0008   | 0.6      | 0.008       | Patina al acelerar                  |
// | Hielo        | 0.0002   | 0.2      | 0.002       | Apenas acelera, mucho deslizamiento |
