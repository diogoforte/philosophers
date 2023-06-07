/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 05:53:36 by dinunes-          #+#    #+#             */
/*   Updated: 2023/06/07 08:12:54 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	checker(t_table *f)
{
	time_t	now;
	int		i;

	i = 0;
	while (!(*f->data.someone_died) && !(*f->data.full_eaten)
		&& f->data.number_of_philosophers > 1)
	{
		usleep(100);
		i = 0;
		while (i < f->data.number_of_philosophers)
		{
			now = get_time() - f->data.start_time;
			pthread_mutex_lock(f->philo->data.meal);
			if (now >= f->philo[i].last_meal + f->data.time_to_die)
			{
				philo_die(f, now, i);
				pthread_mutex_unlock(f->philo->data.meal);
				return ;
			}
			pthread_mutex_unlock(f->philo->data.meal);
			i++;
		}
		if (f->data.number_of_times_each_philosopher_must_eat != -1)
			must_eat(f);
	}
}

void	philo_die(t_table *f, time_t now, int index)
{
	pthread_mutex_lock(f->data.death);
	pthread_mutex_lock(f->data.write);
	printf("%ld %d %s", now, f->philo[index].philo_id, DIE);
	pthread_mutex_unlock(f->data.write);
	*f->data.someone_died = 1;
	pthread_mutex_unlock(f->data.death);
}

void	must_eat(t_table *f)
{
	int	i;

	i = 0;
	pthread_mutex_lock(f->data.meal);
	while (i < f->data.number_of_philosophers)
	{
		if (f->philo[i].eat_count
			< f->data.number_of_times_each_philosopher_must_eat)
			{
				pthread_mutex_unlock(f->data.meal);
				return ;
			}
		i++;
	}
	pthread_mutex_unlock(f->data.meal);
	*f->data.full_eaten = 1;
}
