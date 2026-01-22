/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiance_configs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:14:29 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/15 22:08:18 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cube3D.h"

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

//hecho yes
float	dist_factor_floor(int win_height, int win_y, int horizon, int ambient)
{
	float	dist_factor;

	if (ambient == CEMENTERY)
		dist_factor = 1.0f - (float)(horizon - win_y) / (win_height - horizon);
	else if (ambient == ASTURIAS)
		dist_factor = (float)( win_y - horizon) / (win_height - horizon);
	else if (ambient == OPEN)
		dist_factor = 1.0f - (float)( win_y - horizon) / (win_height - horizon);
	if (dist_factor < 0.0f)
		dist_factor = 0.0f;	
	if (dist_factor > 1.0f)
		dist_factor = 1.0f;
	return (dist_factor);
}

float	dist_factor_ceiling(int win_y, int horizon, int ambient)
{
	float	dist_factor;

	if (ambient == CEMENTERY)
		dist_factor = 1.0f - (float)(win_y - horizon) / horizon;
	else if (ambient == ASTURIAS)
		dist_factor = 1.0f - (float)(horizon - win_y) / horizon;
	else if (ambient == OPEN)
		dist_factor = (float)(horizon - win_y) / horizon;
	if (dist_factor < 0.0f)
		dist_factor = 0.0f;	
	if (dist_factor > 1.0f)
		dist_factor = 1.0f;
	return (dist_factor);
}