/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiance_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:20:17 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/15 22:00:48 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

void	toogle_ambiance(t_mlx *mlx)
{
	if (mlx->frame->textures_onoff == OFF)
	{
		printf("WARNING: Textures are off, cannot toggle ambiance\n");
		return ;
	}
	if (mlx->frame->ambiance_onoff == ON)
	{
		mlx->frame->ambiance_onoff = OFF;
		mlx->frame->floor_celling = render_floor_and_ceiling;
		printf("AMBIANCE OFF\n");
	}
	else
	{
		mlx->frame->ambiance_onoff = ON;
		mlx->frame->floor_celling = render_floor_and_ceiling_amb;
		printf("AMBIANCE ON\n");
	}
}

bool	ambiance_keypress(t_mlx *mlx, int keysym)
{
	if (mlx->frame->ambiance_onoff == false)
	{
		printf("WARNING: Ambiance is off, cannot change ambiance\n");
		return (false);
	}
	if (keysym == XK_1)
		select_ambiance(mlx, ASTURIAS);
	else if (keysym == XK_2)
		select_ambiance(mlx, CEMENTERY);
	else if (keysym == XK_3)
		select_ambiance(mlx, OPEN);
	else
		return (false);
	return (true);
}

void	select_ambiance(t_mlx *mlx, int ambiance)
{
	if (ambiance == ASTURIAS)
	{
		config_ambiance_asturias(mlx->map, &(mlx->amb));
		printf("ASTURIAS AMBIANCE SELECTED: ");
		printf("Recomendeded for open fields\n");
	}
	else if (ambiance == CEMENTERY)
	{
		config_ambiance_cementery(&(mlx->amb));
		printf("CEMETERY AMBIANCE SELECTED: ");
		printf("Recomendeded for closed spaces or Medieval map\n");
	}
	else if (ambiance == OPEN)
	{
		config_ambiance_open(mlx->map, &(mlx->amb));
		printf("OPEN AMBIANCE SELECTED: ");
		printf("Recomendeded for open spaces with sun\n");
	}
}

