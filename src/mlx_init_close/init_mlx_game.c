/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:07:49 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:29:56 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

bool	init_mlx_components(t_mlx *mlx)
{
	if (mlx == NULL)
		return (false);
	mlx->mlx_var = mlx_init();
	if (mlx->mlx_var == NULL)
	{
		perror("X11 server disply conexion failed\n");
		return (false);
	}
	setup_window_wh(mlx);
	mlx->mlx_window = mlx_new_window(mlx->mlx_var, mlx->win_width,
			mlx->win_height, "cub3D");
	if (mlx->mlx_window == NULL)
	{
		perror("X Window creation failed\n");
		destroy_mlx_componets(0, mlx_destroy_window, mlx_destroy_display, mlx);
		return (false);
	}
	if (init_images_data(mlx) == false)
		return (false);
	mlx->has_been_mouse_in_window = false;
	return (true);
}

bool	init_images_data(t_mlx *mlx)
{
	mlx->mlx_img = mlx_new_image(mlx->mlx_var, mlx->win_width, mlx->win_height);
	if (mlx->mlx_img == NULL)
	{
		perror("X Window image buffer creation failed\n");
		destroy_mlx_componets(0, mlx_destroy_window, mlx_destroy_display, mlx);
		return (false);
	}
	mlx->bit_map_address = mlx_get_data_addr(mlx->mlx_img,
			&(mlx->bits_per_pixel), &(mlx->line_length), &(mlx->endian));
	if (mlx->bit_map_address == NULL)
	{
		perror("X Window image components creation failed");
		destroy_mlx_componets(mlx_destroy_image, mlx_destroy_window,
			mlx_destroy_display, mlx);
		return (false);
	}
	return (true);
}

bool	load_textures(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->map->n_textures)
	{
		if (load_single_texture(mlx, &mlx->map->textures[i],
				mlx->map->texture_paths[i]) == false)
		{
			free_loaded_textures(mlx, i + 1, mlx->map->n_textures, 1);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	load_single_texture(t_mlx *mlx, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(mlx->mlx_var, path,
			&texture->width, &texture->height);
	if (texture->img == NULL)
	{
		perror("Xpm file to image fail");
		return (false);
	}
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (texture->addr == NULL || texture->width <= 0 || texture->height <= 0)
	{
		perror("Texture fail while creating image buffer components");
		return (false);
	}
	return (true);
}

void	start_hooks_and_game(t_mlx *mlx)
{
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask,
		key_press, mlx);
	mlx_hook(mlx->mlx_window, KeyRelease, KeyReleaseMask,
		key_release, mlx);
	mlx_hook(mlx->mlx_window, DestroyNotify, StructureNotifyMask,
		close_game_manager, mlx);
	mlx_hook(mlx->mlx_window, ButtonPress, (1L << 2),
		mouse_button_manager, mlx);
	mlx_hook(mlx->mlx_window, EnterNotify, (1L << 4),
		mouse_init_manager, mlx);
	printf(CONTROLS_INFO);
	mlx_loop_hook(mlx->mlx_var, game_engine, mlx);
}
