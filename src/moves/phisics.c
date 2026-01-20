/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phisics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:57:44 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/20 08:36:08 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

// void	jump(t_mlx *mlx)
// {
	
// }

/*
	Estta funcoin acelera al jugador de manera cunado no esta en el aire.
	Con esta funcion calculamos la derivada de la velocidad del jugador haciendo que cuando
	se mueva el jugador dentro de un eje se acelere poco a poco, y cundo de je de moverse
	se desacelere poco a poco simulando una inercia:
	 - Parametros amtematicos y fisicos:
	  Aceleracion (constane) = delta_speed / delta_time (derivada de la velocidad).
	  Delta_time = tiempo trnascuttido entre fram y frame (en ms).
	  Delta_speed = incremento de velocidad por frame (constante ajustable).
	  air_friction = coeficiente de friccion del aire que hace que el jugador se desacelere
	  Velocidad:  La usamos para poder saber el valor de speed que es la variable que 
	  se va usar para calcular el diferencial de la posicion del jugador 
	  en caja eje (x, y) del mapa y asi moverlo segun una trayectoriade manera "continua"
	 - Alternativas de calcuclo de velocidad:
	  A la hora de calcular la velocidad del jugador tenemos varias alternativas:
	   - Velocidad instantanea: La velocidad del jugador cambia de manera instantanea
	   segun se presionen las teclas de moviento. Esto hace que el jugador se mueva
	   de manera brusca y poco realista.
	   - Velocidad con aceleracion y desaceleracion: La velocidad del jugador cambia
	   de manera gradual segun se presionen las teclas de moviento. Esto hace que el
	   jugador se mueva de manera mas suave y realista.
	   - Velocidad con inercia: La velocidad del jugador cambia de manera gradual segun
	   se presionen las teclas de moviento, pero ademas cuando se deja de presionar
	   una tecla el jugador sigue moviendose un poco mas antes de detenerse por completo.
	   Esto simula la inercia del movimiento y hace que el jugador se mueva de manera
	   mas realista.
	 - Alternativas de calculo del diferencial de la velocidad en el vector de movimientos
	 segun la variable delta que multiplica a la aceleracion (delta)
	  - Delta fijo: Usar un valor fijo para delta (por ejemplo 0.1f) hace que la aceleracion
	  sea constante y predecible. Esto es facil de implementar pero puede no ser realista
	  en situaciones donde el tiempo entre frames varía mucho. Esto es la implmetacio mas sencilla
	  hace que el jugadoir se mueva de manera continua , pero tiene dos porblemas. Cunado el frame rate
	  bajja el moviento del jugador se relentiza y cunado el frame rate sube el moviento del jugador se acelera
	  demasiado. Lo bueno que es que n caso de lags el jugador no se teleporta a otra posicion.
	   Uso típico: motores clásicos, demos, retro FPS. (cunado el softare del juego iba controlaba el nivel de fps)
	  - Delta basado en delta_time: Usar delta_time para calcular delta hace que la aceleracion
	  sea proporcional al tiempo transcurrido entre frames. Esto es mas realista pero puede
	  ser mas complejo de implementar. Esto tiene el problema de que cunado hay lags el jugador se teleporta
	  a otra posicion. Como ventaja se sonsigue un moviento determinista del jugador independientemente del frame rate.
	  Esto es util cunado se quiere tener un control preciso sobre el moviento del para que sea mas 
	  predecible. Otra desventaj es que cuando el frame rate baja tambien se pueden porducir pequeños saltos en el moviento del jugador.
	  Esto se puede clipearr limitando el valor maximo de delta_time para evitar saltos grandes en el moviento.
	  Los calculos del timestamp ya se estaba unsado para el contador de fps por lo que los reutilizamos aqui.
	 Uso típico: motores modernos, juegos con FPS variable, físicas “jugables” más puristas. (es util para que un juego pueda correrse en diferentes sistemas con diferentes capacidades de hardware
	  y mantener una experiencia de juego consistente).
	  - Delta basado en en el tiempo con substeps: Esta es una variacion del delta basado en delta_time donde se divide el tiempo transcurrido
	  entre frames en substeps mas pequeños para mejorar la precision del calculo de la aceleracion. 
	  Uso típico: motores profesionales, Unity, Unreal, Source, Doom 3.
	  Conclusion: No usamo un delta basado en fps porque ees menos predecible y porque lmitar la tasasde fps de 
	  nuestra juego tiene sentido por cuidar los ciclos de cpu pero queremos que el motor se alo mas optimo posible
	  segun lo que lo pueda ejecutar exprimir el hardware del usuario. Demas no tenemos la posibilidad de usar uslee
	  para hacer que el tiempo que el motor este renderizando a un tasa mayor de fps de que queremaso limitar en suc ota 
	  superior por lo que solo podriamos hacer un bucle infiniy esperar a que el tiempo transcurrido entre frames sea mayor al limite
	  lo que consumiria recursos de meeria igualemnte. Por eso tenemos que usar la opcion 2 o 3. Metemos la 3 que es la mas precisa.
	  

	  //meterle el headboobing
*/

/*
	La aceleracion se calcula en el inicion del juego como un factor sobre la friccion
	Simpre mayor que que un oapra que se mayor que la friccion. Ademas se mete un parametro 
	k (0,1) que es la traacion, normalemte es el porcenate de la fricion que calcelamos cunado
	el suelo se esta moviendo. Este factor realista a anivel fisco porque simula la fuerza de agarre
	que tiene el calzado o la rueda si fuese un coche con el suelo sobre el que aplica la aceleracion
	Si la fuerza de aggare es mo¡pca por mucha aceleracio (potencia) que tenga no las appica bien y la
	frccion con el medio (suelo fuerza contraria) hace qu eno avance tan rapido es decir pierde aceleracion 
	efectiva.
	Desde elpunto de vista practino no s sirve para poder cancelar la friccion y que no nos ocurra el probelamd eantes 
	con la calcelacion de aceleracion con la fuerza de frccicion y bloqeuso con la fuerza minima
	Subiendo la aceleracion se haceq que arranque mas rapido
	La ocmbiancion de los valores de aceleracionm traccion y friccion hace que podamos conseguir distinitos efectos 
	de moviento simulano sistinito tipos de suelo.
*/
void	acelerate_player(t_mlx *mlx, unsigned int vec_index, long long dt, bool *is_moving)
{
	float	accel;
	float	speed;
	float	max_speed;
	float	traction;

	speed = mlx->player->speed_dt;
	max_speed = mlx->player->max_speed_dt;	
	traction = mlx->phisics.floor_friction * mlx->player->traccion_k; // 0–1 según suelo mejor entre 0.5 y 1
	accel = mlx->player->aceleration[vec_index] * traction;
	speed += accel * (float)dt;
	if (speed > max_speed)
	{
		speed = max_speed;
		printf("Max speed reached: %f m/s\n", max_speed);
	}
	mlx->player->speed_dt = speed;
	*is_moving = 1;
}

/*
	Sea plica la fuerza contraria al moviento que es la fuerza que frena al jugador simulndo la fisicas de un
	entrono realista. Esta fuerza de friccion seria la fuerza que frena al jugador. Cunado se frena el jugador para
	Controlar el tema de la dicion exponenecial del la velociadad por un factor menor que uno se usa:
	Para el frenado cunad on ose esta moviendo no basta con la calcelacion 
	que hace la traccion asi que hay que meterle un multiplicado si no queremos
	que este haciend ocalculos muy grandes a la friccion y asi no tocar la friccion 
	de base para las configuraciones. Es decir no hacer lo contrario que es meter un divisior
	cuando se esta moviendo y pone run friccion mas alta porque de la maner auq el o tengo ya fuciona
	esto es estilo doom/quake
	Otra poccion es mete run afuersxa de frernado del jugador que disminuya la speed despues de 
	aplicarle la friccion pero no es lo mas realista a nivel de fiscas del mapa auqnuq ei que es muy manipublae
	esto es el estilo doom/quake
	Ademas metemos el spano to zero que no es fisica tal cual pero es puero estilo gameplay para poder
	controlar el tema de las matematicas de la divisiones ( se ua mucho en shooters) se rompe la fisica a porpo
	sitop
*/
void	decelerate_player(t_mlx *mlx, long long dt, bool is_moving)
{
	float	speed;
	float	friction;

	speed = mlx->player->speed_dt;
	if (speed <= 0.0f)
		return;
	friction = mlx->phisics.floor_friction;
	if (is_moving == false)
		friction *= 10;
	speed -= speed * friction * (float)dt;
	if (speed < SPEEDMIN_MS)
		speed = 0.0f;
	mlx->player->speed_dt = speed;
}


void	acelerate_dukedoom(t_mlx *mlx, unsigned int vec_index, long long dt, bool *is_moving)
{
	float 		aceleration;
	float 		speed[2];
	float		max_speed[2];
	float		traccion;
	float		total_speed;

	speed[X] = mlx->player->speed_a[X];
	speed[Y] = mlx->player->speed_a[Y];
	max_speed[X] = mlx->player->max_speed_a[X];
	max_speed[Y] = mlx->player->max_speed_a[Y];
	traccion = mlx->phisics.floor_friction * mlx->player->traccion_k;
	aceleration = mlx->player->aceleration[vec_index] * traccion;
	if(speed[X] < max_speed[X])
		speed[X] += dt * aceleration;
	if (speed[Y] < max_speed[Y])
		speed[Y] += dt * aceleration;
	if(speed[X] >= max_speed[X])
		speed[X] = max_speed[X];
	if (speed[Y] >= max_speed[Y])
		speed[Y] = max_speed[Y];
	total_speed = sqrtf((speed[X] * speed[X]) + (speed[Y] * speed[Y]));
	if (total_speed > mlx->player->max_speed_a[X])
	{
		speed[X] *= max_speed[X] / total_speed;
		speed[Y] *= max_speed[X] / total_speed;
	}
	mlx->player->speed_a[X] = speed[X];
	mlx->player->speed_a[Y] = speed[Y];
	*is_moving = 1;
}

void	decelerate_dukedoom(t_mlx *mlx, long long dt, bool is_moving)
{
	float 		speed[2];
	float 		friction;

	speed[X] = mlx->player->speed_a[X];
	speed[Y] = mlx->player->speed_a[Y];
	friction = mlx->phisics.floor_friction;
	if (is_moving == false)
		friction *= 10;
	if(speed[X] > SPEEDMIN_MS)
		speed[X] -= speed[X] * friction * (float)dt;
	if (speed[X] <= SPEEDMIN_MS)
		speed[X] = 0.0f;
	if (speed[Y] > SPEEDMIN_MS)
		speed[Y] -= speed[Y] * friction * (float)dt;
	if (speed[Y] <= SPEEDMIN_MS)
		speed[Y] = 0.0f;
	mlx->player->speed_a[X] = speed[X];
	mlx->player->speed_a[Y] = speed[Y];
}


//meterle el headboobing
void	speed_and_vectorization(t_mlx *mlx)
{
	t_player	*pl;
	long long	delta_time;

	pl = mlx->player;
	if (mlx->frame->phisics_onoff == ON)//entra
	{
		delta_time = mlx->del_timestamp;
		if (delta_time > MAX_DT_FRAME)
		{
			delta_time = MAX_DT_FRAME;
			// printf("Clipped delta_time to %lld ms to prevent large physics steps.\n", delta_time);
		}
		// printf("Delta time for physics: %lld ms\n", delta_time);
		vectorization_phisics(mlx, delta_time);//entra
	}
	else
	{
		printf("Phisics off, using default vectorization.\n");
		delta_time = 1;
		vectorization(mlx->player, delta_time, pl->speed);
	}
}


void	vectorization_phisics(t_mlx *mlx, long long delta_time)
{
	bool	is_moving;

	is_moving = 0;
	if (mlx->frame->dukedoom_mode == OFF)
	{
		if (mlx->player->keys.move_up == true)
			acelerate_player(mlx, FRONT, delta_time, &is_moving);
		if (mlx->player->keys.move_down == true)
			acelerate_player(mlx, BACK, delta_time, &is_moving);
		if (mlx->player->keys.move_left == true || mlx->player->keys.move_right == true)
			acelerate_player(mlx, SIDES, delta_time, &is_moving);
		decelerate_player(mlx, delta_time, is_moving);
		vectorization(mlx->player, delta_time, mlx->player->speed_dt);
	}
	else
	{
		if (mlx->player->keys.move_up == true)
			acelerate_dukedoom(mlx, FRONT, delta_time, &is_moving);
		if (mlx->player->keys.move_down == true)
			acelerate_dukedoom(mlx, BACK, delta_time, &is_moving);
		if (mlx->player->keys.move_left == true || mlx->player->keys.move_right == true)
			acelerate_dukedoom(mlx, SIDES, delta_time, &is_moving);
		decelerate_dukedoom(mlx, delta_time, is_moving);
		vectorization_dukedoom(mlx->player, delta_time);
	}
}




void	vectorization_dukedoom(t_player *pl, long long dt)
{
	float	angle_rad;
	
	ft_bzero(pl->diff, sizeof(pl->diff));
	angle_rad = pl->rad_angle;
	if (pl->keys.move_up)
	{
		pl->diff[X] += cos(angle_rad) * pl->speed_a[X] * dt;
		pl->diff[Y] -= sin(angle_rad) * pl->speed_a[Y] * dt;
	}
	if (pl->keys.move_down)
	{
		pl->diff[X] -= cos(angle_rad) * pl->speed_a[X] * dt;
		pl->diff[Y] += sin(angle_rad) * pl->speed_a[Y] * dt;
	}
	if (pl->keys.move_left)
	{
		pl->diff[X] += cos(angle_rad + (PI * 0.5f)) * pl->speed_a[X] * dt;
		pl->diff[Y] += sin(angle_rad - (PI * 0.5f)) * pl->speed_a[Y] * dt;
	}
	if (pl->keys.move_right)
	{
		pl->diff[X] += cos(angle_rad - (PI * 0.5f)) * pl->speed_a[X] * dt;
		pl->diff[Y] += sin(angle_rad + (PI * 0.5f)) * pl->speed_a[Y] * dt;
	}
}

//normalizar estilo quake
//velicidad nivel motor fps real

//hasta ahora velocidad y deceleracion co inercia estilo motor real y pero cambios de sentido
//sin inercial estilo juegos arcade clasicos



//FUNCiones de antes estilo coche

// void	acelerate_player(t_mlx *mlx, unsigned int vec_index, long long dt)
// {
// 	float 		aceleration;
// 	float 		speed;
// 	float		max_speed;
// 	// float		min_dt;

// 	aceleration = mlx->player->aceleration[vec_index];
// 	// printf("Aceleracion actual del player: %f\n", aceleration);
// 	// mlx->player->aceleration[FRONT] = 1.00002 * mlx->phisics.floor_friction;
// 	speed = mlx->player->speed_dt;
// 	max_speed = mlx->player->max_speed_dt;
// 	// min_dt = (long long)mlx->player->min_dt[vec_index];
// 	if(speed >= max_speed)
// 	{
// 		printf("Player ya esta a velocidad maxima: %f\n", mlx->player->speed_dt);
// 		return ;
// 	}
// 	if (speed == 0.0f)
// 	{
// 		// speed = SPEEDMIN_MS;
// 		speed = 0.0002f;
// 		printf("Iniciando aceleracion del player: %f\n", speed);
// 	}
// 	else
// 		speed += dt * aceleration;
// 	if(speed >= max_speed)
// 		speed = max_speed;
// 	mlx->player->speed_dt = speed;
// 	mlx->phisics.floor_friction *= 0.4f;
// 	printf("Acelerando player: %f\n", mlx->player->speed_dt);
// }


// void	decelerate_player(t_mlx *mlx, long long dt)
// {
// 	float 		speed;
// 	float 		floor_friction;
// 	float 		fric_aprox;

// 	speed = mlx->player->speed_dt;
// 	if(speed <= 0.0f)
// 		return ;
// 	floor_friction = mlx->phisics.floor_friction;
// 	fric_aprox = 1- (floor_friction * (float)dt);//
// 	if (fric_aprox < 0.0f)//
// 		fric_aprox = 0.0f;
// 	if (speed < SPEEDMIN_MS)
// 	{
// 		speed = 0.0f;
// 		printf("Player ya esta detenido: %f\n", mlx->player->speed_dt);
// 	}
// 	speed *=  fric_aprox;
// 	mlx->player->speed_dt = speed;
// 	// printf("Desacelerando player: %f\n", mlx->player->speed_dt);
// }