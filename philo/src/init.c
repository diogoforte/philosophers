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
	f->philo = NULL;
	f->data = NULL;
	if (!init_data(f, ac, av))
		return (0);
	f->data->start_time = get_time();
	if (!init_philo(f))
		return (0);
	if (!init_threads(f))
		return (0);
	if (f->data->number_of_philo > 1)
		checker(f);
	if (!join_threads(f))
		return (0);
	return (1);
}

int	init_data(t_table *f, int ac, char **av)
{
	f->data = malloc(sizeof(t_data));
	if (!f->data)
		return (0);
	f->data->number_of_philo = ft_atoi(av[1]);
	f->data->time_to_die = ft_atoi(av[2]);
	f->data->time_to_eat = ft_atoi(av[3]);
	f->data->time_to_sleep = ft_atoi(av[4]);
	f->data->times_must_eat = -1;
	if (ac == 6)
		f->data->times_must_eat = ft_atoi(av[5]);
	if (f->data->number_of_philo <= 0 || f->data->time_to_die <= 0
		|| f->data->time_to_eat <= 0 || f->data->time_to_sleep <= 0)
	{
		free(f->data);
		return (0);
	}
	f->data->dead = 0;
	f->data->full = 0;
	f->data->life = malloc(sizeof(pthread_mutex_t));
	f->data->food = malloc(sizeof(pthread_mutex_t));
	if (!f->data->life || !f->data->food
		|| pthread_mutex_init(f->data->life, NULL)
		|| pthread_mutex_init(f->data->food, NULL))
		return (0);
	return (1);
}

int	init_philo(t_table *f)
{
	int	i;

	i = -1;
	f->philo = malloc(sizeof(t_philo) * f->data->number_of_philo);
	if (!f->philo)
		return (0);
	while (++i < f->data->number_of_philo)
	{
		f->philo[i].philo_id = i + 1;
		f->philo[i].eat_count = 0;
		f->philo[i].last_meal = 0;
		f->philo[i].data = f->data;
		f->philo[i].fork = malloc(sizeof(pthread_mutex_t));
		if (!f->philo[i].fork)
			return (0);
		if (pthread_mutex_init(f->philo[i].fork, NULL))
			return (0);
	}
	return (1);
}

void	free_philo(t_table *f)
{
	int	i;

	i = -1;
	if (!f->philo)
		return ;
	while (++i < f->data->number_of_philo)
	{
		if (f->philo[i].fork)
		{
			pthread_mutex_destroy(f->philo[i].fork);
			free(f->philo[i].fork);
		}
	}
	if (f->data)
	{
		pthread_mutex_destroy(f->data->life);
		free(f->data->life);
		pthread_mutex_destroy(f->data->food);
		free(f->data->food);
		free(f->data);
		f->data = NULL;
	}
	if (f->philo)
		free(f->philo);
}
