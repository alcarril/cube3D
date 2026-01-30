/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:11:37 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:36:56 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	fps_counter_average(t_mlx *mlx)
{
	static long long	frames;
	static long long	init_timestamp;
	struct timeval		time;
	long long			now_timestamp;
	long long			delta_time;

	gettimeofday(&time, NULL);
	if (init_timestamp == 0 || ++frames == LLONG_MAX)
	{
		init_timestamp = (long long)time.tv_sec * 1000 + (time.tv_usec / 1000);
		frames = 0;
		return ;
	}
	now_timestamp = (long long)time.tv_sec * 1000 + (time.tv_usec / 1000);
	mlx->now_timestamp = now_timestamp;
	mlx->del_timestamp = now_timestamp - mlx->bef_timestamp;
	delta_time = now_timestamp - init_timestamp;
	if (delta_time >= 1000 && (frames % 140) == 0)
	{
		write(mlx->log_fd, "[Average] FPS: ", 15);
		ft_putnbr_fd((int)(frames * 1000 / delta_time), mlx->log_fd);
		write(mlx->log_fd, "\n", 1);
	}
	mlx->bef_timestamp = now_timestamp;
}

void	fps_counter_realtime(t_mlx *mlx)
{
	static long long	frames;
	static long			init_timestamp;
	struct timeval		time;
	long				now_timestamp;
	long				delta_time;

	gettimeofday(&time, NULL);
	if (init_timestamp == 0 || frames == LLONG_MAX)
	{
		init_timestamp = time.tv_sec * 1000 + (time.tv_usec * 0.001);
		frames = 0;
		return ;
	}
	frames++;
	now_timestamp = time.tv_sec * 1000 + (time.tv_usec * 0.001);
	mlx->del_timestamp = now_timestamp - mlx->bef_timestamp;
	delta_time = now_timestamp - init_timestamp;
	if (delta_time >= 500)
	{
		write(mlx->log_fd, "[Realtime] FPS: ", 16);
		ft_putnbrlend_fd((int)(frames * 1000 / delta_time), mlx->log_fd);
		init_timestamp = now_timestamp;
		frames = 0;
	}
	mlx->bef_timestamp = now_timestamp;
}

bool	is_wall_tile(char map_value)
{
	if (map_value == WALL || map_value == BONUS_WALL)
		return (true);
	return (false);
}

void	ft_memset_int(void *s, int c, size_t n)
{
	size_t	i;
	size_t	jumps;
	int		*ptr;

	ptr = (int *)s;
	i = 0;
	jumps = n / sizeof(int);
	while (i < jumps)
	{
		*(ptr + i) = c;
		i++;
	}
}
