/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:06:24 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/09 22:46:50 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

/*
	Funcion que maneja la presion de teclas para el movimiento del jugador
*/
void	player_keypress(t_mlx *mlx, int keysym)
{
	if (keysym == XK_w)
		mlx->player->move_up = true;
	if (keysym == XK_s)
		mlx->player->move_down = true;
	if (keysym == XK_a)
		mlx->player->move_left = true;
	if (keysym == XK_d)
		mlx->player->move_right = true;
	if (keysym == XK_Left)
		mlx->player->r_counterclockwise = true;
	if (keysym == XK_Right)
		mlx->player->r_clockwise = true;
	if (keysym == XK_Shift_L)
	{
		if (mlx->player->sprint == false)
		{
			mlx->player->speed += 0.05;
			mlx->player->sprint = true;
		}
	}
	if (keysym == XK_v)
		change_fov(mlx);
}
/*
	Funcion para cambiar el fov del jugador
*/
void	change_fov(t_mlx *mlx)
{
	if (mlx->player->fov == 60.0f)
	{
		mlx->player->fov = 90.0f;
		mlx->player->rad_fov = 90.0f * (PI / 180.0f);
	}
	else
	{
		mlx->player->fov = 60.0f;
		mlx->player->rad_fov = 60.0f * (PI / 180.0f);
	}
}

/*
	Funcion para togglear minimapa
*/
void	toggle_minimap(t_mlx *mlx)
{
	if (mlx == NULL || mlx->frame == NULL)
		return ;
	if (mlx->frame->minimap_onoff == true)
		mlx->frame->minimap_onoff = false;
	else
		mlx->frame->minimap_onoff = true;
}

/*
	Funcion para togglear rayos en minimapa
*/
void	toggle_rays(t_mlx *mlx)
{
	if (mlx->frame->minimap_showrays == true)
		mlx->frame->minimap_showrays = false;
	else
		mlx->frame->minimap_showrays = true;
}

/*
	Funcion para togglear correccion de fish eye
*/
void	toggle_fish_eye(t_mlx *mlx)
{
	if (mlx->frame->draw_walls == draw_wall_column)
	{
		if (mlx->frame->fish_eye == true)
			mlx->frame->fish_eye = false;
		else
			mlx->frame->fish_eye = true;
	}
	else
		perror("Textures must be off to toggle fish eye effect\n");
}

