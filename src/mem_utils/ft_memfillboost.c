/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memfillboost.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:25:34 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/30 15:28:22 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	ft_memfillboost(void *s, int c, size_t n)
{
	while (n > 0 && ((uintptr_t)s % sizeof(unsigned long long)) != 0)
	{
		*(unsigned char *)s = ((unsigned char *)&c)[0];
		s = (unsigned char *)s + 1;
		n--;
	}
	if (n >= sizeof(unsigned long long))
		ft_memfilllonglong(&s, c, &n);
	if (n >= sizeof(unsigned long))
		ft_memfilllong(&s, c, &n);
	if (n >= sizeof(int))
		ft_memfillint(&s, c, &n);
	else
		ft_memfillchar(s, c, n);
}

void	ft_memfilllonglong(void **s, int c, size_t *n)
{
	unsigned long long	data;
	unsigned long long	*ptr;
	size_t				jumps;
	size_t				i;

	data = (unsigned int)c;
	data |= data << 32;
	ptr = (unsigned long long *)(*s);
	jumps = *n >> 3;
	i = 0;
	while (i < jumps)
		ptr[i++] = data;
	*s = (void *)(ptr + i);
	*n -= jumps * sizeof(unsigned long long);
}

void	ft_memfilllong(void **s, int c, size_t *n)
{
	unsigned long	data;
	unsigned long	*ptr;
	size_t			jumps;
	size_t			i;

	data = (unsigned int)c;
	data |= data << 32;
	ptr = (unsigned long *)(*s);
	jumps = *n >> 3;
	i = 0;
	while (i < jumps)
		ptr[i++] = data;
	*s = (void *)(ptr + i);
	*n -= jumps * sizeof(unsigned long);
}

void	ft_memfillint(void **s, int c, size_t *n)
{
	int		*ptr;
	size_t	jumps;
	size_t	i;

	ptr = (int *)(*s);
	jumps = *n >> 2;
	i = 0;
	while (i < jumps)
		ptr[i++] = c;
	*s = (void *)(ptr + i);
	*n -= jumps * sizeof(int);
}

void	ft_memfillchar(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = (unsigned char)c;
}
