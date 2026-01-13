/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_celling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:45:21 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/13 15:04:23 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

/*
	Función para renderizar el suelo y el techo píxel a píxel
	- Calcula la línea del horizonte (origen o centro) basada en la altura de la ventana
	  y el la desviación vertical del jugador (pitch_pix) -> trasñacion vertical de los
	  puntos del conjunto
	- Itera sobre cada píxel desde la parte superior hasta la línea del horizonte
	  y pinta el techo con el color definido en el mapa
	- Luego, itera desde la línea del horizonte hasta la parte inferior de la ventana
	  y pinta el suelo con el color definido en el mapa
	- En resumen sivide la ventana en dos partes: techo y suelo, y las pinta
	  con los colores especificados
	- Se usa en el renderizado, despues se sobreescrobe la imagen con las paredes y
	  otros elementos 3D y el minimapa 2D
	- Mas lento que render floor and ceiling speed
	- Mas modular que renderizar en el el pintado de del raycasting (aunque
	  menos eficiente)
*/
void	render_floor_and_ceiling(t_mlx *mlx)
{
	int	x;
	int	y;
	int horizon;

	horizon = mlx->win_height / 2 + mlx->player->pitch_pix;
	y = -1;
	while (++y < horizon)
	{
		x = -1;
		while (++x < mlx->win_width)
			buffering_pixel(x, y, mlx, mlx->map->ceiling_color_hex);
	}
	y = horizon;
	while (y < mlx->win_height)
	{
		x = -1;
		while (++x < mlx->win_width)
			buffering_pixel(x, y, mlx, mlx->map->floor_color_hex);
		y++;
	}
}

/*
	Hace lo mismo que render_floor_and_ceiling pero de forma más rápida
	- En lugar de pintar píxel a píxel, pinta línea por línea usando
	  la función buffering_line
	- Con esto se reduce la cantidad de llamadas a la función de biferiado
	  y se mejora el rendimiento.
	- Solo se puede usar cuando el renderizado del suelo y el techo no estan texturizados
*/
void render_floor_and_ceiling_speed(t_mlx *mlx)
{
	int y;
	int horizon;

	horizon = mlx->win_height / 2 + mlx->player->pitch_pix;
	y = 0;
	while (y < horizon)
	{
		buffering_line(y, mlx->map->ceiling_color_hex, mlx, mlx->win_width);
		y++;
	}
	while (y < mlx->win_height)
	{
		buffering_line(y, mlx->map->floor_color_hex, mlx, mlx->win_width);
		y++;
	}
}

