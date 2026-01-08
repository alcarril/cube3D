/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:31:15 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/08 14:08:33 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

/*
	Funcion que maneja la presion de teclas para el movimiento del jugador
	- Se podria optimizar con un jump table
*/
int	key_press(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
	{
		close_handler(mlx);
		return (0);
	}
	player_keypress(mlx, keysym);
	if (keysym == XK_o)
		toogle_raycasting(mlx);
	if (keysym == XK_m)
		toggle_minimap(mlx);
	if (keysym == XK_r)
		toggle_rays(mlx);
	if (keysym == XK_f)
		toggle_fish_eye(mlx);
	return (0);
}

/*
	Funcion que maneja la liberacion de teclas para el movimiento del jugador
*/
int	key_release(int keysym, t_mlx *mlx)
{
	if (keysym == XK_w)
		mlx->player->move_up = false;
	if (keysym == XK_s)
		mlx->player->move_down = false;
	if (keysym == XK_a)
		mlx->player->move_left = false;
	if (keysym == XK_d)
		mlx->player->move_right = false;
	if (keysym == XK_Left)
		mlx->player->r_counterclockwise = false;
	if (keysym == XK_Right)
		mlx->player->r_clockwise = false;
	if (keysym == XK_Shift_L)
	{
		if (mlx->player->sprint == true)
		{
			mlx->player->speed -= 0.05;
			mlx->player->sprint = false;
		}
	}
	return (0);
}

/*
	Funcion que maneja el cierre de la ventana
*/
int	close_handler(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_var,
		mlx->mlx_img);
	mlx_destroy_window(mlx->mlx_var,
		mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_var);
	free(mlx->mlx_var);
	exit(0);
}

/*
	Funcion que activa o desactiva el raycasting
*/
void	toogle_raycasting(t_mlx *mlx)
{
	if (mlx->frame->raycasting_onoff == true)
		mlx->frame->raycasting_onoff = false;
	else
		mlx->frame->raycasting_onoff = true;
}