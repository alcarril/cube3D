/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_celling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:45:21 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:34:55 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	render_floor_and_ceiling(t_mlx *mlx)
{
	int	x;
	int	y;
	int	horizon;

	horizon = (mlx->win_height >> 1) + mlx->player->pitch_pix;
	y = -1;
	while (++y < horizon && y < mlx->win_height)
	{
		x = -1;
		while (++x < mlx->win_width)
			buffering_pixel(x, y, mlx, mlx->map->ceiling_color_hex);
	}
	while (y < mlx->win_height)
	{
		x = -1;
		while (++x < mlx->win_width)
			buffering_pixel(x, y, mlx, mlx->map->floor_color_hex);
		y++;
	}
}

void	render_floor_and_ceiling_speed(t_mlx *mlx)
{
	t_rf	s;
	int		ceiling_limit;
	int		floor_limit;

	load_locals(&s, mlx, &ceiling_limit, &floor_limit);
	s.offset = 0;
	s.y = 0;
	while (s.y < ceiling_limit && s.y < s.height)
	{
		ft_memfillboost(s.bitmap + s.offset, s.ceiling_color, s.line_bytes);
		s.offset += s.line_len;
		s.y++;
	}
	while (s.y <= floor_limit && s.y < s.height)
	{
		s.offset += s.line_len;
		s.y++;
	}
	while (s.y < s.height)
	{
		ft_memfillboost(s.bitmap + s.offset, s.floor_color, s.line_bytes);
		s.offset += s.line_len;
		s.y++;
	}
}

void	load_locals(t_rf *s, t_mlx *mlx, int *ceiling_limit, int *floor_limit)
{
	s->width = mlx->win_width;
	s->height = mlx->win_height;
	s->bitmap = mlx->bit_map_address;
	s->line_len = mlx->line_length;
	s->bpp = mlx->bits_per_pixel >> 3;
	s->ceiling_color = mlx->map->ceiling_color_hex;
	s->floor_color = mlx->map->floor_color_hex;
	s->line_bytes = s->width * s->bpp;
	*ceiling_limit = mlx->frame->wall_start_min;
	*floor_limit = mlx->frame->wall_end_max;
	if (*ceiling_limit < 0)
		*ceiling_limit = 0;
	if (*ceiling_limit >= s->height)
		*ceiling_limit = s->height - 1;
	if (*floor_limit < 0)
		*floor_limit = 0;
	if (*floor_limit >= s->height)
		*floor_limit = s->height - 1;
}

void	render_floor_and_ceiling_amb(t_mlx *mlx)
{
	int				y;
	int				refs[3];
	float			df;
	unsigned int	colors[2];

	colors[0] = mlx->map->ceiling_color_hex;
	colors[1] = mlx->map->floor_color_hex;
	refs[HEIG] = mlx->win_height;
	refs[WIDT] = mlx->win_width;
	refs[HOR] = (refs[0] >> 1) + mlx->player->pitch_pix;
	y = 0;
	while (y < refs[HOR] && y < refs[HEIG])
	{
		df = dist_factor_ceiling(y, refs[HOR], mlx->amb.ambiance);
		colors[0] = apllyamb_ceiling(&(mlx->amb), df, colors[0]);
		buffering_line(y, colors[0], mlx, refs[WIDT]);
		y++;
	}
	while (y < refs[HEIG])
	{
		df = dist_factor_floor(refs[HEIG], y, refs[HOR], mlx->amb.ambiance);
		colors[1] = apllyamb_ceiling(&(mlx->amb), df, colors[1]);
		buffering_line(y, colors[1], mlx, refs[WIDT]);
		y++;
	}
}
