/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:28:56 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:31:55 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	reset_mouse_position(t_mlx *mlx, bool *is_move)
{
	t_mouse	*m;

	m = &(mlx->player->mouse);
	if (is_move[X] == 0 && is_move[Y] == 0)
		return ;
	else if (is_move[X] == 1 && is_move[Y] == 1)
		mlx_mouse_move(mlx->mlx_var, mlx->mlx_window, m->axis_x, m->axis_y);
	else if (is_move[X] == 1 && is_move[Y] == 0)
		mlx_mouse_move(mlx->mlx_var, mlx->mlx_window, m->axis_x, m->pos_y);
	else if (is_move[X] == 0 && is_move[Y] == 1)
		mlx_mouse_move(mlx->mlx_var, mlx->mlx_window, m->pos_x, m->axis_y);
}
