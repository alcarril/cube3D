/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alejandro         #+#    #+#             */
/*   Updated: 2025/12/26 14:08:37 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/carbon.h"

int	read_file_content(t_parse *data)
{
	int		lines;
	int		i;

	if (!data || !data->filename)
		return (0);
	lines = count_file_lines(data->fd);
	if (lines <= 0)
		return (0);
	data->file_content = ft_calloc(lines + 1, sizeof(char *));
	if (!data->file_content)
		return (0);
	close(data->fd);
	data->fd = open(data->filename, O_RDONLY);
	if (data->fd < 0)
		return (0);
	i = 0;
	while ((data->line = get_next_line(data->fd)) != NULL)
	{
		data->file_content[i] = ft_strtrim(data->line, "\n");
		free(data->line);
		if (!data->file_content[i])
			return (0);
		i++;
	}
	return (1);
}

int	count_file_lines(int fd)
{
	char	*line;
	int		count;

	if (fd < 0)
		return (0);
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	return (count);
}