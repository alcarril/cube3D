/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:30:42 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/08 14:33:18 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

/*
	Calculo del movimiento del jugador en cada eje del plano. Descomponemos el 
	moviento y lo bufferizamos dentro del array diferencial. Para ellos usamos 
	los principios de trigonometria de la circunferencia gonimetrica, vectorizacion y el
	diferencial de un punto en un espacio euclideo. Segun el angulo de rotacion 
	del jugador respeto a los ejes del plano y la direcion relativa en la que queramos
	movernos el difrecial se calcula de un maera u otra
	- Cosas a tener en cuenta:
		- En la ventana el NORTE (90 grados) y el SUR (270) estan invertidos.
		- Hay un vectorixacion diferente para cada uno de los movientos dentro
		de la circunferencia (cada uno de los cuadrantes del plano)
		- En ver de sumar 90 grados para los movimientos laterales se podria usar
		la relacion de signos de la matriz de rotacion
		
*/
void	vectorization(t_mlx *mlx, t_player *player, float *diferencial)
{
	float	angle_rad;

	angle_rad = mlx->player->rad_angle;
	if (mlx->player->move_up)
	{
		diferencial[X] += cos(angle_rad) * player->speed;
		diferencial[Y] -= sin(angle_rad) * player->speed;
	}
	if (mlx->player->move_down)
	{
		diferencial[X] -= cos(angle_rad) * player->speed;
		diferencial[Y] += sin(angle_rad) * player->speed;
	}
	if (mlx->player->move_left)
	{
		diferencial[X] += cos(angle_rad + (PI / 2)) * player->speed;
		diferencial[Y] += sin(angle_rad - (PI / 2)) * player->speed;
	}
	if (mlx->player->move_right)
	{
		diferencial[X] += cos(angle_rad - (PI / 2)) * player->speed;
		diferencial[Y] += sin(angle_rad + (PI / 2)) * player->speed;
	}
}

/*
	Con esta funcion rotamos la direccion hacia la que mira el jugador. Dado que los
	ejes estan invertidos en la ventana tenemos que hacer un ajuste para que cuando
	rote en sentido horario el angulo disminuya y cuando rote en sentido antiohorario
	sea alreves. Ademas se ajustan los limites de los angulos para que nunca sean mayores
	de 360 grados o menos aunque a la hora de hacer los calculos de los senos y los cosenos
	esto no sea relevante porque no acambian pero evitamos que el float llegue a los limites y 
	se haga overflow.
*/
void	rotate_player(t_mlx *mlx, float delta_grados)
{
	if (mlx->player->r_clockwise == true)
		mlx->player->angle -= delta_grados;
	else if (mlx->player->r_counterclockwise == true)
		mlx->player->angle += delta_grados;
	if (mlx->player->angle >= 360.0f)
		mlx->player->angle -= 360.0f;
	else if (mlx->player->angle < 0.0f)
		mlx->player->angle += 360.0f;
	mlx->player->rad_angle = mlx->player->angle * (PI / 180.0f);
}

/*
	Función uxiliar para verificar colisiones en un área alrededor del jugador
	cada un de las comporbaciones de WALL es para cada uno de las 4 direcciones de 
	moviemintos y se combina con epsilon para que el jugador no entre dentro de las 
	paredes en el minimapa (epsilon seria el volumen del jugador)
*/
bool	is_collision(float x, float y, t_mlx *mlx, float e)
{
	int mx = (int)x;
	int my = (int)y;

	if (mx < 0 || my < 0 || mx >= (int)mlx->map->max_columns || my >= (int)mlx->map->max_rows)
		return (true);

	return (
		mlx->map->map_grids[(int)(y + e)][(int)(x + e)] == WALL ||
		mlx->map->map_grids[(int)(y - e)][(int)(x + e)] == WALL ||
		mlx->map->map_grids[(int)(y + e)][(int)(x - e)] == WALL ||
		mlx->map->map_grids[(int)(y - e)][(int)(x - e)] == WALL
	);
}

/*
	Con esta funcion actualizamos la posiscion del juahador dentro del plano
	segun el vector de movimitento en el que se mueva. Antes de moverlo calculamos
	la nueva posicion en cada eje (movimeinto descompuesto) asi podemos calcular si hay
	colision en cada uno de los vectores que componen el moviento en la direccion hacia
	donde se mueve y en ela caso de encontrar una parade que no se quede bloqueado. Adenas
	metemos un coeficionete de friccion que disminuye la velocidad de moviento en el eje que
	quede libre para simular la fuerzxa de rozamiento que diminuiriza la velocidad.
*/
void	move_player(t_mlx *mlx)
{
	t_player	*player;
	float		new_pos[2];
	float		diferencial[2];
	bool		colision[2];
	
	player = mlx->player;
	rotate_player(mlx, 1.1f);
	vectorization(mlx, player, diferencial);
	new_pos[X] = player->pos_x + diferencial[X];
	new_pos[Y] = player->pos_y + diferencial[Y];
	colision[X] = is_collision(new_pos[X], player->pos_y, mlx, player->volume);
	colision[Y] = is_collision(player->pos_x, new_pos[Y], mlx, player->volume);
	if (!colision[X] && !colision[Y])
	{
		player->pos_x = new_pos[X];
		player->pos_y = new_pos[Y];
	}
	else
	{
		if (!colision[X])
			player->pos_x += diferencial[X] * FRICTION;
		if (!colision[Y])
			player->pos_y += diferencial[Y] * FRICTION;
	}
}

//esta va a tener que salir de aqui
int mouse_move(int x, int y, t_mlx *mlx)
{
	(void)mlx;
	static int prev_x;
	// static int prev_y;
	static int control;
	float grados_por_pixel_x;
	float ret;

	
	if (control == 0)
	{
		prev_x = WIDTH / 2;
		// prev_y = y;
		control = 1;
	}
	printf("Mouse en: (%d, %d)\n", x, y);

	int delta_pixels_x = x - prev_x;
	// int delta_pixels_y = y - prev_y;
	grados_por_pixel_x = 0.01f;
	ret = delta_pixels_x / grados_por_pixel_x;
	mlx->player->angle -= ret;
	prev_x = WIDTH / 2;

	if (mlx->player->angle >= 360.0f)
		mlx->player->angle -= 360.0f;
	else if (mlx->player->angle < 0.0f)
		mlx->player->angle += 360.0f;
	
	// // Guardar las coordenadas del mouse en la estructura mlx
	// // Depuración: Imprimir las coordenadas del mouse
	// printf("Mouse en: (%d, %d)\n", x, y);

	// // Puedes usar las coordenadas para realizar acciones, como rotar la cámara
	return (0);
}