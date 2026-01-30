/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:06:24 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:26:54 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

bool	player_keypress(t_mlx *mlx, int keysym)
{
	if (keysym == XK_w)
		mlx->player->keys.move_up = true;
	else if (keysym == XK_s)
		mlx->player->keys.move_down = true;
	else if (keysym == XK_a)
		mlx->player->keys.move_left = true;
	else if (keysym == XK_d)
		mlx->player->keys.move_right = true;
	else if (keysym == XK_Left)
		mlx->player->keys.r_counterclockwise = true;
	else if (keysym == XK_Right)
		mlx->player->keys.r_clockwise = true;
	else if (keysym == XK_Up)
		mlx->player->keys.look_up = true;
	else if (keysym == XK_Down)
		mlx->player->keys.look_down = true;
	else if (player_keypres2(mlx, keysym) == true)
		return (true);
	else
		return (false);
	return (true);
}

bool	player_keypres2(t_mlx *mlx, int keysym)
{
	if (keysym == XK_Shift_L)
		return (player_sprint_keypress(mlx), true);
	if (keysym == XK_Control_L)
		return (player_control_keypress(mlx), true);
	if (keysym == XK_Caps_Lock)
		return (player_blockmayus_keypress(mlx), true);
	if (keysym == XK_q)
		return (player_q_keypress(mlx), true);
	if (keysym == XK_space)
		player_space_keypress(mlx);
	else if (keysym == XK_comma)
		change_player_volume(mlx, true);
	else if (keysym == XK_period)
		change_player_volume(mlx, false);
	else if (keysym == XK_v)
		change_fov(mlx);
	else if (keysym == XK_j)
		toogle_mouse(mlx);
	else
		return (false);
	return (true);
}

void	change_fov(t_mlx *mlx)
{
	if (mlx->player->fov == 60.0f)
	{
		mlx->player->fov = 90.0f;
		mlx->player->rad_fov = 90.0f * (PI / 180.0f);
		mlx->player->fov_half = mlx->player->rad_fov / 2.0f;
		mlx->frame->delta_rays = (mlx->player->rad_fov) / mlx->win_width;
		printf("FOV 90\n");
	}
	else
	{
		mlx->player->fov = 60.0f;
		mlx->player->rad_fov = 60.0f * (PI / 180.0f);
		mlx->player->fov_half = mlx->player->rad_fov / 2.0f;
		mlx->frame->delta_rays = (mlx->player->rad_fov) / mlx->win_width;
		printf("FOV 60\n");
	}
}

void	change_player_volume(t_mlx *mlx, bool flag)
{
	if (flag == true && mlx->player->volume < 1.0f)
	{
		mlx->player->volume += 0.1f;
		if (mlx->player->volume > 1.1f)
			mlx->player->volume = 1.0f;
		printf("Volume: %.1f\n", mlx->player->volume);
	}
	else if (flag == false && mlx->player->volume > 0.0f)
	{
		mlx->player->volume -= 0.1f;
		if (mlx->player->volume < 0.2f)
			mlx->player->volume = 0.2f;
		printf("Volume: %.1f\n", mlx->player->volume);
	}
}
