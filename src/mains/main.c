/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:12:38 by alejandro         #+#    #+#             */
/*   Updated: 2025/12/21 20:04:54 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

int main (void)
{
	t_mlx	mlx;
	if (!setup_mlx_enviroment(&mlx))
		return (1);
	mlx_loop(mlx.mlx_var);
	return(0);
}