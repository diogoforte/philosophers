/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:51:25 by dinunes-          #+#    #+#             */
/*   Updated: 2023/05/23 17:51:25 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init(t_table *f, int ac, char **av)
{
	f->data.someone_died = malloc(sizeof(int));
	f->data.full_eaten = malloc(sizeof(int));
	if (!f->data.someone_died || !f->data.full_eaten)
		return (0);
	*f->data.someone_died = 0;
	*f->data.full_eaten = 0;
	f->data.start_time = get_time();
	if (!init_data(f, ac, av))
		return (0);
	if (!init_mutex(f))
		return (0);
	if (!init_philo(f))
		return (0);
	if (!init_threads(f))
		return (0);
	philo_checker(f);
	if (!join_threads(f))
		return (0);
	return (1);
}

int	init_data(t_table *f, int ac, char **av)
{
	f->data.number_of_philosophers = ft_atoi(av[1]);
	f->data.time_to_die = ft_atoi(av[2]);
	f->data.time_to_eat = ft_atoi(av[3]);
	f->data.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		f->data.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		f->data.number_of_times_each_philosopher_must_eat = -1;
	if (f->data.number_of_philosophers <= 0 || f->data.time_to_die <= 0
		|| f->data.time_to_eat <= 0 || f->data.time_to_sleep <= 0)
		return (0);
	return (1);
}

int	init_philo(t_table *f)
{
	int	i;

	i = -1;
	f->philo = malloc(sizeof(t_philo) * f->data.number_of_philosophers);
	if (!f->philo)
		return (0);
	while (++i < f->data.number_of_philosophers)
	{
		f->philo[i].philo_id = i + 1;
		f->philo[i].eat_count = 0;
		f->philo[i].last_meal = 0;
		f->philo[i].data = f->data;
		f->philo[i].fork = malloc(sizeof(pthread_mutex_t));
		if (!f->philo[i].fork || pthread_mutex_init(f->philo[i].fork, NULL))
			return (0);
	}
	return (1);
}

int	init_mutex(t_table *f)
{
	f->data.death = malloc(sizeof(pthread_mutex_t));
	f->data.write = malloc(sizeof(pthread_mutex_t));
	if (!f->data.death || !f->data.write)
		return (0);
	if (pthread_mutex_init(f->data.death, NULL)
		|| pthread_mutex_init(f->data.write, NULL))
		return (0);
	return (1);
}

void	philo_checker(t_table *f)
{
	time_t	now;
	int		i;

	i = 0;
	while (!(*f->data.someone_died) && !(*f->data.full_eaten)
		&& f->data.number_of_philosophers > 1)
	{
		usleep(100);
		while (i < f->data.number_of_philosophers)
		{
			now = get_time() - f->data.start_time;
			if (now >= f->philo[i].last_meal + f->data.time_to_die)
			{
				philo_die(f, now, i);
				return ;
			}
			i++;
		}
		i = 0;
		if (f->data.number_of_times_each_philosopher_must_eat != -1)
			check_must_eat(f);
	}
}
