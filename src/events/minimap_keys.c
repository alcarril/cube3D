/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 21:16:10 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:26:20 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

void	toggle_minimap(t_mlx *mlx)
{
	if (mlx == NULL || mlx->frame == NULL)
		return ;
	if (mlx->frame->minimap_onoff == true)
	{
		mlx->frame->minimap_onoff = false;
		printf("MINIMAP OFF\n");
	}
	else
	{
		mlx->frame->minimap_onoff = true;
		printf("MINIMAP ON\n");
	}
}

void	toggle_rays(t_mlx *mlx)
{
	if (mlx->frame->minimap_showrays == true)
	{
		mlx->frame->minimap_showrays = false;
		printf("MINIMAP RAYS OFF\n");
	}
	else
	{
		mlx->frame->minimap_showrays = true;
		printf("MINIMAP RAYS ON\n");
	}
}

void	minimap_zoom(t_mlx *mlx, bool flag)
{
	if (mlx->frame->minimap_onoff == false)
	{
		printf("WARNING: Minimap is off, cannot zoom\n");
		return ;
	}
	if (flag == true)
	{
		mlx->frame->mm_zoom_factor += 0.25f;
		if (mlx->frame->mm_zoom_factor > MINIMAP_MAX_ZOOM)
			mlx->frame->mm_zoom_factor = MINIMAP_MAX_ZOOM;
		printf("MINIMAP ZOOM  IN FACTOR: %.2f\n", mlx->frame->mm_zoom_factor);
		render_frame2d(mlx);
	}
	else
	{
		mlx->frame->mm_zoom_factor -= 0.25f;
		if (mlx->frame->mm_zoom_factor < MINIMAP_MIN_ZOOM)
			mlx->frame->mm_zoom_factor = MINIMAP_MIN_ZOOM;
		printf("MINIMAP ZOOM  OUT FACTOR: %.2f\n", mlx->frame->mm_zoom_factor);
		render_frame2d(mlx);
	}
}
