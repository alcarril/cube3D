/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:55:10 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/21 20:56:02 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

/*
	Dibuja una columna de pared texturizada en la pantalla.
	Parámetros:
	- mlx: Puntero a la estructura principal que contiene toda la información del juego.
	- column: Índice de la columna en la pantalla donde se dibujará la pared.
	- wall: Puntero a la estructura de la pared que contiene información sobre la pared a dibujar.
	- ray: Puntero a la estructura del rayo que contiene información sobre el rayo que golpeó la pared.
	Funcionalidad:
	- Selecciona la textura adecuada según la dirección del rayo y el lado de la pared golpeada.
	- Calcula la posición exacta en la pared donde el rayo impactó para map
	  pear correctamente la textura.
	- Calcula las coordenadas de la textura y la posición inicial para el mapeo vertical.
	- Itera sobre cada píxel de la columna de la pared desde el inicio hasta el final,
	  extrayendo el color correspondiente de la textura y dibujándolo en el búfer de la imagen.
	Mejoras de microprocesador:
	+ Se calcula la textura y la posicion de wall_x una sola vez fuera del bucle de cada columna
	+ Se evita accedera un valor de puntero dentro del bucle hoot utilizando una variable local
	  t_texture *texture en vez de wall->texture (acceso a resgistros de memeria mas rapido y per
	  mite desenrrollado de loops por el compilador mejor vectorizacion mejorando SIMD)
	+ Se evita acceder a un valor de la estrcutura wall usando una variable local wall_end
	  en vez de wall->wall_end (acceso a resgistros de memeria mas rapido y permite desenroolado de 
	  loops por el compilador mejor vectorizacion mejorando SIMD)
	+ Se evita acceder a un valor de la estrcutura wall usando una variable local wall_tex_y
	  en vez de wall->tex_y (acceso a resgistros de memeria mas rapido y permite desenroolado de
	  loops por el compilador mejor vectorizacion emjorando SIMD)
	
*/
void draw_wall_column_tex(t_mlx *mlx, int column, t_wall *wall, t_ray *ray)
{
	int 			i;
	unsigned int	color;
	int				wall_end;
	int				wall_tex_y;
	t_texture		*texture;

	wall_end = wall->wall_end;
	texture = select_texture(mlx, ray);
	wall->wall_x = calculate_wall_x(mlx, ray);
	calculate_tex(wall, texture, mlx->win_height, mlx->player);
	i = wall->wall_start;
	while (i <= wall_end)
	{	
		wall_tex_y = (int)wall->tex_pos;		
		color = extract_color(texture, wall->tex_x, wall_tex_y);
		buffering_pixel(column, i, mlx, color);
		wall->tex_pos += wall->text_v_step;
		i++;
	}
}


/*
	Dibuja una columna de pared texturizada en la pantalla.
	Parámetros:
	- mlx: Puntero a la estructura principal que contiene toda la información del juego.
	- column: Índice de la columna en la pantalla donde se dibujará la pared.
	- wall: Puntero a la estructura de la pared que contiene información sobre la pared a dibujar.
	- ray: Puntero a la estructura del rayo que contiene información sobre el rayo que golpeó la pared.
	Optimizaciones de microporcesador:
	+ Se evita acceder a un valor de la estrcutura wall usando una variable local wall_end
	  en vez de wall->wall_end (acceso a resgistros de memeria mas rapido y permite desenroolado de 
	  loops por el compilador mejor vectorizacion mejorando SIMD)
	+ Se evita acceder a un valor de la estrcutura wall usando una variable local wall_tex_y
	  en vez de wall->tex_y (acceso a resgistros de memeria mas rapido y permite desenroolado de
	  loops por el compilador mejor vectorizacion emjorando SIMD)
	+ Se calcula la proporción de distancia una sola vez fuera del bucle de cada columna
	+ Se evita la división dentro del bucle hoot utilizando la multiplicación por el inverso:
	  en lugar de dividir por la distancia máxima, se multiplica por su inverso precomputado:
	  si proporcion_dist = ray->wall_dist / max_distance;
	  se puede reescribir como:
	  float inv_maxdistance = 1.0f / max_distance;
	  proporcion_dist = ray->wall_dist * inv_max_distance;
	  Esto reduce la carga computacional dentro del bucle crítico. (hoot loop)
	+ La eleccion de ambiente o no en vez de hacerlo con un if dentro de una funcion aunque el brach predictor
	  moderno es muy bueno siempre es mejor evitar saltos condicionales en bucles criticos. Por lo que se decide
	  antes si llamar al fucnion que tiene el bucle con ambiente o sin ambiente.
	- Fog color en variable local par ano hacer indireccion en cada iteracion del bucle y
	 asi usar registros CPU  o cache directamente sin mas pasos intermedios
*/
void	drawinglopp_tex_amb(t_mlx *mlx, int column, t_wall *wall, t_ray *ray)
{
	int i;
	unsigned int color;
	float proporcion_dist;
	int wall_end;
	int wall_tex_y;

	proporcion_dist = ray->wall_dist * mlx->amb.vinv_max_diatance;
	wall->texture = select_texture(mlx, ray);
	wall->wall_x = calculate_wall_x(mlx, ray);
	calculate_tex(wall, wall->texture, mlx->win_height, mlx->player);
	wall_end = wall->wall_end;
	i = wall->wall_start - 1;
	while (++i <= wall_end)
	{	
		wall_tex_y = (int)wall->tex_pos;
		color = extract_color(wall->texture, wall->tex_x, wall_tex_y);
		color = shade_inverse(color , mlx->amb.k_factor_walls, proporcion_dist * mlx->amb.mult_shader_walls);
		color = apply_desaturation(color, proporcion_dist * 0.6f);
		color = apply_fog_pixel(color, mlx->amb.fog_color_walls, proporcion_dist * mlx->amb.mult_fog_walls);
		buffering_pixel(column, i, mlx, color);
		wall->tex_pos += wall->text_v_step;
	}
}