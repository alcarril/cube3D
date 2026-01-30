/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   difspeed_vecmove_phisics.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:03:22 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:31:13 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	difspeed_and_vecmove(t_mlx *mlx, long long delta_time)
{
	t_player	*pl;
	bool		is_moving;

	pl = mlx->player;
	is_moving = 0;
	if (mlx->player->is_onair == false)
	{
		if (pl->keys.move_up == true)
			acelerate_player(mlx, FRONT, delta_time, &is_moving);
		if (pl->keys.move_down == true)
			acelerate_player(mlx, BACK, delta_time, &is_moving);
		if (pl->keys.move_left == true || pl->keys.move_right == true)
			acelerate_player(mlx, SIDES, delta_time, &is_moving);
		decelerate_player(mlx, delta_time, is_moving);
		vectorization(mlx->player, delta_time, pl->speed_dt, pl->rad_angle);
	}
	else
	{
		decelerate_player_air(mlx, delta_time);
		airborne_vectorization(pl, delta_time, false);
	}
}

void	difvspeed_and_vecmove_nukedoom(t_mlx *mlx, long long delta_time)
{
	t_player	*pl;
	bool		is_moving;

	pl = mlx->player;
	is_moving = 0;
	if (mlx->player->is_onair == false)
	{
		if (pl->keys.move_up == true)
			acelerate_dukedoom(mlx, FRONT, delta_time, &is_moving);
		if (pl->keys.move_down == true)
			acelerate_dukedoom(mlx, BACK, delta_time, &is_moving);
		if (pl->keys.move_left == true || pl->keys.move_right == true)
			acelerate_dukedoom(mlx, SIDES, delta_time, &is_moving);
		decelerate_dukedoom(mlx, delta_time, is_moving);
		vectorization_dukedoom(mlx->player, delta_time, pl->rad_angle);
	}
	else
	{
		decelerate_dukedoom_air(mlx, delta_time);
		airborne_vectorization(pl, delta_time, true);
	}
}
