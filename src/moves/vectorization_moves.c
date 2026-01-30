/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorization_moves.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:25:18 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:33:42 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	vectorization(t_player *pl, long long dt, float speed, float angle)
{
	ft_bzero(pl->diff, sizeof(pl->diff));
	ft_bzero(pl->v_move, sizeof(pl->v_move));
	if (pl->keys.move_up)
	{
		pl->v_move[X] += cos(angle);
		pl->v_move[Y] -= sin(angle);
	}
	if (pl->keys.move_down)
	{
		pl->v_move[X] -= cos(angle);
		pl->v_move[Y] += sin(angle);
	}
	if (pl->keys.move_left)
	{
		pl->v_move[X] += cos(angle + (PI * 0.5f));
		pl->v_move[Y] += sin(angle - (PI * 0.5f));
	}
	if (pl->keys.move_right)
	{
		pl->v_move[X] += cos(angle - (PI * 0.5f));
		pl->v_move[Y] += sin(angle + (PI * 0.5f));
	}
	pl->diff[X] = pl->v_move[X] * speed * dt;
	pl->diff[Y] = pl->v_move[Y] * speed * dt;
}

void	vectorization_dukedoom(t_player *pl, long long dt, float angle)
{
	ft_bzero(pl->diff, sizeof(pl->diff));
	ft_bzero(pl->v_move, sizeof(pl->v_move));
	if (pl->keys.move_up)
	{
		pl->v_move[X] += cos(angle);
		pl->v_move[Y] -= sin(angle);
	}
	if (pl->keys.move_down)
	{
		pl->v_move[X] -= cos(angle);
		pl->v_move[Y] += sin(angle);
	}
	if (pl->keys.move_left)
	{
		pl->v_move[X] += cos(angle + (PI * 0.5f));
		pl->v_move[Y] += sin(angle - (PI * 0.5f));
	}
	if (pl->keys.move_right)
	{
		pl->v_move[X] += cos(angle - (PI * 0.5f));
		pl->v_move[Y] += sin(angle + (PI * 0.5f));
	}
	pl->diff[X] = pl->v_move[X] * pl->speed_a[X] * dt;
	pl->diff[Y] = pl->v_move[Y] * pl->speed_a[Y] * dt;
}

void	airborne_vectorization(t_player *pl, long long dt, bool is_dukedoom)
{
	if (is_dukedoom == false)
	{
		pl->diff[X] = pl->v_move[X] * pl->speed_dt * dt;
		pl->diff[Y] = pl->v_move[Y] * pl->speed_dt * dt;
	}
	else
	{
		pl->diff[X] = pl->v_move[X] * pl->speed_a[X] * dt;
		pl->diff[Y] = pl->v_move[Y] * pl->speed_a[Y] * dt;
	}
}
