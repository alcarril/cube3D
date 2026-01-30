/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 21:01:39 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:24:44 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

unsigned int	apply_shade(unsigned int color, float shade)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 255) * shade);
	g = (int)(((color >> 8) & 255) * shade);
	b = (int)((color & 255) * shade);
	if (r > 255)
		r = 255;
	if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

unsigned int	shade_linear(unsigned int color, float dist, float max_dist)
{
	float	shade;

	shade = 1.0f - (dist / max_dist);
	if (shade < 0.0f)
		shade = 0.0f;
	if (shade > 1.0f)
		shade = 1.0f;
	return (apply_shade(color, shade));
}

unsigned int	shade_inverse(unsigned int color, float k, float prop_dist)
{
	float	shade;

	shade = 1.0f / (1.0f + prop_dist * k);
	return (apply_shade(color, shade));
}

unsigned int	shade_exponential(unsigned int color, float dens, float prop)
{
	float	shade;

	shade = expf(-prop * dens);
	return (apply_shade(color, shade));
}
