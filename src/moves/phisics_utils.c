/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phisics_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:57:44 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:32:16 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	normalize_vector(float *v_speed, float *max_speed)
{
	float	total_speed;

	total_speed = sqrtf((v_speed[X] * v_speed[X]) + (v_speed[Y] * v_speed[Y]));
	if (total_speed > max_speed[X])
	{
		v_speed[X] *= max_speed[X] / total_speed;
		v_speed[Y] *= max_speed[X] / total_speed;
	}
}
