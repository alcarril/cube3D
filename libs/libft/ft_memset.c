/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:44:49 by alcarril          #+#    #+#             */
/*   Updated: 2026/01/15 15:05:09 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_memset(void *s, int c, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		*(unsigned char *)(s + i) = (unsigned char)c;
// 		i++;
// 	}
// 	return (s);
// }

// void	*ft_memset(void *s, int c, size_t n)
// {
//     // size_t			i;
//     unsigned char	*byte_ptr;
//     size_t			*word_ptr;
//     size_t			word_value;

//     byte_ptr = (unsigned char *)s;

//     // Crear un patrón de relleno para operaciones a nivel de palabra
//     word_value = (unsigned char)c;
//     word_value |= word_value << 8;
//     word_value |= word_value << 16;
//     if (sizeof(size_t) == 8) // Si estamos en una arquitectura de 64 bits
//         word_value |= word_value << 32;

//     // Rellenar usando bloques grandes
//     word_ptr = (size_t *)byte_ptr;
//     while (n >= sizeof(size_t))
//     {
//         *word_ptr++ = word_value;
//         n -= sizeof(size_t);
//     }

//     // Rellenar los bytes restantes
//     byte_ptr = (unsigned char *)word_ptr;
//     while (n > 0)
//     {
//         *byte_ptr++ = (unsigned char)c;
//         n--;
//     }

//     return (s);
// }

// void	*ft_memset(void *s, int c, size_t n)
// {
// 	size_t	i;
// 	size_t	n_jumps;
// 	int mode;
	
// 	select_mode(n, &mode, &n_jumps);
// 	if (mode == 0)
// 		mode_chars(s, c, n_jumps);
// 	else if (mode == 1)
// 		mode_chars(s, c, n_jumps);
// 	else if (mode == 2)
// 		mode_ints(s, c, n_jumps);
// 	else if (mode == 3)
// 		mode_longs(s, (long)c, n_jumps);
// 	else if (mode == 4)
// 		mode_long_longs(s, (long long)c, n_jumps);
// }


// void	select_mode(size_t bytes, int *mode, size_t *n_jumps)
// {
// 	if (bytes <= sizeof(char))
// 	{
// 		*n_jumps = bytes / sizeof(char);
// 		*mode = 0;
// 	}
// 	else if (bytes >= sizeof(char) && bytes <= sizeof(int))
// 	{
// 		*n_jumps = bytes / sizeof(char);
// 		*mode = 1;
// 	}
// 	else if (bytes >= sizeof(int) && bytes <= sizeof(long))
// 	{
// 		*n_jumps = bytes / sizeof(int);
// 		*mode = 2;
// 	}
// 	else if (bytes >= sizeof(long) && bytes <= sizeof(long long))
// 	{
// 		*n_jumps = bytes / sizeof(long);
// 		*mode = 3;
// 	}
// 	else
// 	{
// 		*n_jumps = bytes / sizeof(long long);
// 		*mode = 4;
// 	}
// }

// void	mode_chars(void *s, int c, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		*(unsigned char *)(s + i) = (unsigned char)c;
// 		i++;
// 	}
// }

// void	mode_ints(void *s, int c, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		*(int *)(s + i * sizeof(int)) = c;
// 		i++;
// 	}
// }

// void	mode_longs(void *s, long c, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		*(long *)(s + i * sizeof(long)) = c;
// 		i++;
// 	}
// }

// void	mode_long_longs(void *s, long long c, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		*(long long *)(s + i * sizeof(long long)) = c;
// 		i++;
// 	}
// }

////////////////////
void	*ft_memset(void *s, int c, size_t n)
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
	return (s);
}
