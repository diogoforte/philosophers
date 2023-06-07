/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 06:53:24 by dinunes-          #+#    #+#             */
/*   Updated: 2023/06/07 08:58:23 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_all(t_table *f)
{
	free_philo(f);
	free_struct(f);
	destroy_mutex(f);
}

void	free_philo(t_table *f)
{
	int	i;

	i = -1;
	if (!f->philo)
		return ;
	while (++i < f->data.number_of_philosophers)
	{
		if (f->philo[i].fork)
		{
			pthread_mutex_destroy(f->philo[i].fork);
			free(f->philo[i].fork);
			f->philo[i].fork = NULL;
		}
	}
	if (f->philo)
		free(f->philo);
}

void	free_struct(t_table *f)
{
	if (f->data.someone_died)
	{
		free(f->data.someone_died);
		f->data.someone_died = NULL;
	}
	if (f->data.full_eaten)
	{
		free(f->data.full_eaten);
		f->data.full_eaten = NULL;
	}
}

void	destroy_mutex(t_table *f)
{
	if (f->data.death)
	{
		pthread_mutex_destroy(f->data.death);
		free(f->data.death);
		f->data.death = NULL;
	}
	if (f->data.write)
	{
		pthread_mutex_destroy(f->data.write);
		free(f->data.write);
		f->data.write = NULL;
	}
	if (f->data.meal)
	{
		pthread_mutex_destroy(f->data.meal);
		free(f->data.meal);
		f->data.meal = NULL;
	}
}
