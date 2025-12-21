/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcarril.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:14:57 by alejandro         #+#    #+#             */
/*   Updated: 2025/12/21 20:09:08 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALCARRIL_H
#define ALCARRIL_H

/*
	LIBRERIAS:
*/

#include "cube3D.h"

/*
	DEFINES:
*/

# define WIDTH 800
# define HEIGHT 800

/*
	STRUCTS:
*/

typedef struct	s_mlx_components
{
	void	*mlx_var;
	void	*mlx_window;
	void	*mlx_img;
	char	*win_name;
	//offsetinfo
	char	*bit_map_address;
	char	*bit_map_address_copy;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	//extras
	int		origin[2];

}	t_mlx;

typedef struct	s_player_data
{
	int	pos_x;
	int	pos_y;
	
}	t_player;

/*
	FUNCTION PROTOTIPES:
*/


#endif