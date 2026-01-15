/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:12:38 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/15 23:00:38 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3D.h"

//main con mapa antes de tener hecho el parseo
int main (void)
{
	t_mlx	mlx;
	t_map	map;
	t_player	player;
	t_frame	frame;
	
	map.max_columns = MAX_COLUMS;
	map.max_rows = MAX_ROWS;
	char map_data[15][20] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	memcpy(map.map_grids, map_data, sizeof(map_data));
	mlx.map = &map;//quizas osbre si no hay que escalar

	//TEST
	// map.floor_color[0] = 100;
	// map.floor_color[1] = 100;
	// map.floor_color[2] = 100;

	//GRIS
	map.floor_color[0] = 170;
	map.floor_color[1] = 170;
	map.floor_color[2] = 170;

	//GRIS MUY OSCURO
	map.floor_color[0] = 0;  // Rojo
	map.floor_color[1] = 5;  // Verde
	map.floor_color[2] = 0;  // Azul


	//TEST
	// map.ceiling_color[0] = 200;//200
	// map.ceiling_color[1] = 200;//200
	// map.ceiling_color[2] = 200;//200

	//AZUL CLARO
	// map.ceiling_color[0] = 70;//200
	// map.ceiling_color[1] = 130;//200
	// map.ceiling_color[2] = 180;//200

	//AZUL MUY OSCURO
	map.ceiling_color[0] = 0;  // Rojo
	map.ceiling_color[1] = 0;  // Verde
	map.ceiling_color[2] = 5; 

	//NEGRO
	// map.ceiling_color[0] = 0; // Rojo
	// map.ceiling_color[1] = 0; // Verde
	// map.ceiling_color[2] = 0; // Azul

	//NORTE SUR ESTE OESTE
	// char *texture_paths[4] = {
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/test/south.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/test/north.xpm", // SUR -> NORTE
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/test/east.xpm",  // OESTE -> ESTE
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/test/west.xpm"  // ESTE -> OESTE
	// };
	//MATRIX
	// char *texture_paths[4] = {
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/matrix.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/matrix.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/matrix.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/matrix.xpm", // NORTE -> SUR
	// };

	//MEDIEVAL	
	// char *texture_paths[4] = {
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/wolfenstein/grey_stone.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/wolfenstein/grey_stone.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/wolfenstein/grey_stone.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/wolfenstein/grey_stone.xpm"  // ESTE -> OESTE
	// };
	
	//CARBON
	// char *texture_paths[4] = {
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/self/carbon.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/self/carbon.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/self/carbon.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/self/carbon.xpm", // NORTE -> SUR
	// };

	//neo
	// char *texture_paths[4] = {
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/self/neo.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/self/neo.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/self/neo.xpm", // NORTE -> SUR
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/self/neo.xpm", // NORTE -> SUR
	// };

	//adolfo
	char *texture_paths[4] = {
		"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/self/adolfo.xpm", // NORTE -> SUR
		"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/self/neo.xpm", // NORTE -> SUR
		"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/self/neo.xpm", // NORTE -> SUR
		"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/self/neo.xpm", // NORTE -> SUR
	};

	
	// char *texture_paths[4] = {
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/simonkraft/wet_sponge.xpm",  // OESTE -> ESTE
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/simonkraft/wet_sponge.xpm",  // OESTE -> ESTE
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/simonkraft/wet_sponge.xpm",  // OESTE -> ESTE
	// 	"/home/alejandro/42Universe/42Proyects/cube3D/assets/textures/other/simonkraft/wet_sponge.xpm",  // OESTE -> ESTE
	// };

	int i = 0;
	while (i < 4)
	{
		map.texture_paths[i] = texture_paths[i];
		i++;
	}
	//LO de antes de qui es la infomacion que tienes que cargar tu
	if (init_mlx_components(&mlx) == false)
		return (1);
	if (setup_game(&mlx, &player, &map, &frame) == false)
		return (1);
	start_hooks_and_game(&mlx);
	mlx_loop(mlx.mlx_var);
	return(0);
}