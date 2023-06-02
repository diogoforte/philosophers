/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 06:53:24 by dinunes-          #+#    #+#             */
/*   Updated: 2023/06/02 07:19:01 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
		}
	}
	if (f->philo)
		free(f->philo);
}

void	free_struct(t_table *f)
{
	if (f->data.someone_died)
		free(f->data.someone_died);
	if (f->data.full_eaten)
		free(f->data.full_eaten);
	if (f->data.death)
		free(f->data.death);
	if (f->data.write)
		free(f->data.write);
}

void	destroy_mutex(t_table *f)
{
	pthread_mutex_destroy(f->data.death);
	pthread_mutex_destroy(f->data.write);
}
