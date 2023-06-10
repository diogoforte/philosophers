/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 05:53:36 by dinunes-          #+#    #+#             */
/*   Updated: 2023/06/10 20:58:07 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	checker(t_table *f)
{
	time_t	now;
	int		i;

	i = 0;
	while (!(f->philo->dead) && !(f->philo->full))
	{
		usleep(100);
		i = 0;
		while (i < f->data.number_of_philo)
		{
			now = get_time() - f->data.start_time;
			pthread_mutex_lock(f->philo[i].food);
			if (now >= f->philo[i].last_meal + f->data.time_to_die)
				philo_kill(f, i);
			pthread_mutex_unlock(f->philo[i].food);
			i++;
		}
		if (f->data.times_must_eat != -1)
			philo_full(f);
	}
}

void	philo_kill(t_table *f, int index)
{
	int	i;

	i = 0;
	while (i < f->data.number_of_philo)
	{	
		pthread_mutex_lock(f->philo[i].life);
		f->philo[i].dead = 1;
		pthread_mutex_unlock(f->philo[i].life);
		i++;
	}
	print_status(&f->philo[index], DIE);
}

void	philo_full(t_table *f)
{
	int	i;

	i = 0;
	while (i < f->data.number_of_philo)
	{
		pthread_mutex_lock(f->philo[i].food);
		if (f->philo[i].eat_count < f->data.times_must_eat)
		{
			pthread_mutex_unlock(f->philo[i].food);
			return ;
		}
		pthread_mutex_unlock(f->philo[i].food);
		i++;
	}
	i = 0;
	while (i < f->data.number_of_philo)
	{
		pthread_mutex_lock(f->philo[i].food);
		f->philo[i].full = 1;
		pthread_mutex_unlock(f->philo[i].food);
		i++;
	}
}

int	lock(t_philo *philo)
{
	pthread_mutex_lock(philo->food);
	pthread_mutex_lock(philo->life);
	if (philo->dead || philo->full)
	{
		pthread_mutex_unlock(philo->food);
		pthread_mutex_unlock(philo->life);
		return (0);
	}
	pthread_mutex_unlock(philo->food);
	pthread_mutex_unlock(philo->life);
	return (1);
}
