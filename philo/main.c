/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:06 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/23 14:10:12 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
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
	return (num * mult);
}

t_data parse_argv(int argc, char **argv)
{
	t_data	data;

	data.number_of_philosophers = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data.number_of_times_each_philosopher_must_eat = -1;
	data.time_start = get_time();
	return (data);
}

pthread_mutex_t *init_forks(int number_of_forks)
{
	pthread_mutex_t *forks = malloc(sizeof(pthread_mutex_t) * number_of_forks);
	if(!forks)
		return (NULL);
	int i = 0;
	while(i < number_of_forks)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo *init_philosophers(t_data *data, pthread_mutex_t *forks)
{
	int i;
	t_philo *philosophers;

	philosophers = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if(!philosophers)
		return (NULL);
	i = 0;
	while(i < data->number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].left_fork = &forks[i];
		if(i == data->number_of_philosophers - 1 && data->number_of_philosophers > 1)
			philosophers[i].right_fork = &forks[0];
		else if(i < data->number_of_philosophers - 1)
			philosophers[i].right_fork = &forks[i + 1];
		else
			philosophers[i].right_fork = NULL;
		philosophers[i].data = data;
		philosophers[i].last_meal = data->time_start;
		philosophers[i].eat_count = 0;
		i++;
	}
	return (philosophers);
}

int main(int argc, char **argv)
{
	if(argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}

	//setup
	t_data data = parse_argv(argc, argv);
	pthread_mutex_t *forks = init_forks(data.number_of_philosophers);
	if(!forks)
		return (1);
	t_philo *philosophers = init_philosophers(&data, forks);
	if(!philosophers)
	{
		free(forks);
		return (1);
	}
	
	//start
	pthread_t *philo_threads = malloc(sizeof(pthread_t) * data.number_of_philosophers);
	int i = 0;
	while(i < data.number_of_philosophers)
	{
		pthread_create(&philo_threads[i], NULL, philo_think, philosophers + i);
		i++;
	}
	i = 0;
	while(i < data.number_of_philosophers)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}

	//cleanup
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(philo_threads);
	free(philosophers);
	free(forks);
	return (0);
}