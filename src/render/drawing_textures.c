/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:55:10 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:34:36 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	draw_wall_column_tex(t_mlx *mlx, int column, t_wall *wall, t_ray *ray)
{
	t_texture		*texture;
	unsigned int	color;
	int				i;
	int				wall_end;
	int				wall_tex_y;

	wall_end = wall->wall_end;
	texture = select_texture(mlx, ray);
	wall->wall_x = calculate_wall_x(mlx, ray);
	calculate_tex(wall, texture, mlx->win_height, mlx->player);
	i = wall->wall_start;
	while (i <= wall_end)
	{
		wall_tex_y = (int)wall->tex_pos;
		color = extract_color(texture, wall->tex_x, wall_tex_y);
		buffering_pixel(column, i, mlx, color);
		wall->tex_pos += wall->text_v_step;
		i++;
	}
}

void	drawwallcoltexspeed(t_mlx *m, int col, t_wall *w, t_ray *ray)
{
	t_locals	l;
	t_texture	*texture;

	texture = select_texture(m, ray);
	w->wall_x = calculate_wall_x(m, ray);
	calculate_tex(w, texture, m->win_height, m->player);
	l.win_width = m->win_width;
	l.wall_end = w->wall_end;
	l.i = w->wall_start - 1;
	l.tex_pos = w->tex_pos;
	l.text_v_step = w->text_v_step;
	l.tex_stride = texture->line_length >> 2;
	l.tex_ptr = (t_u *)texture->addr + w->tex_x;
	l.fb_ptr = (t_u *)m->bit_map_address + col + w->wall_start * m->win_width;
	while (++l.i <= l.wall_end)
	{
		l.tex_y = (int)l.tex_pos;
		if (l.tex_y < 0)
			l.tex_y = 0;
		else if (l.tex_y >= texture->height)
			l.tex_y = texture->height - 1;
		*l.fb_ptr = l.tex_ptr[l.tex_y * l.tex_stride];
		l.tex_pos += l.text_v_step;
		l.fb_ptr += l.win_width;
	}
}

void	drawinglopp_tex_amb(t_mlx *mlx, int column, t_wall *wall, t_ray *ray)
{
	unsigned int	color;
	float			proporcion_dist;
	int				i;
	int				wall_end;
	int				wall_tex_y;

	proporcion_dist = ray->wall_dist * mlx->amb.vinv_max_diatance;
	wall->texture = select_texture(mlx, ray);
	wall->wall_x = calculate_wall_x(mlx, ray);
	calculate_tex(wall, wall->texture, mlx->win_height, mlx->player);
	wall_end = wall->wall_end;
	i = wall->wall_start - 1;
	while (++i <= wall_end)
	{
		wall_tex_y = (int)wall->tex_pos;
		color = extract_color(wall->texture, wall->tex_x, wall_tex_y);
		color = shade_inverse(color, mlx->amb.k_factor_walls, proporcion_dist
				* mlx->amb.mult_shader_walls);
		color = apply_desaturation(color, proporcion_dist * 0.6f);
		color = apply_fog_pixel(color, mlx->amb.fog_color_walls,
				proporcion_dist * mlx->amb.mult_fog_walls);
		buffering_pixel(column, i, mlx, color);
		wall->tex_pos += wall->text_v_step;
	}
}
