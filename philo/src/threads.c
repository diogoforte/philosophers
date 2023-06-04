/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:47:52 by dinunes-          #+#    #+#             */
/*   Updated: 2023/06/04 01:09:36 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_threads(t_table *f)
{
	int	i;

	i = 0;
	while (i < f->data.number_of_philosophers)
	{
		if (pthread_create(&f->philo[i].thread,
				NULL, (void *)routine, &(f->philo[i])))
			return (0);
		i++;
	}
	return (1);
}

int	join_threads(t_table *f)
{
	int	i;

	i = 0;
	while (i < f->data.number_of_philosophers)
	{
		if (pthread_join(f->philo[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}
