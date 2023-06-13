/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 01:06:34 by dinunes-          #+#    #+#             */
/*   Updated: 2023/06/13 23:53:04 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	routine(void *arg)
{
	time_t	time;
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_philo == 1)
	{
		time = philo->data->time_to_die;
		wait_or_die(philo, philo->data->time_to_die);
		printf("%ld %d %s", time, philo->philo_id, DIE);
		return ;
	}
	else
	{
		if (philo->philo_id % 2)
			wait_or_die(philo, philo->data->number_of_philo);
		if (!philo->data->dead)
			lifecycle(philo);
	}
}

void	lifecycle(t_philo *philo)
{
	while (1)
	{
		if (!lock(philo))
			return ;
		usleep(100);
		forks(philo, 1);
		actions(philo, 1);
		forks(philo, 2);
		actions(philo, 2);
	}
}

void	forks(t_philo *philo, int action)
{
	t_philo	*next_philo;

	if (philo->philo_id < philo->data->number_of_philo)
		next_philo = &philo[1];
	else
		next_philo = &philo[-1 * (philo->data->number_of_philo - 1)];
	if (action == 1)
	{
		if (philo->philo_id < next_philo->philo_id)
		{
			pthread_mutex_lock(philo->fork);
			pthread_mutex_lock(next_philo->fork);
			return ;
		}
		pthread_mutex_lock(next_philo->fork);
		pthread_mutex_lock(philo->fork);
	}
	else if (action == 2)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(next_philo->fork);
	}
}

void	actions(t_philo *philo, int action)
{
	if (action == 1)
	{
		print_status(philo, FORK);
		print_status(philo, FORK);
		print_status(philo, EAT);
		pthread_mutex_lock(philo->food);
		philo->last_meal = get_time() - philo->data->start_time;
		philo->eat_count++;
		pthread_mutex_unlock(philo->food);
		wait_or_die(philo, philo->data->time_to_eat);
	}
	else if (action == 2)
	{
		print_status(philo, SLEEP);
		wait_or_die(philo, philo->data->time_to_sleep);
		print_status(philo, THINK);
	}
}

void	wait_or_die(t_philo *philo, time_t time)
{
	time_t	start;
	time_t	now;

	start = get_time();
	pthread_mutex_lock(philo->life);
	while (!philo->data->dead)
	{
		now = get_time();
		if (now - start >= time)
			break ;
		usleep(100);
	}
	pthread_mutex_unlock(philo->life);
}
