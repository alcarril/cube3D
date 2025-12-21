/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:53:10 by alejandro         #+#    #+#             */
/*   Updated: 2025/12/21 23:35:25 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

void	destroy_mlx_componets(int (*f)(), int (*g)(), int (*t)(),
	t_mlx *mlx)
{
	if (f != NULL)
		f(mlx->mlx_var, mlx->mlx_img);
	if (g != NULL)
		g(mlx->mlx_var, mlx->mlx_window);
	if (t != NULL)
		t(mlx->mlx_var);
	free(mlx->mlx_var);
}

int	close_handler(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_var,
		mlx->mlx_img);
	mlx_destroy_window(mlx->mlx_var,
		mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_var);
	free(mlx->mlx_var);
}

int	manage_key(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
		close_handler(mlx);
	return (0);
}

void	create_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask,
		manage_key, mlx);
	mlx_hook(mlx->mlx_window, DestroyNotify, StructureNotifyMask,
		close_handler, mlx);
}

char	init_mlx_components(t_mlx *mlx)
{
	if (!mlx)
		return (0);
	mlx->mlx_var = mlx_init();
	if (!mlx->mlx_var)
		return (0);
	mlx->mlx_window = mlx_new_window(mlx->mlx_var, WIDTH, HEIGHT, "cube3D");
	if (!mlx->mlx_window)
		return (destroy_mlx_componets(0, mlx_destroy_window, 0, mlx), 0);
	mlx->mlx_img = mlx_new_image(mlx->mlx_var, HEIGHT, WIDTH);
	if (!mlx->mlx_img)
		return (destroy_mlx_componets(0, mlx_destroy_window,
				mlx_destroy_display, mlx), 0);
	mlx->bit_map_address = mlx_get_data_addr(mlx->mlx_img,
			&(mlx->bits_per_pixel), &(mlx->line_length), &(mlx->endian));
	if (!mlx->bit_map_address)
		return (destroy_mlx_componets(mlx_destroy_image, mlx_destroy_window,
				mlx_destroy_display, mlx), 0);
	mlx->bit_map_address_copy = mlx->bit_map_address;//porque
	// set_default_values(img);//esta funcion puede ser util
	create_hooks(mlx);
	return (1);
}

void	buffering_pixel(int x, int y, t_mlx *mlx, int color)
{
	unsigned int	offset;

	offset = (y * mlx->line_length) + (x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)(mlx->bit_map_address + offset) = color;
}

int main (void)
{
	t_mlx	mlx;
	if (!init_mlx_components(&mlx))
		return (1);
	mlx_loop(mlx.mlx_var);
	return(0);
}
