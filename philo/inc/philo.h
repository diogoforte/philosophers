/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:48:42 by dinunes-          #+#    #+#             */
/*   Updated: 2023/05/23 17:48:42 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK   "has taken a fork\n"
# define EAT    "is eating\n"
# define SLEEP  "is sleeping\n"
# define THINK  "is thinking\n"
# define DIE    "died\n"

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				full;
	int				dead;
	pthread_mutex_t	*life;
	pthread_mutex_t	*food;
	time_t			start_time;
}	t_data;

typedef struct s_philo
{
	int				philo_id;
	int				eat_count;
	int				last_meal;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	t_data			*data;
}	t_philo;

typedef struct s_table
{
	t_data	*data;
	t_philo	*philo;
}	t_table;

/* Utility functions */
int			check_input(int ac, char **av);
int			check_num(char *av);
int			ft_atoi(char *str);
void		print_status(t_philo *philo, char *str);
time_t		get_time(void);

/* Initialization functions */
int			init(t_table *f, int ac, char **av);
int			init_data(t_table *f, int ac, char **av);
int			init_philo(t_table *f);
int			init_threads(t_table *f);
int			join_threads(t_table *f);

/* Routine and cycle functions */
void		routine(void *arg);
void		lifecycle(t_philo *philo);
void		forks(t_philo *philo, int action);
void		actions(t_philo *philo, int action);
void		wait_or_die(t_philo *philo, time_t time);

/* Check functions */
void		checker(t_table *f);
void		philo_kill(t_table *f, int index);
void		philo_full(t_table *f);

/* Freeing functions */
void		free_philo(t_table *f);

#endif
