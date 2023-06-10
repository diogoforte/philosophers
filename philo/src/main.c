/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:47:22 by dinunes-          #+#    #+#             */
/*   Updated: 2023/05/23 17:47:22 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_table	f;

	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (!check_input(ac, av))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (!init(&f, ac, av))
	{
		printf("Error: Initializing arguments\n");
		free_philo(&f);
		return (1);
	}
	free_philo(&f);
	return (0);
}
