/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:53:10 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/04 12:42:58 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

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
	// create_hooks(mlx);
	return (1);
}

void	create_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask,
		key_press, mlx);
	mlx_hook(mlx->mlx_window, KeyRelease, KeyReleaseMask,
		key_release, mlx);
	mlx_hook(mlx->mlx_window, DestroyNotify, StructureNotifyMask,
		close_handler, mlx);
	mlx_loop_hook(mlx->mlx_var, throw_rays, mlx);
}

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

//init player settings (ya no necesitamos cambiar posición porque viene del parsing)
void setup_player(t_mlx *mlx)
{
	mlx->player->speed = 0.033f;
	mlx->player->r_speed = 2.0f;
	mlx->player->fov = 60.0f;
	mlx->player->fish_eye = false;
	mlx->player->euclidean = false;
	mlx->player->move_down = false;
	mlx->player->move_up = false;
	mlx->player->move_right = false;
	mlx->player->move_left = false;
	mlx->player->r_clockwise = false;
	mlx->player->r_counterclockwise = false;
	
	// Inicializar array de distancias FOV si es necesario
	mlx->player->fov_distances = malloc(sizeof(double) * WIDTH);
	if (!mlx->player->fov_distances)
	{
		printf("Error: Failed to allocate memory for FOV distances\n");
		return;
	}
	
	printf("Player setup complete at (%.2f, %.2f) facing %.0f degrees\n", 
		   mlx->player->pos_x, mlx->player->pos_y, mlx->player->angle);
}
