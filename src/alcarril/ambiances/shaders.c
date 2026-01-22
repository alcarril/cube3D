/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 21:01:39 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/14 16:07:39 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

// Funcion base aplicasr shde a  un color
unsigned int apply_shade(unsigned int color, float shade)
{
	int r = (int)(((color >> 16) & 255) * shade);
	int g = (int)(((color >> 8) & 255) * shade);
	int b = (int)((color & 255) * shade);

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
	return (r << 16) | (g << 8) | b;
}

//Fucnion para plizar el shade lineal
unsigned int shade_linear(unsigned int color, float dist, float max_dist)
{
	float shade = 1.0f - (dist / max_dist);
	if (shade < 0.0f) 
		shade = 0.0f;
	if (shade > 1.0f) 
		shade = 1.0f;

	return apply_shade(color, shade);
}

//metodo inverso de shadin (recomendado) -> k >1 y proportion dis (0.1)
//optimizacion multiplicamos por porportion dist el k que alfinal es lo miso que 
//hacer el k proporciol y multiplicarlo por dis y ademas asi n o se hace la opracion en cadapixell
///de la pantalla menos ciclos de procesador
unsigned int shade_inverse(unsigned int color, float k, float proportion_dist)
{
	float	shade;
	
	shade  = 1.0f / (1.0f + proportion_dist * k);
	return apply_shade(color, shade);
}

//medodo exponencial niebla densa density > 1.0	proportion dist (0.1)
//meto optimizacion de proportion dist
unsigned int shade_exponential(unsigned int color, float density, float proportion_dist)
{	
	float shade;
	
	shade  = expf(-proportion_dist * density);
	return apply_shade(color, shade);
}

