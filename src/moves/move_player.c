/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:30:42 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:32:12 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	rotate_player(t_player *player, float delta_grades)
{
	if (player->keys.r_clockwise == true)
		player->angle -= delta_grades;
	else if (player->keys.r_counterclockwise == true)
		player->angle += delta_grades;
	if (player->angle >= 360.0f)
		player->angle -= 360.0f;
	else if (player->angle < 0.0f)
		player->angle += 360.0f;
	player->rad_angle = player->angle * (PI / 180.0f);
}

void	axis_y_pitch(t_player *player)
{
	t_player	*pl;
	static int	max_pitch;

	if (max_pitch == 0)
		max_pitch = player->max_pitch_pix;
	pl = player;
	if (pl->keys.look_up == true)
		pl->pitch_pix += pl->pitch_factor * pl->max_pitch_pix;
	if (pl->keys.look_down == true)
		pl->pitch_pix -= pl->pitch_factor * pl->max_pitch_pix;
	if (pl->pitch_pix > pl->max_pitch_pix)
		pl->pitch_pix = pl->max_pitch_pix;
	if (pl->pitch_pix < -pl->max_pitch_pix)
		pl->pitch_pix = -pl->max_pitch_pix;
	return ;
}

void	jump_speed_vecmove(t_mlx *mlx)
{
	t_player	*pl;
	long long	delta_time;

	pl = mlx->player;
	if (mlx->frame->phisics_onoff == ON)
	{
		delta_time = mlx->del_timestamp;
		if (delta_time > MAX_DT_FRAME)
			delta_time = MAX_DT_FRAME;
		jump(mlx, delta_time);
		if (mlx->frame->dukedoom_mode == OFF)
			difspeed_and_vecmove(mlx, delta_time);
		else
			difvspeed_and_vecmove_nukedoom(mlx, delta_time);
	}
	else
	{
		delta_time = 1;
		vectorization(mlx->player, delta_time, pl->speed, pl->rad_angle);
	}
}

bool	is_collision(float x, float y, t_mlx *mlx, float e)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || my < 0 || mx >= (int)mlx->map->max_columns
		|| my >= (int)mlx->map->max_rows)
	{
		return (true);
	}
	return (
		is_wall_tile(mlx->map->map_grids[(int)(y + e)][(int)(x + e)]) ||
		is_wall_tile(mlx->map->map_grids[(int)(y - e)][(int)(x + e)]) ||
		is_wall_tile(mlx->map->map_grids[(int)(y + e)][(int)(x - e)]) ||
		is_wall_tile(mlx->map->map_grids[(int)(y - e)][(int)(x - e)])
	);
}

void	move_player(t_mlx *mlx)
{
	t_player	*player;
	float		new_pos[2];
	bool		colision[2];

	player = mlx->player;
	rotate_player(player, 1.1f);
	axis_y_pitch(player);
	jump_speed_vecmove(mlx);
	new_pos[X] = player->pos_x + player->diff[X];
	new_pos[Y] = player->pos_y + player->diff[Y];
	colision[X] = is_collision(new_pos[X], player->pos_y, mlx, player->volume);
	colision[Y] = is_collision(player->pos_x, new_pos[Y], mlx, player->volume);
	if (!colision[X] && !colision[Y])
	{
		player->pos_x = new_pos[X];
		player->pos_y = new_pos[Y];
	}
	else
	{
		if (!colision[X])
			player->pos_x += player->diff[X] * WALL_FRICTION;
		if (!colision[Y])
			player->pos_y += player->diff[Y] * WALL_FRICTION;
	}
}
