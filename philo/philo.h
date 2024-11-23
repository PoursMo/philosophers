/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:19 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/23 14:04:59 by aloubry          ###   ########.fr       */
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
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	long long	time_start;
} t_data;

typedef struct s_philo
{
	int		id;
	pthread_mutex_t 	*right_fork;
	pthread_mutex_t 	*left_fork;
	t_data 	*data;
	long long	last_meal;
	int		eat_count;
} t_philo;

//actions1.c
void	*philo_take_left_fork(void *void_data);
void	*philo_take_right_fork(void *void_data);
void	*philo_eat(void *void_data);
void	*philo_think(void *void_data);
void	*philo_sleep(void *void_data);

//time.c
long long	get_time();
long long	get_timestamp(long long time_start);

#endif