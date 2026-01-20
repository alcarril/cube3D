/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phisics_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 06:00:34 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/20 08:40:19 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"


bool	phisics_engine_keypress(t_mlx *mlx, int keysym)
{
	if (keysym == XK_p)
		toggle_phisics_mode(mlx);
	else if (keysym == XK_k)
		toggle_dukedoom_mode(mlx);
	else
		return (false);
	return (true);
}

void	toggle_phisics_mode(t_mlx *mlx)
{
	if (mlx->frame->phisics_onoff == OFF)
	{
		mlx->frame->phisics_onoff = ON;
		printf("Phisics ENABLED: ");
		printf("Now you can experince aceleration, friction and traccion!\n");
	}
	else
	{
		mlx->frame->phisics_onoff = OFF;
		printf("Phisics DISABLED: ");
	}
}

void	toggle_dukedoom_mode(t_mlx *mlx)
{
	if (mlx->frame->dukedoom_mode == OFF)
	{
		mlx->frame->dukedoom_mode = ON;
		printf("DukeDoom mode ENABLED: ");
		printf("Now you can experince Duke Nukem style phisics!\n");
	}
	else
	{
		mlx->frame->dukedoom_mode = OFF;
		printf("DukeDoom mode DISABLED: ");
	}
}

// Tabla de fricción, tracción y aceleración según la superficie:
// | Superficie   | Fricción | Tracción | Aceleración | Sensación                           |
// | ------------ | -------- | -------- | ----------- | ----------------------------------- |
// | Asfalto seco | 0.0020   | 1.0      | 0.020       | Arranque fuerte, frena rápido       |
// | Tierra       | 0.0012   | 0.8      | 0.012       | Algo de derrape                     |
// | Barro        | 0.0008   | 0.6      | 0.008       | Patina al acelerar                  |
// | Hielo        | 0.0002   | 0.2      | 0.002       | Apenas acelera, mucho deslizamiento |