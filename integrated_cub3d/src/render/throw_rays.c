/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 00:00:00 by integrated        #+#    #+#             */
/*   Updated: 2026/01/04 12:42:58 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

// Implementación básica de throw_rays que actúa como un wrapper para render_frame2D
int	throw_rays(t_mlx *mlx)
{
	if (!mlx)
		return (0);
	return (render_frame2D(mlx));
}