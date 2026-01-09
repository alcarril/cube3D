/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:04:35 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/09 14:19:58 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

/*
	- Función principal para lanzar los rayos y realizar la bufferización
	- Hace el barrido de rayos desde la izquierda hasta la derecha del campo de visión.
	 Lo hace asi porque los ejes de la ventana en mlx estan invertidos respecto al minimapa.
	 Sino ocurriria un efecto espejo en la visualización 3D. y es mejor hacerlo asi que corregir desde
	 la bufferización.
	- La conversion a raadianes se hace en cada frame, podria optimizarse guardando el valor en la estructura del jugador
	  pero no es un gran gasto computacional y mejora la legibilidad del código.
*/
void	throw_rays(t_mlx *mlx)
{
	float	ray_angle;
	float	rad_dif;
	float	fov_half;
	int		n_ray;

	fov_half = mlx->player->rad_fov / 2;
	rad_dif = (mlx->player->rad_fov) / mlx->win_width;
	ray_angle = (mlx->player->rad_angle) + fov_half;
	n_ray = 0;
	while (n_ray < mlx->win_width)
	{
		cast_ray(mlx,n_ray, ray_angle);
		ray_angle -= rad_dif;
		n_ray++;
	}
}

/*
	Función auxiliar para manejar la lógica de un solo rayo
	- Inicializa los parámetros del rayo
	- Calcula la distancia hasta la pared utilizando el algoritmo DDA
	- Calcula la altura de la pared en función de la distancia
	- Dibuja la columna de la pared en la posición correspondiente de la pantalla
*/
void	cast_ray(t_mlx *mlx, int n_ray, float ray_angle)
{
	t_ray	ray;
	int		wall_height;
	int		a = 2;
	
	set_ray(mlx, &ray, ray_angle);
	ray.proyected_wall_dist = get_distance_to_wall(mlx, &ray, ray_angle);
	wall_height = calculate_wall_height(ray.proyected_wall_dist, mlx->win_height);
	if (a == 1)
		draw_wall_column1(mlx, n_ray, wall_height);
	else
		draw_wall_column(mlx, n_ray, wall_height, &ray);
}

/*
	Inicializar los parámetros del rayo:
	- Dirección del rayo en los ejes X e Y
	- Ajuste de norte-sur en el seno
*/
void	set_ray(t_mlx *mlx, t_ray *ray, float ray_angle)
{
	ray->raydir[X] = cos(ray_angle);
	ray->raydir[Y] = -sin(ray_angle); //ajuste norte sur
	ray->map[X] = (int)(mlx->player->pos_x);
	ray->map[Y] = (int)(mlx->player->pos_y);
	if (ray->raydir[X] == 0)
		ray->delta[X] = 1e30; // Evitar división por cero //porque ese nuemero
	else
		ray->delta[X] = fabs(1 / ray->raydir[X]);
	if (ray->raydir[Y] == 0)
		ray->delta[Y] = 1e30; // Evitar división por cero
	else
		ray->delta[Y] = fabs(1 / ray->raydir[Y]);
}

float	get_distance_to_wall(t_mlx *mlx, t_ray *ray, float ray_angle)
{
	float	wall_dist_corrected;
	
	calc_side_dist(mlx, ray);
	dda_loop(mlx, ray);
	if (mlx->frame->euclidean == false)
		ray->perp_wall_dist = get_ray_distance_perpendicular(mlx, ray);
	else
		ray->perp_wall_dist = get_ray_distance_euclidean(mlx, ray);
	if (mlx->frame->fish_eye == false)
		wall_dist_corrected = ray->perp_wall_dist * cos(ray_angle - (mlx->player->rad_angle));//
	return (wall_dist_corrected);
}

void	draw_wall_column1(t_mlx *mlx, int column, int wall_height)
{
	int	wall_start;
	int	wall_end;
	int i;
	
	i = 0;
	wall_start = (mlx->win_height / 2) - (wall_height / 2);
	wall_end = (mlx->win_height / 2) + (wall_height / 2);
	i = wall_start;
	while (i <= wall_end)
	{
		buffering_pixel(column, i, mlx, 0x00FFF00000); // Color rojo
		i++;
	}
	// printf("pedro\n");
}


// Selecciona la textura según el lado y la dirección del rayo
t_texture *select_texture(t_mlx *mlx, t_ray *ray)
{
	t_texture *texture;

	if (ray->side_hit == VERTICAL)
	{
		if (ray->raydir[X] > 0)
			texture = &mlx->map->textures[2]; // EAST
		else
			texture = &mlx->map->textures[3]; // WEST
	}
	else
	{
		if (ray->raydir[Y] > 0)
			texture = &mlx->map->textures[0]; // NORTH
		else
			texture = &mlx->map->textures[1]; // SOUTH
	}
	return texture;
}

// Calcula el inicio y fin de la pared en la pantalla-> esta esta bine
void calculate_wall_limits(int *wall_start, int *wall_end, int wall_height, int win_height)
{
	*wall_start = (win_height / 2) - (wall_height / 2);
	*wall_end = (win_height / 2) + (wall_height / 2);

	if (*wall_start < 0)
		*wall_start = 0;
	if (*wall_end >= win_height)
		*wall_end = win_height - 1;
}

/*
	Viene de las ecuaciones parametricas de la linea
	x = x0 + t * dx
	Donde X0 e Y0 son las coordenadas del jugador
	DX y DY son las direcciones del rayo
	t es la distancia perpendicular a la pared
*/

double calculate_wall_x(t_mlx *mlx, t_ray *ray)
{
	double wall_x;

	if (ray->side_hit == VERTICAL)
		wall_x = mlx->player->pos_y + ray->perp_wall_dist * ray->raydir[Y];
	else
		wall_x = mlx->player->pos_x + ray->perp_wall_dist * ray->raydir[X];
	
	wall_x -= floor(wall_x);

	// INVERTIMOS LA LÓGICA:
	// Antes tenías (VERTICAL && raydir[X] > 0)
	// Cámbialo por esto para "darle la vuelta" a todas las caras:
	if ((ray->side_hit == VERTICAL && ray->raydir[X] < 0) || 
		(ray->side_hit == HORIZONTAL && ray->raydir[Y] > 0))
	{
		wall_x = 1.0 - wall_x;
	}
	return wall_x;
}

int calculate_tex_x(double wall_x, t_texture *texture)
{
	int tex_x;

	// wall_x ya está corregido, solo escalamos al ancho de la imagen
	tex_x = (int)(wall_x * (double)texture->width);

	// Un pequeño "guardrail" para no salirnos de la memoria (opcional)
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= texture->width) tex_x = texture->width - 1;

	return tex_x;
}

void draw_wall_column(t_mlx *mlx, int column, int wall_height, t_ray *ray)
{
	int wall_start, wall_end, tex_x, tex_y, i;
	float step, tex_pos;
	double wall_x;
	int color;
	t_texture *texture;

	// Seleccionar la textura
	texture = select_texture(mlx, ray);

	// Calcular los límites de la pared
	calculate_wall_limits(&wall_start, &wall_end, wall_height, mlx->win_height);

	// Calcular wall_x
	wall_x = calculate_wall_x(mlx, ray);

	// Calcular tex_x
	tex_x = calculate_tex_x(wall_x, texture);

	// Calcular el paso y la posición inicial en la textura
	step = (float)texture->height / (float)wall_height;
	tex_pos = (wall_start - mlx->win_height / 2 + wall_height / 2) * step;

	// Dibujar la columna
	for (i = wall_start; i <= wall_end; i++)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;

		color = *(unsigned int *)(texture->addr
				+ tex_y * texture->line_length
				+ tex_x * (texture->bits_per_pixel / 8));

		buffering_pixel(column, i, mlx, color);
		tex_pos += step;
	}
}