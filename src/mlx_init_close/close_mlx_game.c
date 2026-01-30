/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_mlx_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:53:10 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:29:38 by carbon-m         ###   ########.fr       */
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

void	free_loaded_textures(t_mlx *mlx, int loaded, int max_textures, bool f)
{
	int	i;
	int	max;

	if (f)
		max = loaded;
	else
		max = max_textures;
	i = 0;
	while (i < max)
	{
		if (mlx->map->textures[i].img)
			mlx_destroy_image(mlx->mlx_var, mlx->map->textures[i].img);
		i++;
	}
}

int	close_game_manager(t_mlx *mlx)
{
	mlx_mouse_show(mlx->mlx_var, mlx->mlx_window);
	free_loaded_textures(mlx, 0, mlx->map->n_textures, 0);
	mlx_destroy_image(mlx->mlx_var,
		mlx->mlx_img);
	mlx_destroy_window(mlx->mlx_var,
		mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_var);
	free(mlx->mlx_var);
	if (mlx->frame->fov_distances != NULL)
		free(mlx->frame->fov_distances);
	close(mlx->log_fd);
	free_map_data(mlx);
	exit(1);
}

void	free_game(t_mlx *mlx)
{
	mlx_mouse_show(mlx->mlx_var, mlx->mlx_window);
	free_loaded_textures(mlx, 0, mlx->map->n_textures, 0);
	mlx_destroy_image(mlx->mlx_var,
		mlx->mlx_img);
	mlx_destroy_window(mlx->mlx_var,
		mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_var);
	free(mlx->mlx_var);
	if (mlx->frame->fov_distances != NULL)
		free(mlx->frame->fov_distances);
	free_map_data(mlx);
	close(mlx->log_fd);
}

void	free_map_data(t_mlx *mlx)
{
	unsigned int	i;

	i = 0;
	while (i < (unsigned int)mlx->map->n_textures)
	{
		free(mlx->map->texture_paths[i]);
		i++;
	}
	i = 0;
	while (i < mlx->map->max_rows)
	{
		free(mlx->map->map_grids[i]);
		i++;
	}
	free(mlx->map->map_grids);
}
