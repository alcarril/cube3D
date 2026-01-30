/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiance_configs1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:24:57 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:24:33 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

float	dist_factor_floor(int win_height, int win_y, int horizon, int ambient)
{
	float	dist_fac;

	dist_fac = 0;
	if (ambient == CEMENTERY)
		dist_fac = 1.0f - (float)(horizon - win_y) / (win_height - horizon);
	else if (ambient == ASTURIAS)
		dist_fac = (float)(win_y - horizon) / (win_height - horizon);
	else if (ambient == OPEN)
		dist_fac = 1.0f - (float)(win_y - horizon) / (win_height - horizon);
	if (dist_fac < 0.0f)
		dist_fac = 0.0f;
	if (dist_fac > 1.0f)
		dist_fac = 1.0f;
	return (dist_fac);
}

float	dist_factor_ceiling(int win_y, int horizon, int ambient)
{
	float	dist_factor;

	dist_factor = 0;
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

unsigned int	apllyamb_ceiling(t_ambiance *a, float df, unsigned int rcol)
{
	unsigned int	col;
	float			mult_shader;
	float			mult_fog;
	float			k_factor;
	int				fog_color;

	mult_shader = a->mult_shader_ceiling;
	mult_fog = a->mult_fog_ceiling;
	k_factor = a->k_factor_ceiling;
	fog_color = a->fog_color_fc;
	col = shade_inverse(rcol, k_factor, df * mult_shader);
	col = apply_desaturation(col, df * 0.6f);
	col = apply_fog_pixel(col, fog_color, df * mult_fog);
	return (col);
}

unsigned int	apllyamb_floor(t_ambiance *a, float df, unsigned int rcol)
{
	unsigned int	col;
	float			mult_shader;
	float			mult_fog;
	float			k_factor;
	int				fog_color;

	mult_shader = a->mult_shader_floor;
	mult_fog = a->mult_fog_floor;
	k_factor = a->k_factor_floor;
	fog_color = a->fog_color_fc;
	col = shade_inverse(rcol, k_factor, df * mult_shader);
	col = apply_desaturation(col, df * 0.6f);
	col = apply_fog_pixel(col, fog_color, df * mult_fog);
	return (col);
}
