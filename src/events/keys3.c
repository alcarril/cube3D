/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:59:20 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/09 23:00:30 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

void	toogle_dist_calc(t_mlx *mlx)
{
	if (mlx->frame->draw_walls == draw_wall_column)
	{
		if (mlx->frame->euclidean == false)
			mlx->frame->euclidean = true;
		else
			mlx->frame->euclidean = false;
	}
	else
		perror("Cannot toggle distance calculation method when textures are enabled\n");
}

void	print_controls(void)
{
	printf("Controls:\n");
	printf("WASD: Move Up, Down, Left, Right\n");
	printf("Left Arrow: Rotate Counterclockwise\n");
	printf("Right Arrow: Rotate Clockwise\n");
	printf("Left Shift: Sprint\n");
	printf("M: Toggle Minimap\n");
	printf("R: Toggle Rays on Minimap\n");
	printf("F: Toggle Fish Eye Effect\n");
	printf("O: Toggle Raycasting On/Off\n");
	printf("E: Toggle Distance Calculation (Euclidean/Perpendicular)\n");
	printf("T: Toggle Textures On/Off\n");
	printf("C: Toggle Floor and Ceiling Rendering Method\n");
	printf("ESC: Exit Game\n");
}