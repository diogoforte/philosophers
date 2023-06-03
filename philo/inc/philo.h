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

# define FORK	"has taken a fork\n"
# define EAT	"is eating\n"
# define SLEEP	"is sleeping\n"
# define THINK	"is thinking\n"
# define DIE	"died\n"

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				*someone_died;
	int				*full_eaten;
	time_t			start_time;
	pthread_mutex_t	*death;
	pthread_mutex_t	*write;
}	t_data;

typedef struct s_philo
{
	int				philo_id;
	int				eat_count;
	int				last_meal;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	t_data			data;
}	t_philo;

typedef struct s_table
{
	t_data	data;
	t_philo	*philo;
}	t_table;

int			check_input(int ac, char **av);
int			check_num(char *av);
int			ft_atoi(char *str);
int			init(t_table *f, int ac, char **av);
int			init_data(t_table *f, int ac, char **av);
int			init_philo(t_table *f);
time_t		get_time(void);
void		wait_or_die(t_data data, time_t time);
int			init_mutex(t_table *f);
int			init_threads(t_table *f);
int			join_threads(t_table *f);
void		routine(void *arg);
void		lifecycle(t_philo *philo);
void		print_status(t_philo *philo, pthread_mutex_t *write, char *str);
void		free_philo(t_table *f);
void		free_struct(t_table *f);
void		destroy_mutex(t_table *f);
void		philo_die(t_table *f, time_t now, int index);
void		check_must_eat(t_table *f);
void		philo_checker(t_table *f);
int			next_philo_pos(t_philo *philo);
#endif
