/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:31:15 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/04 12:42:58 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

bool	is_collision(float x, float y, t_mlx *mlx, float e);
void	rotate_player(t_mlx *mlx);
void	vectorization(t_mlx *mlx, t_player *player, float *diferencial);
void	move_player(t_mlx *mlx);

int	close_handler(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_var,
		mlx->mlx_img);
	mlx_destroy_window(mlx->mlx_var,
		mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_var);
	free(mlx->mlx_var);
	exit(0);
}

int	key_press(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
	{
		close_handler(mlx);
		return (0);
	}
	if (keysym == XK_w)
		mlx->player->move_up = true;
	if (keysym == XK_s)
		mlx->player->move_down = true;
	if (keysym == XK_a)
		mlx->player->move_left = true;
	if (keysym == XK_d)
		mlx->player->move_right = true;
	if (keysym == XK_Left)
		mlx->player->r_counterclockwise = true;
	if (keysym == XK_Right)
		mlx->player->r_clockwise = true;
	return (0);
}

int	key_release(int keysym, t_mlx *mlx)
{
	if (keysym == XK_w)
		mlx->player->move_up = false;
	if (keysym == XK_s)
		mlx->player->move_down = false;
	if (keysym == XK_a)
		mlx->player->move_left = false;
	if (keysym == XK_d)
		mlx->player->move_right = false;
	if (keysym == XK_Left)
		mlx->player->r_counterclockwise = false;
	if (keysym == XK_Right)
		mlx->player->r_clockwise = false;
	return (0);
}



// Función uxiliar para verificar colisiones en un área alrededor del jugador
//cada un de las comporbaciones de WALL es para cada uno de las 4 direcciones de 
//moviemintos
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


//caso de moverse en x
//caso de moverse en y
//caso de dar con pared hacia donde se mueve o se queda quieto-> calculo diferencial y suavizadp
void	move_player(t_mlx *mlx)
{
	float	new_pos[2];
	float	diferencial[2];
	bool	colision[2];

	rotate_player(mlx);
	vectorization(mlx, mlx->player, diferencial);
	new_pos[X] = mlx->player->pos_x + diferencial[X];
	new_pos[Y] = mlx->player->pos_y + diferencial[Y];
	colision[X] = is_collision(new_pos[X], mlx->player->pos_y, mlx, EPSILON);
	colision[Y] = is_collision(mlx->player->pos_x, new_pos[Y], mlx, EPSILON);
	if (!colision[X] && !colision[Y])
	{
		mlx->player->pos_x = new_pos[X];
		mlx->player->pos_y = new_pos[Y];
	}
	else
	{
		// Deslizar con suavizado
		if (!colision[X])
			mlx->player->pos_x += diferencial[X] * FRICTION;
		if (!colision[Y])
			mlx->player->pos_y += diferencial[Y] * FRICTION;
	}
}

void	vectorization(t_mlx *mlx, t_player *player, float *diferencial)
{
	float	angle_rad;
	
	angle_rad = mlx->player->angle * (PI / 180);
	if (mlx->player->move_up)
	{
		diferencial[X] += player->speed * cos(angle_rad);
		diferencial[Y] -= player->speed * sin(angle_rad);
	}
	if (mlx->player->move_down)
	{
		diferencial[X] -= player->speed * cos(angle_rad);
		diferencial[Y] += player->speed * sin(angle_rad);
	}
	if (mlx->player->move_left)
	{
		diferencial[X] += player->speed * cos(angle_rad + (PI / 2));
		diferencial[Y] += player->speed * sin(angle_rad - (PI / 2));
	}
	if (mlx->player->move_right)
	{
		diferencial[X] += player->speed * cos(angle_rad - (PI / 2));
		diferencial[Y] += player->speed * sin(angle_rad + (PI / 2));
	}
}





//rotar en sentido del reloj
//rotar en sentido antihoraio
//controlar los grados y los radianes
//controlar los maximos y minimos 
void	rotate_player(t_mlx *mlx)
{
	//el clockwise depende de donde este el norte y el sur del mapa segun si rotamos el ejeo no lo rotamos
	if (mlx->player->r_clockwise == true)
		mlx->player->angle -= 1.1f;//5 grados es mucho 
	else if (mlx->player->r_counterclockwise == true)
		mlx->player->angle += 1.1f;//5 grados es mucho
	//el ajuste de lso grados se hace despues de hacer el cambio de grados
	if (mlx->player->angle >= 360.0f)
		mlx->player->angle -= 360.0f;
	else if (mlx->player->angle < 0.0f)
		mlx->player->angle += 360.0f;
	return ;
}

//Documentar porque los angulos cambian y como cambia 
//Ducomentar