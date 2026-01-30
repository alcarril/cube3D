/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_keys_buttons.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:59:20 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:26:29 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

int	mouse_init_manager(t_mlx *mlx)
{
	if (mlx->has_been_mouse_in_window == true)
		return (0);
	if (mlx->has_been_mouse_in_window == false)
		mlx->has_been_mouse_in_window = true;
	printf("Now you can use boost mode without crash kernell pixmap, ;)\n");
	mlx_mouse_hide(mlx->mlx_var, mlx->mlx_window);
	mlx->player->mouse.onoff = ON;
	return (0);
}

void	toogle_mouse(t_mlx *ml)
{
	t_mouse	*m;

	m = &(ml->player->mouse);
	if (m->onoff == ON)
	{
		m->onoff = OFF;
		mlx_mouse_show(ml->mlx_var, ml->mlx_window);
		printf("MOUSE OFF\n");
	}
	else
	{
		m->onoff = ON;
		mlx_mouse_get_pos(ml->mlx_var, ml->mlx_window, &(m->pos_x),
			&(m->pos_y));
		if (is_mouse_in_window(ml, m->pos_x, m->pos_y) == IN)
		{
			mlx_mouse_move(ml->mlx_var, ml->mlx_window, m->axis_x, m->axis_y);
			m->out_and_on = false;
		}
		else
			m->out_and_on = true;
		m->out_and_on = true;
		mlx_mouse_hide(ml->mlx_var, ml->mlx_window);
		printf("MOUSE ON\n");
	}
}

int	mouse_button_manager(int mouse_button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (mouse_button == 4)
	{
		mlx->player->mouse.sens_x += 0.02f;
		mlx->player->mouse.pitch_factor += 0.002f;
		printf("MOUSE: Sensibility increasing\n");
	}
	if (mouse_button == 5)
	{
		mlx->player->mouse.sens_x -= 0.02f;
		mlx->player->mouse.pitch_factor -= 0.002f;
		printf("MOUSE: Sensibility decreasing\n");
	}
	if (mlx->player->mouse.sens_x > MOUSE_MAX_SENSX)
		mlx->player->mouse.sens_x = MOUSE_MAX_SENSX;
	if (mlx->player->mouse.pitch_factor > MAX_MOUSE_PITCH_FACTOR)
		mlx->player->mouse.pitch_factor = MAX_MOUSE_PITCH_FACTOR;
	if (mlx->player->mouse.sens_x < MOUSE_MIN_SENSX)
		mlx->player->mouse.sens_x = MOUSE_MIN_SENSX;
	if (mlx->player->mouse.pitch_factor < MIN_MOUSE_PITCH_FACTOR)
		mlx->player->mouse.pitch_factor = MIN_MOUSE_PITCH_FACTOR;
	return (0);
}
