/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:57:41 by dinunes-          #+#    #+#             */
/*   Updated: 2023/06/02 07:23:32 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

time_t	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) < 0)
	{
		return (0);
	}
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	wait_or_die(t_data data, time_t time)
{
	time_t	start;
	time_t	now;

	start = get_time();
	while (!(*data.someone_died))
	{
		now = get_time();
		if (now - start >= time)
			break ;
		usleep(100);
	}
}
