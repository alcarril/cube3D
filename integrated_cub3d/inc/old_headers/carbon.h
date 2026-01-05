/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carbon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:15:03 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/04 12:40:36 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CARBON_H
#define CARBON_H

/*
	DEFINES:
*/
#define MAX_LINE_LENGTH 1024

/*
	FUNCTION PROTOTIPES:
*/

// Funciones de parsing directo a estructuras de alexpruebas
int		parse_cub_file(char *filename, t_map *map, t_player *player);
int		validate_cub_map(t_map *map, t_player *player);
void	free_map_textures(t_map *map);

#endif