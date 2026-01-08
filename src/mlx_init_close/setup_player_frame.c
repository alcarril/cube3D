/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_player_frame.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:42:33 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/08 14:30:39 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

/*
	Inicializar los datos del jugador: 
	- Inicializamos la posicion iniclial del jugador (parser val)
	- La orientacion inicla del jugador (parser val)
	- La velocidad de moviento (multiplicador del diferencial de cada componenete de los vectore de moviento)
	- El campo de vision del jugador (fov)
	- El volumen del jugador (radio de colision)
	- Los booleanos para los movientos, rotaciones y sprint del jugador
	Esta funcion va a tener que tener mas argumentos uno para la posicion iniclal metida en 
	un array de dos valores y otro mas para la orien
	tacion inicial del jugador (N,S,E,W).-> estos dato se obtienen en el parser.
	Iniiclaizamos los datos de los booleanos del moviento del jugador, el multiplicadpr para
	calculñar los diferenciales de los movientos
*/
void setup_player(t_mlx *mlx)
{
	int	middle[2];//esto se va a borrar
	
	middle[X] = mlx->map->max_columns / 2; //esto se va a borrar
	middle[Y] = mlx->map->max_rows / 2; //esto se va a borrar
	
	init_player_orientation_pos(mlx->player, 'N', middle);
	mlx->player->speed = 0.033f;
	mlx->player->fov = 60.0f;
	mlx->player->rad_fov = 60.0f * (PI / 180.0f);
	mlx->player->volume = EPSILON;
	mlx->player->move_down = false;
	mlx->player->move_up = false;
	mlx->player->move_right = false;
	mlx->player->move_left = false;
	mlx->player->r_clockwise = false;
	mlx->player->r_counterclockwise = false;
	mlx->player->sprint = false;
}

/*
	Inicializar los datos del jugador:
	- Inicializamos el angulo del jugador en funcion de la cardinalidad
	- Inicializamos la posicion del jugador en funcion de la posicion del mapa
*/
void	init_player_orientation_pos(t_player *pl, char cardinal, int pos[2])
{
	if (cardinal == 'N')
		pl->angle = 90.0f;
	if (cardinal == 'S')
		pl->angle = 270.0f;
	if (cardinal == 'E')
		pl->angle = 0.0f;
	if (cardinal == 'W')
		pl->angle = 180.0f;
	pl->rad_angle = pl->angle * (PI / 180.0f);
	pl->pos_x = (float)pos[X] + 0.5f;
	pl->pos_y = (float)pos[Y] + 0.5f;
}

/*
	Inicializar los datos del frame:
	- Inicializamos el minimapa como apagado
	- Inicializamos la opcion de mostrar los rayos en el minimapa como apagado
	- Inicializamos el procentaje del ancho y largo de la ventana que se usa para el minimapa
	- Inicializamos la escala del minimapa en funcion del procentaje del ancho y largo de la ventana
	  y del numero de filas y columnas del mapa original
	- Inicializamos el efecto fish eye como apagado
	- Inicializamos el efecto euclidean como apagado
*/
void	init_frame_data( t_mlx *mlx)
{
	mlx->frame->minimap_onoff = false;
	mlx->frame->minimap_showrays = false;
	mlx->frame->mm_height= mlx->win_height / MINI_HEIGHT;
	mlx->frame->mm_widht = mlx->win_width / MINI_WIDTH;
	mlx->frame->raycasting_onoff = true;
	mlx->frame->fish_eye = false;
	mlx->frame->euclidean = false;
	get_minimapscale(mlx, mlx->frame->mm_scale);
}

/*
	Esta funcion sirve para poder sacar la escala del minimapa en funcion de:
	- El numero de filas y columnas del mapa original
	- El procentaje del ancho y largo de la ventana que se usa para el minimapa
*/
void	get_minimapscale(t_mlx *mlx, float *scale)
{
	scale[X] = (float)(mlx->frame->mm_widht) / mlx->map->max_columns;
	scale[Y] = (float)(mlx->frame->mm_height) / mlx->map->max_rows;
}