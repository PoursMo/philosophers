/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:19 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/26 18:11:20 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_data
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_philo_eat;
	long long	time_start;
	int		stop;
	pthread_mutex_t stop_mutex;
	pthread_mutex_t print_mutex;
} t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	t_data 			*data;
	long long		last_meal;
	int				eat_count;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t eat_count_mutex;
} t_philo;

//actions1.c
void	*philo_loop(void *void_data);

//actions2.c
int	is_stop(t_data *data);
void print_action(t_philo *philo, char *action);

//monitor.c
void	*monitor(void *void_philosophers);

//time.c
long long	get_time();
long long	get_timestamp(long long time_start);
int	ft_usleep(size_t milliseconds);

//setup.c
t_data	parse_and_init_data(int argc, char **argv);
pthread_mutex_t	*init_forks(int number_of_forks);
t_philo	*init_philosophers(t_data *data, pthread_mutex_t *forks);

#endif