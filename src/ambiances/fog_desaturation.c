/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog_desaturation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:40:14 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:24:37 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

unsigned int	apply_fog_pixel(unsigned int col, unsigned int fog_c, float p)
{
	unsigned char	rgb[3];
	unsigned char	fog[3];
	int				i;

	if (p > 1.0f)
		p = 1.0f;
	rgb[R] = (col >> 16) & 0xFF;
	rgb[G] = (col >> 8) & 0xFF;
	rgb[B] = col & 0xFF;
	fog[R] = (fog_c >> 16) & 0xFF;
	fog[G] = (fog_c >> 8) & 0xFF;
	fog[B] = fog_c & 0xFF;
	i = 0;
	while (i < 3)
	{
		rgb[i] = (unsigned char)((1.0f - p) * rgb[i] + p * fog[i]);
		i++;
	}
	return ((rgb[R] << 16) | (rgb[G] << 8) | rgb[B]);
}

unsigned int	apply_desaturation(unsigned int color, float factor)
{
	unsigned char	rgb[3];
	unsigned char	gray;
	int				i;

	if (factor < 0.0f)
		factor = 0.0f;
	if (factor > 1.0f)
		factor = 1.0f;
	rgb[R] = (color >> 16) & 0xFF;
	rgb[G] = (color >> 8) & 0xFF;
	rgb[B] = color & 0xFF;
	gray = (unsigned char)(0.299f * rgb[R] + 0.587f * rgb[G] + 0.114f * rgb[B]);
	i = 0;
	while (i < 3)
	{
		rgb[i] = (unsigned char)((1.0f - factor) * rgb[i] + factor * gray);
		i++;
	}
	return ((rgb[R] << 16) | (rgb[G] << 8) | rgb[B]);
}
