/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:45:15 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/13 15:12:18 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	update_minimap_dinamic_offset(t_mlx *mlx);
void	update_center_minimap_offset(t_mlx *mlx, float *escaled_zoom);

/*
	- Renderiza el minimapa en 2D recorriendo cada píxel de la ventana del minimapa.
	- Dibuja cada píxel según si corresponde a una pared, suelo o la posición del jugador.
	- Si la opción de mostrar rayos está activada, dibuja los rayos en el minimapa.
	- Escalamos los pixeles de la ventana a posisocnes del mapa usando mm_scale A->B
	- NO renderizamos el minimpaa en el recorrido de los pixeles de raycasting porque
	  seria un desperdicio de recursos, lo hacemos despues de renderizar toda la escena
	  en 3D. Ya que en ambos casos habria que sobrescribir el buffer de la imagen.
	  Es mas modular aunque la desventaja es que se recorre dos veces la matriz de pixeles
	  de la zona de la ventana del minmapa.
*/
int	render_frame2D(t_mlx *mlx)
{
	int		win[2];
	float	scaled_zoom[2];
	
	//esto solo en modo seguiemiento jugador va a ser un puntero a funcion cunado cambie se pondra
	//tambienn el minimap scale diferente
	// update_minimap_dinamic_offset(mlx);
	update_center_minimap_offset(mlx, scaled_zoom);
	win[Y] = 0;
	while (win[Y] <= mlx->frame->mm_height)
	{
		win[X] = 0;
		buffering_line(win[Y], 0xFFFFFFFF, mlx, mlx->frame->mm_widht);
		while (win[X] <= mlx->frame->mm_widht)
		{
			draw_mini_pixel_offset(mlx, win, scaled_zoom);
			win[X]++;
		}
		win[Y]++;
	}
	if (mlx->frame->minimap_showrays == true)
		draw_rays2D(mlx);
	return (1);
}

void	update_center_minimap_offset(t_mlx *mlx, float *escaled_zoom)
{
	t_frame		*f;
	float	pl_pos[2];
	float	zoom;

	f = mlx->frame;
	pl_pos[X] = mlx->player->pos_x;
	pl_pos[Y] = mlx->player->pos_y;
	zoom = mlx->frame->mm_zoom_factor;
	escaled_zoom[X] = f->mm_scale[X] * zoom;
	escaled_zoom[Y] = f->mm_scale[Y] * zoom;
	f->mm_offset[X] = pl_pos[X] - (f->mm_widht / 2) / (f->mm_scale[X] * zoom);
	f->mm_offset[Y] = pl_pos[Y] - (f->mm_height / 2) / (f->mm_scale[Y] * zoom);
	
}


/*
	- Dibuja un píxel del minimapa en función de su correspondencia con el mapa.
	- Los valores del mapa en float para permitir un movimiento fluido del jugador 
		(mov continuo) si quremos que sea celda a celda tiene que ser con ints.
	- Calculamos las traslacion del los puntos del minimapa respecto a la posicion
	  del jugador, para eso restamos la posicon delorigen (cventro del minimapa) a
	  la posicion del jugador
	- Despues escalamos los puntos de la ventana a las posiciones del mapa con mm_scale
	- y apicamos el factor de zoom del minimapa
	- Si la posición escalada  y trasladadas corresponde a una pared, dibuja un píxel naranja.
	- Si es suelo, dibuja un pixel negro/gris.
*/
void	draw_mini_pixel_offset(t_mlx *mlx, int *win, float *scaled_zoom)
{
	t_frame		*f;
	float		map[2];
	
	f = mlx->frame;
	map[X] = f->mm_offset[X] + (float)win[X] / (scaled_zoom[X]);
	map[Y] = f->mm_offset[Y] + (float)win[Y] / (scaled_zoom[Y]);
	if ((unsigned int)map[Y] < mlx->map->max_rows &&
			(unsigned int)map[X] < mlx->map->max_columns)
	{
		if (is_wall(mlx, map) == true)
			buffering_pixel(win[X], win[Y], mlx, 0xFF8C00);
		else
			buffering_pixel(win[X], win[Y], mlx, 0x969696);
		is_person2D(mlx, win, map);
	}
}


/*
	Con esta funcion comprobamos si una posicion del mapa es una pared o no
	para pintarla en el minimapa.
	Se puede sustituir por tpuch_wall pero asi es mas modular
	Pasamos las posicion del pixel a int para saber si corresponde a una 
	pared dentro del conjusnto de posiciones(i,j) del mapa (discretas)
*/
bool is_wall(t_mlx *mlx, float *map)
{
	unsigned int map_x;
	unsigned int map_y;
	
	map_x = (unsigned int)map[X];
	map_y = (unsigned int)map[Y];
	if (mlx->map->map_grids[map_y][map_x] == WALL)
		return (true);
	return (false);
}

/*
	Con esta funcion comprobamso si el personaje esta en la region del mapa despues
	de haberlo escalado teneindo en cuenta el volumen del mapa. La usamos para hacer
	ls comporbacion en cada par de pixeles del minimapa.
	Se hace la comprobacion en float para tener en cuenta el volumen (epsilon) del personaje
	y que el personaje pueda estar en varias posiciones dentro de una celda del mapa. Si se
	comparase con ints el moviento del persona no seria ocntinuo
	Se comprueba en cada combinacion de punetos x,y de los pixeles escalados al minimapa (es menos
	eficiente que hacer un draw person2D que dibujaria elpersonaje despues de renderizar
	el minimaapa en la siguiente capa de renerizado)
*/
void	is_person2D(t_mlx *mlx, int *window, float *map)
{
	if (fabs(mlx->player->pos_x - map[X]) < mlx->player->volume &&
			fabs(mlx->player->pos_y - map[Y]) < mlx->player->volume)
	{
		buffering_pixel(window[X], window[Y], mlx, 0x000000);
	}
}

/*
	Esta funcion se usa en el caso de que queramos hacer de la matriz de pixeles 
	del mapa, poder saber si los pixeles son parte de la zona del minimapay aprovechar
	ese recorrido para bufferizar esos pixeles de la parte del minimapa.
	- Comprobar si el píxel está dentro de los límites del minimapa
	
*/
bool is_minimapzone(int win_x, int win_y, t_mlx *mlx)
{
	int minimap_start_x = 0;
	int minimap_start_y = 0;

	if (win_x >= minimap_start_x && win_x <= mlx->frame->mm_widht &&
		win_y >= minimap_start_y && win_y <= mlx->frame->mm_height)
			return (true);
	return (false);
}

/*
	- Dibuja un píxel del minimapa en función de su correspondencia con el mapa.
	- Los valores del mapa en float para permitir un movimiento fluido del jugador 
		(mov continuo) si quremos que sea celda a celda tiene que ser con ints.
	- Escala las coordenadas de la ventana a las del mapa usando mm_scale.
	- Si la posición escalada corresponde a una pared, dibuja un píxel naranja.
	- Si es suelo, dibuja un pixel negro/gris.
*/
void	draw_mini_pixel(t_mlx *mlx, int *win)
{
	float	map[2];

	map[X] = (float)win[X] / mlx->frame->mm_scale[X];
	map[Y] = (float)win[Y] / mlx->frame->mm_scale[Y];
	if ((unsigned int)map[Y] < mlx->map->max_rows &&
			(unsigned int)map[X] < mlx->map->max_columns)
	{
		if (is_wall(mlx, map) == true)
			buffering_pixel(win[X], win[Y], mlx, 0xFF8C00);
		else
			buffering_pixel(win[X], win[Y], mlx, 0x969696);
		is_person2D(mlx, win, map);
	}
}

void	update_minimap_dinamic_offset(t_mlx *mlx)
{
	static float offset[2] = {0, 0}; // offset persistente
	float margin_x = 1.0f;          // margen horizontal en unidades de mapa
	float margin_y = 1.0f;          // margen vertical en unidades de mapa

	// Posición del jugador
	float px = mlx->player->pos_x;
	float py = mlx->player->pos_y;

	// Dimensiones del minimapa en píxeles
	int mini_width  = mlx->frame->mm_widht;
	int mini_height = mlx->frame->mm_height;

	// Posición central actual del minimapa
	float center_x = offset[X] + mini_width / (2 * mlx->frame->mm_zoom_factor * mlx->frame->mm_scale[X]);
	float center_y = offset[Y] + mini_height / (2 * mlx->frame->mm_zoom_factor * mlx->frame->mm_scale[Y]);

	// Ajustamos offset solo si el jugador sale del margen
	if (fabs(px - center_x) > margin_x)
	{
		if (px > center_x)
			offset[X] += fabs(px - center_x) - margin_x;
		else
			offset[X] -= fabs(px - center_x) - margin_x;
	}

	if (fabs(py - center_y) > margin_y)
	{
		if (py > center_y)
			offset[Y] += fabs(py - center_y) - margin_y;
		else
			offset[Y] -= fabs(py - center_y) - margin_y;
	}

	mlx->frame->mm_offset[X] = offset[X];
	mlx->frame->mm_offset[Y] = offset[Y];
}

/*
	Esta funcion sirve para no tener que comprobar en cada par de pixeles de la 
	matriz de la pantalla si es eso pixeles corresponden al la posisicon del person
	naje + su volumen (epsilon). Nos permite modularizar el codigo y baja r al complejidad
*/
// void draw_person2D(t_mlx *mlx)
// {
// 	int player_x, player_y;
// 	int start_x, start_y;
// 	int end_x, end_y;
// 	int x, y;

// 	// Calcular la posición del jugador en el minimapa
// 	player_x = mlx->player->pos_x * (WIDTH / MINI_WIDTH) / mlx->map->max_columns;
// 	player_y = mlx->player->pos_y * (HEIGHT / MINI_HEIGHT) / mlx->map->max_rows;

// 	// Definir el área del jugador (un cuadrado alrededor de su posición)
// 	start_x = player_x - EPSILON * (WIDTH / MINI_WIDTH);
// 	start_y = player_y - EPSILON * (HEIGHT / MINI_HEIGHT);
// 	end_x = player_x + EPSILON * (WIDTH / MINI_WIDTH);
// 	end_y = player_y + EPSILON * (HEIGHT / MINI_HEIGHT);

// 	// Pintar el área del jugador
// 	y = start_y;
// 	while (y <= end_y)
// 	{
// 		x = start_x;
// 		while (x <= end_x)
// 		{
// 			if (x >= 0 && x < WIDTH / MINI_WIDTH && y >= 0 && y < HEIGHT / MINI_HEIGHT)
// 				buffering_pixel(x, y, mlx, 0x0000FFFF); // Color del jugador
// 			x++;
// 		}
// 		y++;
// 	}
// }



/////////////////////////////FUNCIONES DE REDERIZADO DE B->A//////////////////////////////////////////

// void render_cell2D(t_mlx *mlx, unsigned int map_x, unsigned int map_y, int *scale)
// {
// 	int	window_x;
// 	int	window_y;
// 	int	i;
	
// 	i = 0;
// 	while (i < scale[0]) // Iterar dentro de la celda en x
// 	{
// 		int j = 0;
// 		while (j < scale[1]) // Iterar dentro de la celda en y
// 		{
// 			window_x = (map_x * scale[0]) + i; // Coordenada X en la ventana
// 			window_y = (map_y * scale[1]) + j; // Coordenada Y en la ventana //a1
// 			if (mlx->map->map_grids[map_y][map_x] == WALL && (i == scale[0] - 1 || i == 0))
// 				buffering_pixel(window_x, window_y, mlx, 0x0000FF00); // Color para paredes birdes horizontales
// 			else if (mlx->map->map_grids[map_y][map_x] == WALL && (j == scale[1] - 1 || j == 0))
// 				buffering_pixel(window_x, window_y, mlx, 0x0000FF00); // Color para paredes bordes verticales
// 			else if (mlx->map->map_grids[map_y][map_x] == WALL)
// 				buffering_pixel(window_x, window_y, mlx, 0x00FF0000); // Color para paredes
// 			else
// 				buffering_pixel(window_x, window_y, mlx, 0x00000000); // Color para el suelo
// 			// Dibujar al jugador si está en esta posición (como es un booleano se trcunca y se queda con la parte entera->funciona)
// 			float epsilon = 0.4;// Margen de error para la comparación
// 			if (fabs(mlx->player->pos_x - map_x) < epsilon &&
// 				fabs(mlx->player->pos_y - map_y) < epsilon)
// 			{
// 				buffering_pixel(window_x, window_y, mlx, 0x0000FFFF); // Color para el jugador
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// //renderizado de conjunto pares del mapa (puntos x, y) A -> a conjunto de puntos (pares x, y) de la ventana
// void render_frame2DD(t_mlx *mlx, int minimap_sizex, int minimap_sizey)
// {
// 	unsigned int	map_x;
// 	unsigned int	map_y;
// 	int				scale[2];
	
// 	scale[0] = (WIDTH / minimap_sizex) / mlx->map->max_columns;
// 	scale[1] = (HEIGHT / minimap_sizey) / mlx->map->max_rows;
// 	map_x = 0;
// 	while (map_x < mlx->map->max_columns)
// 	{
// 		map_y = 0;
// 		while (map_y < mlx->map->max_rows)
// 		{
// 			render_cell2D(mlx, map_x, map_y, scale);
// 			map_y++;
// 		}
// 		map_x++;
// 	}
// 	mlx_put_image_to_window(mlx->mlx_var, mlx->mlx_window, mlx->mlx_img, 0, 0);
// }