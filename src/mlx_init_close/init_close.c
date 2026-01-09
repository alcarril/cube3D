/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:53:10 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/09 14:18:14 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

void	print_texture_values(t_mlx *mlx);

//aqui tendriamos que refactorizar
char	init_mlx_components(t_mlx *mlx)
{
	if (!mlx)
		return (0);
	mlx->mlx_var = mlx_init();
	if (!mlx->mlx_var)
		return (0);
	setup_window_wh(mlx);
	mlx->mlx_window = mlx_new_window(mlx->mlx_var, mlx->win_width, mlx->win_height, "cub3D");
	if (!mlx->mlx_window)
		return (destroy_mlx_componets(0, mlx_destroy_window, 0, mlx), 0);
	mlx->mlx_img = mlx_new_image(mlx->mlx_var, mlx->win_width, mlx->win_height);
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
	// print_texture_values(mlx);
	printf("MLX components initialized successfully.\n");
	return (1);
}

/*
	Obtener la escala del mapa a la pantalla. IGual no esra necesario
*/
void	setup_window_wh(t_mlx *mlx)
{
	mlx->win_height = mlx->map->max_rows * WIN_SCALE * 4;
	mlx->win_width = mlx->map->max_columns * WIN_SCALE * 3;
}

void	create_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask,
		key_press, mlx);
	mlx_hook(mlx->mlx_window, KeyRelease, KeyReleaseMask,
		key_release, mlx);
	mlx_hook(mlx->mlx_window, DestroyNotify, StructureNotifyMask,
		close_handler, mlx);
	// mlx_hook(mlx->mlx_window, MotionNotify, PointerMotionMask, mouse_move, mlx);
	mlx_loop_hook(mlx->mlx_var, game_engine, mlx);
}

void	load_textures(t_mlx *mlx)
{
	char *texture_paths[4] = {
		"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/test/south.xpm", // NORTE -> SUR
		"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/test/north.xpm", // SUR -> NORTE
		"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/test/east.xpm",  // OESTE -> ESTE
		"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/test/west.xpm"  // ESTE -> OESTE
	};
	int	i;
	printf("Texture.\n");
	i = 0;
	while (i < 4)
	{
		mlx->map->textures[i].img = mlx_xpm_file_to_image(mlx->mlx_var,
			texture_paths[i], &mlx->map->textures[i].width, &mlx->map->textures[i].height);
		if (!mlx->map->textures[i].img)
		{
			printf("Error loading texture: %s\n", texture_paths[i]);
			return ;//
		}
		mlx->map->textures[i].addr = mlx_get_data_addr(mlx->map->textures[i].img,
			&mlx->map->textures[i].bits_per_pixel, &mlx->map->textures[i].line_length,
			&mlx->map->textures[i].endian);
		i++;
	}
	printf("Textures loaded successfully.\n");
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


void	free_loaded_textures(t_mlx *mlx, int loaded_count)
{
	int i;

	i = 0;
	while (i < loaded_count)
	{
		if (mlx->map->textures[i].img)
			mlx_destroy_image(mlx->mlx_var, mlx->map->textures[i].img);
		i++;
	}
}

void	load_single_texture(t_mlx *mlx, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(mlx->mlx_var, path,
        &texture->width, &texture->height);
    if (!texture->img)
    {
        printf("Error loading texture: %s\n", path);
        exit(EXIT_FAILURE);
    }
    texture->addr = mlx_get_data_addr(texture->img,
        &texture->bits_per_pixel, &texture->line_length, &texture->endian);
    if (!texture->addr || texture->width <= 0 || texture->height <= 0)
    {
        printf("Invalid texture data: %s\n", path);
        mlx_destroy_image(mlx->mlx_var, texture->img);
        exit(EXIT_FAILURE);
    }
}
