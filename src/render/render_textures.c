/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:44:58 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/21 20:56:11 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

/*
	Selecciona la textura adecuada en función de la dirección del rayo
	y del lado de la pared que fue golpeada.
	- Cunando la direccion del rayo es positiva el rayo ha chocado con una celda
	vertitical signifaica que la ultima colision ha sido con un pared de los latera
	les derecaha o izquierda del mapa, limite de grid del mapa. SEgun la pendiente la
	componenete del vector unitario del rayo en el eje x sea positiva o negtiva significa
	que ha sido co nuna pared del este o del oeste respectivamente.
	- Cuando la direccion del rayo es negativa el rayo ha chocado con una celda
	horizontal significa que la ultima colision ha sido con una pared de la parte
	superior o inferior del mapa, limite de grid del mapa. SEgun la pendiente la
	componenete del vector unitario del rayo en el eje y sea positiva o negtiva
	significa que ha sido con una pared del norte o del sur respectivamente.
	- Ademas si ha chocado con una pared especial (BONUS_WALL) se selecciona esa textura
	de la bonus wall, esto lo sabemos el tipo de celda del mapa que hemos chocado. variable guardada
	raydir simepre esta comprendida entre -1 y 1 porque es un vector unitario., circunferencia
	gonimetrixa se podria usar tambien el angulo pero es mas costoso computacionalmente.
	Tambien se podri usar delta_x e y en este caso pero la ligca es la misma
	Parámetros:
	- mlx: Puntero a la estructura principal que contiene toda la información del juego.
	- ray: Puntero a la estructura del rayo que contiene información sobre la dirección del rayo y el lado golpeado.
	Devuelve:
	- Puntero a la textura seleccionada.
*/
t_texture *select_texture(t_mlx *mlx, t_ray *ray)
{
	t_texture *texture;
	
	if (ray->wall_value == BONUS_WALL)
	{
		texture = &(mlx->map->textures)[4];
		return (texture);
	}
	if (ray->side_hit == VERTICAL)
	{
		if (ray->raydir[X] > 0)
			texture = &(mlx->map->textures)[E];
		else
			texture = &(mlx->map->textures)[W];
	}
	else
	{
		if (ray->raydir[Y] > 0)
			texture = &(mlx->map->textures)[N];
		else
			texture = &(mlx->map->textures)[S];
	}
	return texture;
}

/*
	Viene de las ecuaciones parametricas de la linea (x = x0 + t * dx):
	- Donde X0 e Y0 son las coordenadas del jugador
	- DX y DY son las direcciones del rayo
	- t es la distancia a la pared (hipotenusa aprox)
	- Ese porcentaje lo vamos a usar para calcular que porporcion del with de la textura
	usamos para dibujar la pared. (saber su posicion en prporcion al with de la textura)
	por eso hay un ajuste para obtener solo la parte decimal (wall_x - floor(wall_x))
	- Se hace un ajuste para que no se inviertan las texturas en ciertas caras
	wall x es un porcentaje (0-1) de donde el rayo golpea la pared en la baseo
	eje x de la textura. eso es por la inversion de las caras
	Se podria decir que estamosacando la posicion escala 1 de la textura
	
	Retirno de a la funcion:
	- wall_x: Porporcion (0-1) de donde el rayo golpea la pared en la baseo eje x de imagen
	de  la textura with.
	Parámetros:
	- mlx: Puntero a la estructura principal que contiene toda la información del juego.
	- ray: Puntero a la estructura del rayo que contiene información sobre el r
	
	Nota: se osa ala distancia de la hipotenisa (wall_dist) en ligar de la proyección
	para evitar desplazamientos en las texturas debido al efecto de ojo de pez.
*/
double	calculate_wall_x(t_mlx *mlx, t_ray *ray)
{
	double	wall_x;

	if (ray->side_hit == VERTICAL)
		wall_x = mlx->player->pos_y + ray->wall_dist * ray->raydir[Y];
	else
		wall_x = mlx->player->pos_x + ray->wall_dist * ray->raydir[X];
	wall_x -= floor(wall_x);
	if ((ray->side_hit == VERTICAL && ray->raydir[X] < 0) || 
		(ray->side_hit == HORIZONTAL && ray->raydir[Y] > 0))
	{
		wall_x = 1.0 - wall_x;
	}
	return (wall_x);
}

/*
	Calcula los parámetros necesarios para renderizar la textura:
	- tex_x: Coordenada X en la matriz de píxeles de la textura. Representa la posición horizontal
	  en la textura que corresponde al punto de impacto del rayo en la pared.
	  Se calcula multiplicando la proporción de la posición del impacto en la pared (wall_x)
	  por el ancho de la textura. Esto escala la posición relativa (0-1) al rango de píxeles de la textura.
	- text_v_step: Proporción entre la altura de la textura y la altura de la pared en píxeles.
	  Esto determina cuánto se debe avanzar en la textura por cada píxel dibujado en la pantalla,
	  asegurando que la textura no se deforme.
	- tex_pos: Posición inicial en la textura en el eje Y (vertical) desde donde se comenzará
	  a muestrear la textura. Esto se calcula en función de la posición de inicio de la pared
	  en la pantalla (`wall_start`), el centro de la pantalla (`horizon`), y el desplazamiento
	  vertical del jugador (`pitch` y `vertical_offset`). Este cálculo asegura que la textura
	  esté alineada correctamente con la pared renderizada en la pantalla.
	Variables:
	- horizon: Representa el centro de la pantalla ajustado por el pitch (desplazamiento vertical del jugador)
	  y el desplazamiento vertical adicional (vertical_offset). Es el punto de referencia para alinear la textura.
	- ws_offset: Diferencia entre el inicio de la pared (`wall_start`) y el horizonte (`horizon`).
	  Indica cuánto se debe desplazar la textura verticalmente para alinearla con la pared.
	- wall_height_half: Mitad de la altura de la pared en píxeles. Se usa para centrar la textura en la pared.
	Parámetros:
	- wall: Estructura que contiene información sobre la pared.
	- texture: Puntero a la textura.
	- win_height: Altura de la ventana.
	- player: Puntero a la estructura del jugador.
	NOTA:
	- `wall_start` está invertido debido al sistema de coordenadas de la librería gráfica utilizada.
	- Se pueden optimizar algunos cálculos precalculando valores constantes como el horizonte
	  en eventos de cambio de ventana o ajustes de `pitch`.
*/
void	calculate_tex(t_wall *wall, t_texture *texture, int winh, t_player *pl)
{
	int	horizon;
	int ws_offset;
	int wall_height_half;
	
	wall->tex_x = (int)(wall->wall_x * (double)texture->width);
	wall->text_v_step = (float)texture->height / (float)wall->wall_height;
	horizon = (winh >> 1) + pl->pitch_pix + pl->vertical_offset;
	ws_offset = wall->wall_start - horizon;
	wall_height_half = wall->wall_height >> 1;
	wall->tex_pos = (ws_offset + wall_height_half) * wall->text_v_step;
}

/*
	Extrae el color de un píxel de una textura en base a las coordenadas tex_x y tex_y.
	Pasos:
	1. Validar las coordenadas tex_x y tex_y para asegurarse de que están dentro de los límites de la textura.
	2. Calcular la dirección del píxel en la memoria de la textura utilizando tex_x, tex_y, line_length y bits_per_pixel.
	3. Leer el color desde la dirección calculada en la memoria.
	4. Devolver el color como un entero (unsigned int).
	Parámetros:
	- texture: Puntero a la textura de la que se extraerá el color.
	- tex_x, tex_y: Coordenadas del píxel en la textura.
	Devuelve:
	- El color como un entero (unsigned int).
	Optimizaciones de microporcesador (pendiente):
	- Se evita la división utilizando un desplazamiento de bits para calcular el tamaño del píxel en bytes.
	  Se sustituye texture->bits_per_pixel / 8 por texture->bits_per_pixel >> 3
	- Nose pueden usarvariable slocales estaicas porque la imagen de las texturas pueden cambiar en tiempo de ejecucion
	  si se cargan nuevas texturas o se liberan de memoria.
*/
unsigned int	extract_color(t_texture *texture, int tex_x, int tex_y)
{
	unsigned int	color;
	char			*pixel_address;

	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	pixel_address = texture->addr + (tex_y * texture->line_length) + 
		(tex_x * (texture->bits_per_pixel >> 3));
	color = *(unsigned int *)pixel_address;
	return (color);
}
