/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by carbon            #+#    #+#             */
/*   Updated: 2026/01/05 14:58:36 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3D.h"

int main (int argc, char **argv)
{
	t_mlx	mlx;
	t_map	map;
	t_player	player;
	
	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}

	// Verificar que el archivo termina en .cub
	char *extension = ft_strrchr(argv[1], '.');
	if (!extension || ft_strncmp(extension, ".cub", 4) != 0)
	{
		printf("Error: Map file must have .cub extension\n");
		return (1);
	}

	// Parsear directamente a las estructuras
	if (!parse_cub_file(argv[1], &map, &player))
	{
		printf("Error: Failed to parse map file\n");
		free_map_textures(&map);
		return (1);
	}

	// Validar el mapa parseado
	if (!validate_cub_map(&map, &player))
	{
		printf("Error: Invalid map format\n");
		free_map_textures(&map);
		return (1);
	}

	// Inicializar MLX
	if (!init_mlx_components(&mlx))
	{
		free_map_textures(&map);
		return (1);
	}
	
	mlx.map = &map;
	mlx.player = &player;
	setup_player(&mlx);
	create_hooks(&mlx);
	mlx_loop(mlx.mlx_var);
	
	free_map_textures(&map);
	return(0);
}