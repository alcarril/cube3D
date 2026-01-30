/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/29 22:57:12 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/carbon.h"

int	parse_map_file(char *filename, t_carbon_map *map)
{
	t_carbon_parse	parse_data;

	if (!filename || !map)
		return (0);
	if (!init_parse_data(&parse_data, filename))
		return (0);
	if (!read_file_content(&parse_data))
		return (cleanup_parse(&parse_data, 0));
	if (!parse_elements(&parse_data, map))
		return (cleanup_parse(&parse_data, 0));
	if (!validate_map(map))
		return (cleanup_parse(&parse_data, 0));
	return (cleanup_parse(&parse_data, 1));
}

int	init_parse_data(t_carbon_parse *data, char *filename)
{
	if (!data || !filename)
		return (0);
	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".cub", 4) != 0)
	{
		printf("Error: Invalid file. Expected <path>/file.cub\n");
		return (0);
	}
	data->fd = open(filename, O_RDONLY);
	if (data->fd < 0)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (0);
	}
	data->line = NULL;
	data->file_content = NULL;
	data->texture_count = 0;
	data->color_count = 0;
	data->map_started = 0;
	data->filename = ft_strdup(filename);
	if (!data->filename)
	{
		close(data->fd);
		return (0);
	}
	return (1);
}
