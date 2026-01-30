/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:44:58 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:36:12 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

t_texture	*select_texture(t_mlx *mlx, t_ray *ray)
{
	t_texture	*texture;

	if (ray->wall_value == BONUS_WALL)
	{
		texture = &(mlx->map->textures)[4];
		return (texture);
	}
	if (ray->side_hit == VERTICAL)
	{
		if (ray->raydir[X] > 0)
			texture = &(mlx->map->textures)[E];
		else
			texture = &(mlx->map->textures)[W];
	}
	else
	{
		if (ray->raydir[Y] > 0)
			texture = &(mlx->map->textures)[N];
		else
			texture = &(mlx->map->textures)[S];
	}
	return (texture);
}

double	calculate_wall_x(t_mlx *mlx, t_ray *ray)
{
	double	wall_x;

	if (ray->side_hit == VERTICAL)
		wall_x = mlx->player->pos_y + ray->wall_dist * ray->raydir[Y];
	else
		wall_x = mlx->player->pos_x + ray->wall_dist * ray->raydir[X];
	wall_x -= (int)(wall_x);
	if ((ray->side_hit == VERTICAL && ray->raydir[X] < 0)
		|| (ray->side_hit == HORIZONTAL && ray->raydir[Y] > 0))
	{
		wall_x = 1.0 - wall_x;
	}
	return (wall_x);
}

void	calculate_tex(t_wall *wall, t_texture *texture, int winh, t_player *pl)
{
	int	horizon;
	int	ws_offset;
	int	wall_height_half;

	wall->tex_x = (int)(wall->wall_x * (double)texture->width);
	wall->text_v_step = (float)texture->height / (float)wall->wall_height;
	horizon = (winh >> 1) + pl->pitch_pix + (int)wall->vertical_offset;
	ws_offset = wall->wall_start - horizon;
	wall_height_half = wall->wall_height >> 1;
	wall->tex_pos = (ws_offset + wall_height_half) * wall->text_v_step;
}

unsigned int	extract_color(t_texture *texture, int tex_x, int tex_y)
{
	unsigned int	color;
	char			*pixel_address;

	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	pixel_address = texture->addr + (tex_y * texture->line_length)
		+ (tex_x * (texture->bits_per_pixel >> 3));
	color = *(unsigned int *)pixel_address;
	return (color);
}
