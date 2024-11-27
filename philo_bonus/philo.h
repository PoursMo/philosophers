/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:19 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/27 13:47:50 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <limits.h>


typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_philo_eat;
	long long		time_start;
	int				stop;
	sem_t	*stop_sem;
	sem_t	*print_sem;
}	t_data;

typedef struct s_philo
{
	int				id;
	sem_t	**right_fork;
	sem_t	**left_fork;
	t_data			*data;
	long long		last_meal;
	int				eat_count;
	sem_t	*last_meal_sem;
	sem_t	*eat_count_sem;
}	t_philo;

//actions.c
void			*philo_loop(void *void_data);

//utils.c
int				is_stop(t_data *data);
void			print_action(t_philo *philo, char *action);
void			print_usage(char *program);

//monitor.c
void			*monitor_philos(void *void_philosophers);

//itoa.c
char	*ft_itoa(int num);

//minilibft.c
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(const char *str1, const char *str2);

//time.c
long long		get_time(void);
long long		get_timestamp(long long time_start);

//setup.c
t_data	parse_and_init_data(int argc, char **argv);
sem_t	**init_forks(int number_of_forks);
t_philo	*init_philosophers(t_data *data, sem_t **forks);

#endif