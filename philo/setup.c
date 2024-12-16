/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:02:49 by aloubry           #+#    #+#             */
/*   Updated: 2024/12/16 16:42:56 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *nptr)
{
	int	mult;
	int	num;

	mult = 1;
	while (*nptr && ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' '))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			mult = -1;
		nptr++;
	}
	num = 0;
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		num = num * 10 + (*nptr - 48);
		nptr++;
	}
	if (*nptr && !(*nptr >= '0' && *nptr <= '9'))
		return (0);
	return (num * mult);
}

t_data	parse_and_init_data(int argc, char **argv)
{
	t_data	data;

	data.nb_philo = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.nb_philo_eat = ft_atoi(argv[5]);
	else
		data.nb_philo_eat = -1;
	data.time_start = get_time();
	data.stop = 0;
	pthread_mutex_init(&data.stop_mutex, NULL);
	pthread_mutex_init(&data.print_mutex, NULL);
	return (data);
}

pthread_mutex_t	*init_forks(int number_of_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * number_of_forks);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < number_of_forks)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo	*init_philosophers(t_data *data, pthread_mutex_t *forks)
{
	int		i;
	t_philo	*philosophers;

	philosophers = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].left_fork = &forks[i];
		if (i == data->nb_philo - 1 && data->nb_philo > 1)
			philosophers[i].right_fork = &forks[0];
		else if (i < data->nb_philo - 1)
			philosophers[i].right_fork = &forks[i + 1];
		else
			philosophers[i].right_fork = NULL;
		philosophers[i].data = data;
		philosophers[i].last_meal = data->time_start;
		philosophers[i].eat_count = 0;
		pthread_mutex_init(&philosophers[i].last_meal_mutex, NULL);
		pthread_mutex_init(&philosophers[i].eat_count_mutex, NULL);
		i++;
	}
	return (philosophers);
}
