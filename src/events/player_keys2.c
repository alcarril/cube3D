/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_keys2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:49:04 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:27:32 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

void	player_sprint_keypress(t_mlx *mlx)
{
	t_player	*pl;

	pl = mlx->player;
	if (pl->is_flying || pl->is_dragging || pl->is_hided || pl->is_groundpound)
		return ;
	if (mlx->frame->phisics_onoff == OFF)
	{
		mlx->player->speed += 0.05;
		mlx->player->keys.sprint = true;
		mlx->player->is_sprinting = true;
		printf("SPRINT ON\n");
	}
	else
	{
		mlx->player->aceleration[FRONT] += mlx->phisics.floor_friction
			* SPRINT_ACCELERATION_FRONT_FACTOR;
		mlx->player->max_speed_dt = MAX_PLAYER_SPEED_STRINT;
		mlx->player->max_speed_a[X] = MAX_PLAYER_SPEED_STRINT;
		mlx->player->max_speed_a[Y] = MAX_PLAYER_SPEED_STRINT;
		mlx->player->keys.sprint = true;
		mlx->player->is_sprinting = true;
		printf("SPRINT ON\n");
	}
}

void	player_sprint_keyrelease(t_mlx *mlx)
{
	t_player	*pl;

	pl = mlx->player;
	if (pl->is_flying || pl->is_dragging || pl->is_hided || pl->is_groundpound)
		return ;
	if (mlx->frame->phisics_onoff == OFF)
	{
		mlx->player->speed -= 0.05;
		mlx->player->keys.sprint = false;
		mlx->player->is_sprinting = false;
		printf("SPRINT OFF\n");
	}
	else
	{
		mlx->player->aceleration[FRONT] = mlx->phisics.floor_friction
			* ACCELERATION_FRONT_FACTOR;
		mlx->player->max_speed_dt = MAX_PLAYER_SPEED;
		mlx->player->max_speed_a[X] = MAX_PLAYER_SPEED;
		mlx->player->max_speed_a[Y] = MAX_PLAYER_SPEED;
		mlx->player->keys.sprint = false;
		mlx->player->is_sprinting = false;
		printf("SPRINT OFF\n");
	}
}

void	player_space_keypress(t_mlx *mlx)
{
	t_player	*pl;

	pl = mlx->player;
	if (pl->is_flying || pl->is_dragging || pl->is_hided || pl->is_groundpound)
		return ;
	if (mlx->frame->phisics_onoff == OFF)
		return ;
	if (mlx->player->is_jumping == false)
	{
		mlx->player->is_jumping = true;
		mlx->player->is_onair = true;
		mlx->player->aceleration_z = mlx->player->aceleration_zcp;
		mlx->player->speed_z = 0.0f;
		printf("JUMPING\n");
	}
}

void	player_space_keyrelease(t_mlx *mlx)
{
	t_player	*pl;

	pl = mlx->player;
	if (pl->is_flying || pl->is_dragging || pl->is_hided || pl->is_groundpound)
		return ;
	if (mlx->frame->phisics_onoff == OFF)
		return ;
	if (mlx->player->is_jumping == true)
	{
		mlx->player->aceleration_z = 0;
		mlx->player->is_jumping = false;
		printf("FALLING\n");
	}
}

void	player_control_keypress(t_mlx *mlx)
{
	t_player	*pl;

	pl = mlx->player;
	if (mlx->frame->phisics_onoff == OFF)
		return ;
	if (pl->is_onair || pl->is_flying || pl->is_dragging || pl->is_sprinting)
		return ;
	if (mlx->player->is_hided == false)
	{
		mlx->player->camz = FLOOR_Z * 0.5f;
		mlx->player->max_speed_dt = MAX_PLAYER_SPEED * 0.5f;
		mlx->player->max_speed_a[X] = MAX_PLAYER_SPEED * 0.5f;
		mlx->player->max_speed_a[Y] = MAX_PLAYER_SPEED * 0.5f;
		mlx->player->is_hided = true;
		printf("CROUCH\n");
	}
	else
	{
		mlx->player->camz = MIDDLE_Z;
		mlx->player->max_speed_dt = MAX_PLAYER_SPEED;
		mlx->player->max_speed_a[X] = MAX_PLAYER_SPEED;
		mlx->player->max_speed_a[Y] = MAX_PLAYER_SPEED;
		mlx->player->is_hided = false;
		printf("STAND UP\n");
	}
}
