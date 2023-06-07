/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:51:22 by dinunes-          #+#    #+#             */
/*   Updated: 2023/05/23 17:51:22 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_input(int ac, char **av)
{
	while (av[--ac] && ac > 0)
	{
		if (!av[ac][0])
			return (0);
	}
	av++;
	while (*av)
	{
		if (!check_num(*av))
			return (0);
		av++;
	}
	return (1);
}

int	check_num(char *av)
{
	while (*av)
	{
		if (*av < 48 || *av > 57)
			return (0);
		av++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	long int	res;
	int			sign;

	res = 0;
	sign = 1;
	if (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str++ - '0');
		if (res * sign < INT_MIN || res * sign > INT_MAX)
			return (-1);
	}
	return (res *= sign);
}
