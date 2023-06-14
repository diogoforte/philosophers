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

void	print_status(t_philo *philo, char *str)
{
	time_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(philo->data->life);
	pthread_mutex_lock(philo->data->food);
	if (philo->data->dead || philo->data->full)
	{
		pthread_mutex_unlock(philo->data->life);
		pthread_mutex_unlock(philo->data->food);
		return ;
	}
	pthread_mutex_unlock(philo->data->life);
	pthread_mutex_unlock(philo->data->food);
	printf("\033[0;90m%ld	\033[0;91m%d \033[0;0m%s",
		time, philo->philo_id, str);
}

time_t	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) < 0)
	{
		return (0);
	}
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
