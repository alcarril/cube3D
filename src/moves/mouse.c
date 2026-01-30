/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 01:48:42 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:31:44 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	get_mouse_pos_and_move(t_mlx *mlx)
{
	t_mouse	*m;
	int		pix_dif[2];
	bool	is_move[2];

	m = &(mlx->player->mouse);
	mlx_mouse_get_pos(mlx->mlx_var, mlx->mlx_window, &(m->pos_x), &(m->pos_y));
	if (is_mouse_in_window(mlx, m->pos_x, m->pos_y) == OUT)
	{
		if (m->out_and_on == true)
			return ;
		mlx_mouse_move(mlx->mlx_var, mlx->mlx_window, m->axis_x, m->axis_y);
	}
	else
		m->out_and_on = false;
	ft_bzero((void *)is_move, sizeof(is_move));
	move_player_with_mouse(mlx, pix_dif, is_move);
	reset_mouse_position(mlx, is_move);
}

void	move_player_with_mouse(t_mlx *mlx, int *pix_dif, bool *is_move)
{
	t_mouse	*m;

	m = &(mlx->player->mouse);
	pix_dif[X] = m->pos_x - m->axis_x;
	if (clamp_mouse_deltax(&pix_dif[X]) == true)
	{
		is_move[X] = 1;
		mlx->player->angle -= pix_dif[X] * m->sens_x;
		mlx->player->rad_angle = mlx->player->angle * (PI / 180.0f);
	}
	pix_dif[Y] = m->pos_y - m->axis_y;
	if (clamp_mouse_deltay(&pix_dif[Y]) == true)
	{
		is_move[Y] = 1;
		mlx->player->pitch_pix -= pix_dif[Y]
			* (m->pitch_factor * mlx->player->max_pitch_pix);
	}
}

bool	is_mouse_in_window(t_mlx *mlx, int mouse_x, int mouse_y)
{
	if (mouse_x >= 0 && mouse_x < mlx->win_width
		&& mouse_y >= 0 && mouse_y < mlx->win_height)
	{
		return (IN);
	}
	return (OUT);
}

bool	clamp_mouse_deltax(int *pix_dif)
{
	if (*pix_dif > -MOUSE_DEADZONEX && *pix_dif < MOUSE_DEADZONEX)
		return (false);
	if (*pix_dif > MOUSE_MAX_MOV)
		*pix_dif = MOUSE_MAX_MOV;
	if (*pix_dif < -MOUSE_MAX_MOV)
		*pix_dif = -MOUSE_MAX_MOV;
	return (true);
}

bool	clamp_mouse_deltay(int *pix_dif)
{
	if (*pix_dif > -MOUSE_DEADZONEY && *pix_dif < MOUSE_DEADZONEY)
		return (false);
	if (*pix_dif > MOUSE_MAX_MOV)
		*pix_dif = MOUSE_MAX_MOV;
	if (*pix_dif < -MOUSE_MAX_MOV)
		*pix_dif = -MOUSE_MAX_MOV;
	return (true);
}
