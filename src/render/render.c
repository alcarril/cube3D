/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 21:34:21 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/08 15:23:03 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	draw_wall_column(t_mlx *mlx, int column, int wall_height);
int		calculate_wall_height(float perpendicular_distance, int win_height);
float	get_ray_distance_euclidean(t_mlx *mlx, t_ray *ray);
float	get_ray_distance_perpendicular(t_mlx *mlx, t_ray *ray, bool side);
bool	dda_loop(t_mlx * mlx, t_ray *ray);
void	calc_side_dist(t_mlx * mlx, t_ray *ray);
float	get_distance_to_wall(t_mlx *mlx, t_ray *ray, float ray_angle);
void	set_ray(t_mlx *mlx, t_ray *ray, float ray_angle);

//se puede optimizar pasando por refencia las variables
void	buffering_pixel(int x, int y, t_mlx *mlx, int color)
{
	unsigned int	offset;

	if (x < 0 || x > mlx->win_width || y < 0 || y > mlx->win_height)
		return ;
	offset = (y * mlx->line_length) + (x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)(mlx->bit_map_address + offset) = color;
}

/*
	Función principal para manejar el ciclo de renderizado del motor del juego:
	- Se activa gracias al hook de mlx_loop_hook
	- Maneja el movimiento del jugador
	- Limpia el buffer de la imagen (si no se limpia no funciona bien el render)
	- Llama a la función de raycasting para renderizar la escena 3D
	- Llama a la función para renderizar el minimapa 2D si está activado
	- Finalmente, actualiza la ventana con la nueva imagen renderizada	
*/
int	game_engine(t_mlx *mlx)
{
	move_player(mlx);
	ft_bzero(mlx->bit_map_address, mlx->win_height * mlx->line_length);
	if (mlx->frame->raycasting_onoff == true)
		throw_rays(mlx);
	if (mlx->frame->minimap_onoff == true)
		render_frame2D(mlx);
	mlx_put_image_to_window(mlx->mlx_var, mlx->mlx_window, mlx->mlx_img, 0, 0);
	return (0);
}


//barido por defecto invierte respeto al minimapta hayq ue barrede deizquierda a derecha o de derecha a izquierda 
//apara hcer un ajuste elegante y no rmper al estrcutura, no se tiene que ajustar desde la bifferizacin porque es 
// Función principal para lanzar los rayos y realizar la bufferización
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
	int		n_rays;

	fov_half = mlx->player->rad_fov / 2;
	rad_dif = (mlx->player->rad_fov) / mlx->win_width;
	ray_angle = (mlx->player->rad_angle) + fov_half;
	n_rays = 0;
	while (n_rays < mlx->win_width)
	{
		cast_ray(mlx, n_rays, ray_angle);
		ray_angle -= rad_dif;
		n_rays++;
	}
}

/*
	Función auxiliar para manejar la lógica de un solo rayo
	- Inicializa los parámetros del rayo
	- Calcula la distancia hasta la pared utilizando el algoritmo DDA
	- Calcula la altura de la pared en función de la distancia
	- Dibuja la columna de la pared en la posición correspondiente de la pantalla
*/
void cast_ray(t_mlx *mlx, int n_rays, float ray_angle)
{
	t_ray	ray;
	float	distance;
	int		wall_height;

	set_ray(mlx, &ray, ray_angle);
	distance = get_distance_to_wall(mlx, &ray, ray_angle);
	wall_height = calculate_wall_height(distance, mlx->win_height);
	draw_wall_column(mlx, n_rays, wall_height);
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

float get_distance_to_wall(t_mlx *mlx, t_ray *ray, float ray_angle)
{
	bool	side;
	float	wall_dist;
	
	calc_side_dist(mlx, ray);
	side = dda_loop(mlx, ray);
	if (mlx->frame->euclidean == false)
		wall_dist = get_ray_distance_perpendicular(mlx, ray, side);
	else
		wall_dist = get_ray_distance_euclidean(mlx, ray);
	if (mlx->frame->fish_eye == false)
		wall_dist = wall_dist * cos(ray_angle - (mlx->player->rad_angle));
	return (wall_dist);
}

// Determinar la dirección del paso y la distancia inicial a los lados
//falta control de errores de seno y conseno siempre es entre -1 y 1
void	calc_side_dist(t_mlx * mlx, t_ray *ray)
{
	if (ray->raydir[X] < 0)
	{
		ray->step[X] = -1;
		ray->sidedist[X] = (mlx->player->pos_x - ray->map[X]) * ray->delta[X];
	}
	else
	{
		ray->step[X] = 1;
		ray->sidedist[X] = (ray->map[X] + 1.0 - mlx->player->pos_x) * ray->delta[X];
	}
	if (ray->raydir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->sidedist[Y] = (mlx->player->pos_y - ray->map[Y]) * ray->delta[Y];
	}
	else
	{
		ray->step[Y] = 1;
		ray->sidedist[Y] = (ray->map[Y] + 1.0 - mlx->player->pos_y) * ray->delta[Y];
	}
}

// Avanzar al siguiente lado de la celda
bool	dda_loop(t_mlx * mlx, t_ray *ray)
{
	int hit;
	bool side;

	hit = 0;
	side = 0;
	while (hit == 0)
	{
		if (ray->sidedist[X] < ray->sidedist[Y])
		{
			ray->sidedist[X] += ray->delta[X];
			ray->map[X] += ray->step[X];
			side = VERTICAL;
		}
		else
		{
			ray->sidedist[Y] += ray->delta[Y];
			ray->map[Y] += ray->step[Y];
			side = HORIZONTAL;
		}
		// if (ray->map[X] < 0 || ray->map[X] >= (int)mlx->map->max_columns ||
		//     ray->map[Y] < 0 || ray->map[Y] >= (int)mlx->map->max_rows)
		//     return (false);
		if (mlx->map->map_grids[ray->map[Y]][ray->map[X]] == WALL)
			hit = 1;
	}
	return (side);
}

//dda algorithm calculus
float get_ray_distance_perpendicular(t_mlx *mlx, t_ray *ray, bool side)
{
	float	wall_dist;
	
	if (side == VERTICAL)
		wall_dist = (ray->map[X] - mlx->player->pos_x + (1 - ray->step[X]) / 2) / ray->raydir[X];
	else
		wall_dist = (ray->map[Y] - mlx->player->pos_y + (1 - ray->step[Y]) / 2) / ray->raydir[Y];
	
	return (wall_dist);
}

//trigonmetric calculus
float get_ray_distance_euclidean(t_mlx *mlx, t_ray *ray)
{
	float fish_eye_dist;
	
	fish_eye_dist = sqrt(pow(ray->map[X] - mlx->player->pos_x, 2) +
							   pow(ray->map[Y] - mlx->player->pos_y, 2));
	 return fish_eye_dist;
}

int	calculate_wall_height(float perpendicular_distance, int win_height)
{
	int wall_height;
	
	if (perpendicular_distance <= 0) 
		return (win_height);
	wall_height = (int)(win_height / perpendicular_distance);
	return (wall_height);
}

void	draw_wall_column(t_mlx *mlx, int column, int wall_height)
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
}
