/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alejandro         #+#    #+#             */
/*   Updated: 2025/12/25 19:10:56 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/carbon.h"

static int	g_player_found = 0;

int	find_player_position(char *line, t_player *player, int y)
{
	int	i;

	if (!line || !player)
		return (1);
	
	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || 
			line[i] == 'E' || line[i] == 'W')
		{
			if (g_player_found)
			{
				printf("Error: Multiple players found\n");
				return (0);
			}
			player->x = i + 0.5; // Centro de la casilla
			player->y = y + 0.5; // Centro de la casilla
			player->direction = line[i];
			set_player_angle(player);
			line[i] = '0'; // Reemplazar con suelo
			g_player_found = 1;
		}
		i++;
	}
	return (1);
}

void	set_player_angle(t_player *player)
{
	if (!player)
		return;
	
	if (player->direction == 'N')
		player->angle = 3 * M_PI / 2; // 270° (arriba en pantalla)
	else if (player->direction == 'S')
		player->angle = M_PI / 2;     // 90°  (abajo en pantalla)
	else if (player->direction == 'E')
		player->angle = 0;            // 0°   (derecha)
	else if (player->direction == 'W')
		player->angle = M_PI;         // 180° (izquierda)
}