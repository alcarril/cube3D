/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axisz_phisics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 09:02:37 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:30:59 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	jump(t_mlx *mlx, long long dt_ms)
{
	t_player	*pl;
	t_phisics	*ph;
	float		dt;
	float		tm_aceleration;

	pl = mlx->player;
	if (pl->is_dragging || pl->is_hided || pl->is_flying || pl->is_groundpound)
		return ;
	dt = (float)dt_ms * 0.001f;
	ph = &mlx->phisics;
	if (pl->is_jumping)
		tm_aceleration = pl->aceleration_z - ph->gravity;
	else
		tm_aceleration = -ph->gravity;
	pl->speed_z += tm_aceleration * dt;
	pl->camz += pl->speed_z * dt;
	check_altitude(pl);
}

void	check_altitude(t_player	*pl)
{
	if (pl->camz > MAP_MAX_Z)
	{
		pl->camz = MAP_MAX_Z;
		pl->speed_z = 0.0f;
		pl->is_jumping = false;
	}
	if (pl->camz < MIDDLE_Z)
	{
		pl->camz = MIDDLE_Z;
		pl->speed_z = 0.0f;
		pl->is_jumping = false;
		pl->is_onair = false;
	}
}
