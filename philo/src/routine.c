/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 01:06:34 by dinunes-          #+#    #+#             */
/*   Updated: 2023/06/04 02:33:06 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	routine(void *arg)
{
	time_t	time;
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data.number_of_philosophers == 1)
	{
		time = get_time() - philo->data.start_time;
		wait_or_die(philo->data, philo->data.time_to_die);
		printf("%ld %d %s", time, philo->philo_id, DIE);
		return ;
	}
	else
	{
		if (philo->philo_id % 2)
			wait_or_die(philo->data, 1);
		if (!(*philo->data.someone_died))
			lifecycle(philo);
	}
}

int	next_philo_pos(t_philo *philo)
{
	int	nextpos;
	int	i;

	nextpos = 0;
	i = 0;
	if (philo->philo_id < philo->data.number_of_philosophers)
		nextpos = i + 1;
	else
		nextpos = -1 * (philo->data.number_of_philosophers - 1);
	return (nextpos);
}

void	lifecycle(t_philo *philo)
{
	int	nextpos;

	while (!(*philo->data.someone_died) && !(*philo->data.full_eaten))
	{
		pthread_mutex_lock(philo->fork);
		print_status(philo, philo->data.write, FORK);
		nextpos = next_philo_pos(philo);
		pthread_mutex_lock(philo[nextpos].fork);
		print_status(philo, philo->data.write, FORK);
		print_status(philo, philo->data.write, EAT);
		philo->last_meal = get_time() - philo->data.start_time;
		philo->eat_count++;
		wait_or_die(philo->data, philo->data.time_to_eat);
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo[nextpos].fork);
		print_status(philo, philo->data.write, SLEEP);
		wait_or_die(philo->data, philo->data.time_to_sleep);
		print_status(philo, philo->data.write, THINK);
	}
}

void	philo_die(t_table *f, time_t now, int index)
{
	pthread_mutex_lock(f->data.death);
	pthread_mutex_lock(f->data.write);
	printf("%ld %d %s", now, f->philo[index].philo_id, DIE);
	*f->data.someone_died = 1;
	pthread_mutex_unlock(f->data.write);
	pthread_mutex_unlock(f->data.death);
}

void	check_must_eat(t_table *f)
{
	int	i;

	i = 0;
	while (i < f->data.number_of_philosophers)
	{
		if (f->philo[i].eat_count
			< f->data.number_of_times_each_philosopher_must_eat)
			return ;
		i++;
	}
	*f->data.full_eaten = 1;
}
