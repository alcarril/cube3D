/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:31:15 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/09 23:17:15 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

/*
	Funcion que maneja la presion de teclas para el movimiento del jugador
	- Se podria optimizar con un jump table
*/
int	key_press(int keysym, t_mlx *mlx)
{
	if (mlx == NULL)
		return (0);
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
	if (keysym == XK_e)
		toogle_dist_calc(mlx);
	if (keysym == XK_t)
		toggle_textures(mlx);
	if (keysym == XK_c)
		toogle_floor_celling(mlx);
	if (keysym == XK_z)
		print_controls();
	return (0);
}

/*
	Funcion que maneja la liberacion de teclas para el movimiento del jugador
*/
int	key_release(int keysym, t_mlx *mlx)
{
	if (mlx == NULL)
		return (0);
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
	Funcion que activa o desactiva el raycasting
*/
void	toogle_raycasting(t_mlx *mlx)
{
	if (mlx->frame->raycasting_onoff == true)
		mlx->frame->raycasting_onoff = false;
	else
		mlx->frame->raycasting_onoff = true;
}

void	toggle_textures(t_mlx *mlx)
{
	if (mlx->frame->draw_walls == draw_wall_column)
	{
		mlx->frame->draw_walls = draw_wall_column_tex;
		mlx->frame->fish_eye = false;
		mlx->frame->euclidean = false;
		printf("Textures enabled\n");
	}
	else
	{
		mlx->frame->draw_walls = draw_wall_column;
		printf("Textures disabled\n");
	}
}

void	toogle_floor_celling(t_mlx *mlx)
{
	if (mlx->frame->floor_celling == render_floor_and_ceiling)
	{
		mlx->frame->floor_celling = render_floor_and_ceiling_speed;
		printf("Fast floor and ceiling rendering enabled\n");
	}
	else
	{
		mlx->frame->floor_celling = render_floor_and_ceiling;
		printf("Accurate floor and ceiling rendering enabled\n");
	}
}
