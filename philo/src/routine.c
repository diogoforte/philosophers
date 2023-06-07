/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 01:06:34 by dinunes-          #+#    #+#             */
/*   Updated: 2023/06/07 17:57:41 by dinunes-         ###   ########.fr       */
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
		pthread_mutex_lock(philo->data.death);
		if (!(*philo->data.someone_died))
		{
			pthread_mutex_unlock(philo->data.death);
			lifecycle(philo);
		}
		else
			pthread_mutex_unlock(philo->data.death);
	}
}

void	lifecycle(t_philo *philo)
{
	pthread_mutex_lock(philo->data.write);
	pthread_mutex_lock(philo->data.meal);
	pthread_mutex_lock(philo->data.death);
	while (!(*philo->data.someone_died) && !(*philo->data.full_eaten))
	{
		pthread_mutex_unlock(philo->data.write);
		pthread_mutex_unlock(philo->data.meal);
		pthread_mutex_unlock(philo->data.death);
		forks(philo, 1);
		actions(philo, 0);
		forks(philo, 2);
		actions(philo, 1);
		pthread_mutex_lock(philo->data.write);
		pthread_mutex_lock(philo->data.meal);
		pthread_mutex_lock(philo->data.death);
	}
	pthread_mutex_unlock(philo->data.write);
	pthread_mutex_unlock(philo->data.meal);
	pthread_mutex_unlock(philo->data.death);
}

void	forks(t_philo *philo, int action)
{
	t_philo	*next_philo;

		if (philo->philo_id < philo->data.number_of_philosophers)
			next_philo = &philo[philo->philo_id];
		else
			next_philo = &philo[-1 * (philo->data.number_of_philosophers - 1)];
	if (action == 1)
	{
		if (philo->philo_id < next_philo->philo_id)
		{
			pthread_mutex_lock(philo->fork);
			pthread_mutex_lock(next_philo->fork);
		}
		else
		{
			pthread_mutex_lock(next_philo->fork);
			pthread_mutex_lock(philo->fork);
		}
	}
	else if (action == 2)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(next_philo->fork);
	}
}

void	actions(t_philo *philo, int action)
{
	if (action == 0)
	{
		print_status(philo, FORK);
		print_status(philo, FORK);
		print_status(philo, EAT);
		pthread_mutex_lock(philo->data.meal);
		philo->last_meal = get_time() - philo->data.start_time;
		philo->eat_count++;
		pthread_mutex_unlock(philo->data.meal);
		wait_or_die(philo->data, philo->data.time_to_eat);
	}
	else if (action == 2)
	{
		print_status(philo, SLEEP);
		wait_or_die(philo->data, philo->data.time_to_sleep);
		print_status(philo, THINK);
	}
}

void	wait_or_die(t_data data, time_t time)
{
	time_t	start;
	time_t	now;

	pthread_mutex_lock(data.meal);
	start = get_time();
	while (!(*data.someone_died))
	{
		now = get_time();
		if (now - start >= time)
			break ;
		usleep(100);
	}
	pthread_mutex_unlock(data.meal);
}
