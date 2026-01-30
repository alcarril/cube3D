/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_engine_keys.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 20:54:29 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:25:15 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

void	toogle_raycasting(t_mlx *mlx)
{
	t_frame	*f;

	f = mlx->frame;
	if (mlx->frame->raycasting_onoff == ON)
	{
		mlx->frame->raycasting_onoff = OFF;
		f->mm_height *= MINI_HEIGHT;
		f->mm_widht *= MINI_WIDTH;
		f->minimap_onoff = ON;
		printf("RAYCASTING OFF\n");
	}
	else
	{
		mlx->frame->raycasting_onoff = ON;
		f->mm_height /= MINI_HEIGHT;
		f->mm_widht /= MINI_WIDTH;
		printf("RAYCASTING ON\n");
	}
	f->mm_scale[X] = (float)(f->mm_widht) / mlx->map->max_columns;
	f->mm_scale[Y] = (float)(f->mm_height) / mlx->map->max_rows;
}

void	toggle_textures(t_mlx *mlx)
{
	if (mlx->frame->textures_onoff == OFF)
	{
		mlx->frame->textures_onoff = ON;
		mlx->frame->fish_eye = OFF;
		mlx->frame->euclidean = OFF;
		printf("TEXTURED ENABLED\n");
	}
	else
	{
		mlx->frame->textures_onoff = OFF;
		mlx->frame->ambiance_onoff = OFF;
		printf("TEXTURES DISABLED\n");
	}
}

void	toogle_floor_celling(t_mlx *mlx)
{
	if (mlx->has_been_mouse_in_window == false)
	{
		printf("WARNING: Boost mode requires kernell create pixmap");
		printf("for mouse\n");
		printf("TRADUCTION: Put the f... mouse in window at least once !!!\n");
		return ;
	}
	if (mlx->frame->ambiance_onoff == ON)
	{
		printf("WARNING: Ambiance is on, cannot toggle floor and ceiling");
		printf("rendering method\n");
		return ;
	}
	if (mlx->frame->boost == OFF)
	{
		mlx->frame->boost = ON;
		printf("FAST floor and ceiling rendering enabled\n");
		write(mlx->log_fd, "BOOST MODE ENABLED\n", 19);
	}
	else
	{
		mlx->frame->boost = OFF;
		printf("ACURATED floor and ceiling rendering enabled\n");
		write(mlx->log_fd, "BOOST MODE DISABLED\n", 20);
	}
}

void	toogle_dist_calc(t_mlx *mlx)
{
	if (mlx->frame->textures_onoff == OFF)
	{
		if (mlx->frame->euclidean == false)
		{
			mlx->frame->euclidean = true;
			printf("EUCLIDEAN DISTANCE ENABLED\n");
		}
		else
		{
			mlx->frame->euclidean = false;
			printf("PERPENDICULAR DISTANCE ENABLED\n");
		}
	}
	else
		printf("WARNING!!: Textures must be off to toggle euclidean dist\n");
}

void	toggle_fish_eye(t_mlx *mlx)
{
	if (mlx->frame->textures_onoff == OFF)
	{
		if (mlx->frame->fish_eye == true)
		{
			mlx->frame->fish_eye = false;
			printf("FISH EYE CORRECTION OFF\n");
		}
		else
		{
			mlx->frame->fish_eye = true;
			printf("FISH EYE CORRECTION ON\n");
		}
	}
	else
		printf("WARNING!!: Textures must be off to toggle fish eye effect\n");
}
