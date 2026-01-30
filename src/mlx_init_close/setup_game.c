/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:42:33 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:30:30 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

bool	setup_game(t_mlx *mlx, t_player *player, t_map *map, t_frame *frame)
{
	if (load_textures(mlx) == false)
	{
		destroy_mlx_componets(mlx_destroy_image, mlx_destroy_window,
			mlx_destroy_display, mlx);
		free_map_data(mlx);
		return (false);
	}
	map->max_distance = sqrtf((mlx->map->max_columns * mlx->map->max_columns)
			+ (mlx->map->max_rows * mlx->map->max_rows));
	setup_default_ambiance(mlx->map, &(mlx->amb));
	setup_default_phisics(&(mlx->phisics));
	mlx->player = player;
	setup_player_mouse(mlx);
	mlx->frame = frame;
	mlx->log_fd = create_fps_logfile();
	if (init_frame_data(mlx) == false || mlx->log_fd < 0)
	{
		free_game(mlx);
		return (false);
	}
	return (true);
}

void	setup_player_mouse(t_mlx *mlx)
{
	t_player	*pl;

	pl = mlx->player;
	pl->speed = SPEED_DIGITAL;
	pl->fov = 60.0f;
	pl->rad_fov = pl->fov * (PI / 180.0f);
	pl->fov_half = pl->rad_fov / 2.0f;
	ft_bzero((void *)(pl->diff), sizeof(pl->diff));
	ft_bzero((void *)(pl->v_move), sizeof(pl->v_move));
	pl->volume = EPSILON;
	pl->pitch_pix = 0;
	pl->pitch_factor = PITCH_FACTOR;
	pl->max_pitch_pix = mlx->win_height * MAX_PIXELS_PITCH;
	init_player_mouse(pl, mlx);
	init_player_phisics(pl, &(mlx->phisics));
	ft_bzero((void *)&(pl->keys), sizeof(pl->keys));
}

void	init_player_orientation_pos(t_player *pl, char cardinal, int pos[2])
{
	if (cardinal == 'N')
		pl->angle = 90.0f;
	if (cardinal == 'S')
		pl->angle = 270.0f;
	if (cardinal == 'E')
		pl->angle = 0.0f;
	if (cardinal == 'W')
		pl->angle = 180.0f;
	pl->rad_angle = pl->angle * (PI / 180.0f);
	pl->pos_x = (float)pos[X] + 0.5f;
	pl->pos_y = (float)pos[Y] + 0.5f;
}

bool	init_frame_data( t_mlx *mlx)
{
	t_frame	*f;

	f = mlx->frame;
	f->mm_height = mlx->win_height / MINI_HEIGHT;
	f->mm_widht = mlx->win_width / MINI_WIDTH;
	f->mm_scale[X] = (float)(f->mm_widht) / mlx->map->max_columns;
	f->mm_scale[Y] = (float)(f->mm_height) / mlx->map->max_rows;
	f->mm_zoom_factor = MINI_ZOOM_FACTOR;
	f->minimap_onoff = OFF;
	f->minimap_showrays = false;
	f->raycasting_onoff = ON;
	f->fish_eye = OFF;
	f->euclidean = OFF;
	f->boost = OFF;
	f->textures_onoff = ON;
	f->ambiance_onoff = OFF;
	f->delta_rays = (mlx->player->rad_fov) / mlx->win_width;
	f->phisics_onoff = OFF;
	f->dukedoom_mode = OFF;
	f->fov_distances = NULL;
	f->fov_distances = (float *)malloc(sizeof(float) * mlx->win_width);
	if (!mlx->frame->fov_distances)
		return (perror("Error allocating memory for fov_distances\n"), false);
	return (true);
}

int	create_fps_logfile(void)
{
	int	log_fd;

	log_fd = open("log/cub3d_log.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (log_fd < 0)
	{
		perror("File error ");
		return (-1);
	}
	else
		return (log_fd);
}
