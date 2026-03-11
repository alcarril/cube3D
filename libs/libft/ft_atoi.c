/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:01:02 by alcarril          #+#    #+#             */
/*   Updated: 2026/03/11 18:43:58 by carbon-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_ovflow(unsigned long long num, int neg)
{
	if (neg == -1 && num > 9223372036854775807)
		return (0);
	if (neg == 1 && num > 9223372036854775807)
		return (-1);
	return (num);
}

int	ft_atoi(const char *nptr)
{
	int					i;
	unsigned long long	num;
	int					sign;

	i = 0;
	num = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		sign *= -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + nptr[i] - 48;
		i++;
	}
	num = ft_ovflow(num, sign);
	return (num * sign);
}
