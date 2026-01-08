/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:26:17 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/08 14:37:14 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

/*
	Comprueba si un punto (x, y) toca una pared en el mapa.
	Devuelve true si toca una pared o está fuera de los límites del mapa, false en caso contrario.
*/
bool	touch_wall(t_mlx *mlx, float x, float y)
{
	if (x < 0 || y < 0 || x >= mlx->map->max_columns || y >= mlx->map->max_rows)
		return (1);
	if (mlx->map->map_grids[(unsigned int)y][(unsigned int)x] == WALL)
		return (1);
	return (0);
}

/*
	- Dibuja el haz de rayos en 2D desde la posición del jugador en el minimapa.
	- Los rayos se dibujan dentro del campo de visión (FOV) del jugador.
	- Sobreescribimos la memeria de la imagen para dibujar los rayos. en vez de triangular
	  para saber si en el recorrido del minimpa un estamos en un pixel de la matriz de pixeles
	  que representa el minimapa
*/
void draw_rays2D(t_mlx *mlx)
{
	float	diferencial[2];
	float	fov_half;
	float	rad_pos;
	float	rad_dif;
	float	rad_end;

	fov_half = mlx->player->rad_fov / 2;
	rad_pos = (mlx->player->rad_angle - fov_half);
	rad_end = (mlx->player->rad_angle + fov_half);
	rad_dif = (mlx->player->rad_fov / (mlx->frame->mm_widht));
	while (rad_pos <= rad_end)
	{
		diferencial[X] = mlx->player->pos_x;
		diferencial[Y] = mlx->player->pos_y;
		draw_ray2D(mlx, diferencial, rad_pos);
		rad_pos += rad_dif;
	}
}

/*
	Funcion para pintar un rayo en 2D desde la posicion del jugador hasta que toque una pared.
	- En el calculo del diferencial del eje y se usa el ajuste norte sur (inverso del seno).
*/
void	draw_ray2D(t_mlx *mlx, float diferencial[2], float rad)
{
	int	window[2];
	float step;
	
	step = 0.1f;
	while (!touch_wall(mlx, diferencial[X], diferencial[Y]))
	{
		diferencial[X] += step * cos(rad);
		diferencial[Y] += step * -sin(rad);
		window[X] = diferencial[X] * mlx->frame->mm_scale[X];
		window[Y] = diferencial[Y] * mlx->frame->mm_scale[Y];
		if (window[X] >= 0 && window[X] < mlx->win_width &&
				window[Y] >= 0 && window[Y] < mlx->win_height)
		{
			buffering_pixel(window[X], window[Y], mlx, 0x000000FF);
		}
	}
}
