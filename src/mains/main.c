/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:12:38 by alejandro         #+#    #+#             */
/*   Updated: 2025/12/26 13:46:21 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/carbon.h"

int main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (ft_strlen(argv[1]) < 4 || ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		printf("Error: Map file must have .cub extension\n");
		return (1);
	}
	if (!init_map(&map))
	{
		printf("Error: Failed to initialize map\n");
		return (1);
	}
	if (!parse_map_file(argv[1], &map))
	{
		printf("Error: Invalid map file\n");
		cleanup_map(&map);
		return (1);
	}
	printf("Map parsed successfully!\n");
	print_map_info(&map); // Para debug
	cleanup_map(&map);
	return (0);
}