/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:19 by aloubry           #+#    #+#             */
/*   Updated: 2024/12/02 13:46:40 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <limits.h>
# include <stdint.h>
# include <fcntl.h>

typedef struct s_data
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_philo_eat;
	long long	time_start;
	sem_t		*stop_sem;
	sem_t		*print_sem;
	sem_t		*forks_sem;
	sem_t		*full_philos_sem;
	pid_t			*philo_processes;
}	t_data;

typedef struct s_philo
{
	int			id;
	t_data		*data;
	long long	last_meal;
	int			eat_count;
	sem_t		*last_meal_sem;
	sem_t		*eat_count_sem;
	pthread_t	philo_monitor;
}	t_philo;

// ft_strings.c
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int	ft_atoi(const char *nptr);

// ft_itoa.c
char	*ft_itoa(int num);

//time.c
long long		get_time(void);
long long		get_timestamp(long long time_start);
int				ft_usleep(size_t milliseconds);

//utils.c
void			print_action(t_philo *philo, char *action);
void			print_usage(char *program);

//setup.c
t_data			parse_and_init_data(int argc, char **argv);
t_philo	*init_philosophers(t_data *data);

//monitor.c
void	*monitor_philo(void *void_philo);
void *monitor_stop(void *void_data);
void *monitor_fulls(void *void_data);

//actions.c
void	philo_loop(t_philo *philo);

#endif