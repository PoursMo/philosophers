/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:19 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/29 13:02:35 by aloubry          ###   ########.fr       */
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
}	t_data;

typedef struct s_philo
{
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


// ft_itoa.c
char	*ft_itoa(int num);

#endif