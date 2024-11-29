/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:19 by aloubry           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/29 13:02:35 by aloubry          ###   ########.fr       */
=======
/*   Updated: 2024/11/27 15:47:45 by aloubry          ###   ########.fr       */
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
<<<<<<< HEAD
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
=======
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdint.h>


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
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
}	t_data;

typedef struct s_philo
{
<<<<<<< HEAD
	int			id;
	t_data		*data;
	long long	last_meal;
	int			eat_count;
	sem_t		*last_meal_sem;
	sem_t		*eat_count_sem;
}	t_philo;

// ft_strings.c
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
=======
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
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2


<<<<<<< HEAD
// ft_itoa.c
char	*ft_itoa(int num);
=======
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
int				ft_usleep(size_t milliseconds);

//setup.c
t_data	parse_and_init_data(int argc, char **argv);
sem_t	**init_forks(int number_of_forks);
t_philo	*init_philosophers(t_data *data, sem_t **forks);
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2

#endif