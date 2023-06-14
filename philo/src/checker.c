/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 05:53:36 by dinunes-          #+#    #+#             */
/*   Updated: 2023/06/14 07:44:10 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	checker(t_table *f)
{
	time_t	now;
	int		i;

	i = 0;
	while (!(f->data->dead) && !(f->data->full))
	{
		usleep(100);
		i = 0;
		while (i < f->data->number_of_philo)
		{
			now = get_time() - f->data->start_time;
			pthread_mutex_lock(f->data->food);
			if (now >= f->philo[i].last_meal + f->data->time_to_die)
			{
				pthread_mutex_unlock(f->data->food);
				philo_kill(f, i);
			}
			else
				pthread_mutex_unlock(f->data->food);
			i++;
		}
		if (f->data->times_must_eat != -1)
			philo_full(f);
	}
}

void	philo_kill(t_table *f, int index)
{
	time_t	time;

	time = get_time() - f->philo->data->start_time;
	if (f->data->dead || f->data->full)
		return ;
	pthread_mutex_lock(f->data->life);
	f->data->dead = 1;
	pthread_mutex_unlock(f->data->life);
	usleep(10);
	printf("\033[0;90m%ld	\033[0;91m%d \033[0;0m%s",
		time, index + 1, DIE);
}

void	philo_full(t_table *f)
{
	int	i;

	i = 0;
	while (i < f->data->number_of_philo)
	{
		pthread_mutex_lock(f->data->food);
		if (f->philo[i].eat_count < f->data->times_must_eat)
		{
			pthread_mutex_unlock(f->data->food);
			return ;
		}
		pthread_mutex_unlock(f->data->food);
		i++;
	}
	pthread_mutex_lock(f->data->food);
	f->data->full = 1;
	pthread_mutex_unlock(f->data->food);
}
