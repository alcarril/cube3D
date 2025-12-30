/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alejandro         #+#    #+#             */
/*   Updated: 2025/12/25 19:10:56 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/carbon.h"

int	parse_elements(t_parse *data, t_map *map)
{
	int	i;

	if (!data || !map || !data->file_content)
		return (0);
	i = 0;
	while (data->file_content[i] && !data->map_started)
	{
		if (is_empty_line(data->file_content[i]))
		{
			i++;
			continue;
		}
		if (is_texture_line(data->file_content[i]))
		{
			if (!parse_texture(data->file_content[i], map))
				return (0);
			data->texture_count++;
		}
		else if (is_color_line(data->file_content[i]))
		{
			if (!parse_color(data->file_content[i], map))
				return (0);
			data->color_count++;
		}
		else if (data->texture_count == 4 && data->color_count == 2)
		{
			data->map_started = 1;
			return (parse_map_grid(data, map, i));
		}
		else
		{
			printf("Error: Invalid line: %s\n", data->file_content[i]);
			return (0);
		}
		i++;
	}
	if (data->texture_count != 4 || data->color_count != 2)
	{
		printf("Error: Missing elements (textures: %d/4, colors: %d/2)\n", 
			data->texture_count, data->color_count);
		return (0);
	}
	return (0);
}