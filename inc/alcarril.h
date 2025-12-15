/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcarril.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:14:57 by alejandro         #+#    #+#             */
/*   Updated: 2025/12/15 05:39:27 by alejandro        ###   ########.fr       */
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

typedef struct s_image_data
{
	void							*img_var;
	char							*name;
	char							*bit_map_address;
	char							*bit_map_address_copy;
	int								bits_per_pixel;
	int								line_length;
	int								endian;
	char							**config;
	int								origin[2];
	double							zoom;
	double							with[2];
}									t_imgdata;

typedef struct s_mlx_enviroment
{
	void							*mlx_var;
	void							*window;
	t_imgdata					*img_data;
}				t_mlxenv;

/*
	FUNCTION PROTOTIPES:
*/


#endif