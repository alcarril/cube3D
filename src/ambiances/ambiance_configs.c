/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiance_configs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:14:29 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:24:12 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

void	config_ambiance_cementery(t_ambiance *amb)
{
	amb->fog_color_walls = FOG_MEDIO_OSCURO;
	amb->fog_color_fc = FOG_MEDIO_OSCURO;
	amb->v_max_distance_map = MEDIUM_DISTANCE;
	amb->vinv_max_diatance = 1.0f / amb->v_max_distance_map;
	amb->mult_fog_walls = 1.7f;
	amb->mult_fog_floor = 1.7f;
	amb->mult_fog_ceiling = 1.7f;
	amb->k_factor_floor = 1.0f;
	amb->k_factor_ceiling = 1.0f;
	amb->k_factor_walls = 8.0f;
	amb->mult_shader_walls = 1.0f;
	amb->mult_shader_floor = 1.0f;
	amb->mult_shader_ceiling = 1.0f;
	amb->ambiance = CEMENTERY;
}

void	config_ambiance_asturias(t_map *map, t_ambiance *amb)
{
	amb->fog_color_walls = FOG_MEDIO_CLARO;
	amb->fog_color_fc = FOG_MEDIO_CLARO;
	amb->v_max_distance_map = map->max_distance * 0.7f;
	amb->vinv_max_diatance = 1.0f / amb->v_max_distance_map;
	amb->mult_fog_walls = 1.7f;
	amb->mult_fog_floor = 1.7f;
	amb->mult_fog_ceiling = 1.0f;
	amb->k_factor_walls = 8.0f;
	amb->k_factor_floor = 3.0f;
	amb->k_factor_ceiling = 1.0f;
	amb->mult_shader_walls = 1.0f;
	amb->mult_shader_floor = 1.3f;
	amb->mult_shader_ceiling = 0.3f;
	amb->ambiance = ASTURIAS;
}

void	config_ambiance_open(t_map *map, t_ambiance *amb)
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

void	config_ambiance_matrix(t_map *map, t_ambiance *amb)
{
	amb->fog_color_walls = 0x71DB00;
	amb->fog_color_fc = 0x71DB00;
	amb->v_max_distance_map = map->max_distance * 0.7f;
	amb->vinv_max_diatance = 1.0f / amb->v_max_distance_map;
	amb->mult_fog_walls = 0.3f;
	amb->mult_fog_floor = 0.4f;
	amb->mult_fog_ceiling = 0.3f;
	amb->k_factor_walls = 8.0f;
	amb->k_factor_floor = 3.0f;
	amb->k_factor_ceiling = 1.0f;
	amb->mult_shader_walls = 1.0f;
	amb->mult_shader_floor = 1.3f;
	amb->mult_shader_ceiling = 0.3f;
	amb->ambiance = MATRIX;
}
