/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:54:24 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:30:48 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	setup_default_ambiance(t_map *map, t_ambiance *amb)
{
	amb->fog_color_walls = FOG_MEDIO_OSCURO;
	amb->fog_color_fc = FOG_MEDIO_CLARO;
	amb->v_max_distance_map = map->max_distance * 0.9f;
	amb->vinv_max_diatance = 1.0f / amb->v_max_distance_map;
	amb->mult_fog_walls = 0.2f;
	amb->mult_fog_floor = 0.3f;
	amb->mult_fog_ceiling = 0.2f;
	amb->k_factor_walls = 8.0f;
	amb->k_factor_floor = 1.0f;
	amb->k_factor_ceiling = 4.0f;
	amb->mult_shader_walls = 1.0f;
	amb->mult_shader_floor = 0.7f;
	amb->mult_shader_ceiling = 0.5f;
	amb->ambiance = OPEN;
}

void	setup_default_phisics(t_phisics *phisics)
{
	phisics->gravity = GRAVITY_EARTH;
	phisics->air_friction = AIR_FRICTION_MS;
	phisics->floor_friction = FLOOR_FRICTION_MS;
}

void	init_player_phisics(t_player *pl, t_phisics *ph)
{
	pl->aceleration[FRONT] = ACCELERATION_FRONT_FACTOR * ph->floor_friction;
	pl->aceleration[BACK] = ACCELERATION_BACK_FACTOR * ph->floor_friction;
	pl->aceleration[SIDES] = ACCELERATION_SIDES_FACTOR * ph->floor_friction;
	pl->traccion_k = TRACCION_K;
	pl->speed_dt = 0.0f;
	pl->max_speed_dt = MAX_PLAYER_SPEED;
	pl->speed_a[X] = 0.0f;
	pl->speed_a[Y] = 0.0f;
	pl->max_speed_a[X] = MAX_PLAYER_SPEED;
	pl->max_speed_a[Y] = MAX_PLAYER_SPEED;
	pl->camz = MIDDLE_Z;
	pl->aceleration_z = 0.0f;
	pl->aceleration_zcp = ph->gravity * ACCELERATION_K_EARTH;
	pl->speed_z = 0.0f;
	pl->is_jumping = false;
	pl->is_onair = false;
	pl->is_flying = false;
	pl->is_hided = false;
	pl->is_dragging = false;
	pl->is_sprinting = false;
	pl->is_groundpound = false;
}

void	init_player_mouse(t_player *pl, t_mlx *mlx)
{
	pl->mouse.pos_x = mlx->win_width / 2;
	pl->mouse.pos_y = mlx->win_height / 2;
	pl->mouse.axis_x = mlx->win_width / 2;
	pl->mouse.axis_y = mlx->win_height / 2;
	pl->mouse.sens_x = MOUSE_INIT_SENSX;
	pl->mouse.pitch_factor = MOUSE_PITCH_FACTOR;
	pl->mouse.onoff = OFF;
	pl->mouse.out_and_on = true;
}
