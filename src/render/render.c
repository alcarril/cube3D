/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 21:34:21 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/08 19:19:26 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

/*
	Función principal para manejar el ciclo de renderizado del motor del juego:
	- Se activa gracias al hook de mlx_loop_hook
	- Maneja el movimiento del jugador
	- Limpia el buffer de la imagen (si no se limpia no funciona bien el render)
	- Llama a la función de raycasting para renderizar la escena 3D
	- Llama a la función para renderizar el minimapa 2D si está activado
	- Finalmente, actualiza la ventana con la nueva imagen renderizada	
*/
int	game_engine(t_mlx *mlx)
{
	move_player(mlx);
	ft_bzero(mlx->bit_map_address, mlx->win_height * mlx->line_length);
	if (mlx->frame->raycasting_onoff == true)
		throw_rays(mlx);
	if (mlx->frame->minimap_onoff == true)
		render_frame2D(mlx);
	mlx_put_image_to_window(mlx->mlx_var, mlx->mlx_window, mlx->mlx_img, 0, 0);
	return (0);
}

//se puede optimizar pasando por refencia las variables
void	buffering_pixel(int x, int y, t_mlx *mlx, int color)
{
	unsigned int	offset;

	if (x < 0 || x > mlx->win_width || y < 0 || y > mlx->win_height)
		return ;
	offset = (y * mlx->line_length) + (x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)(mlx->bit_map_address + offset) = color;
}

