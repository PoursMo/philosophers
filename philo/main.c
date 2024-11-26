/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:06 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/26 15:26:24 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor(void *void_data)
{
	int i;

	t_philo *philosophers = (t_philo *)void_data;
	while (1)
	{
		i = 0;
		while (i < philosophers[0].data->number_of_philosophers)
		{
			pthread_mutex_lock(&philosophers[i].last_meal_mutex);
			if (get_time() - philosophers[i].last_meal >= philosophers[i].data->time_to_die)
			{
				pthread_mutex_unlock(&philosophers[i].last_meal_mutex);
				print_action(philosophers + i, "died");
				pthread_mutex_lock(&philosophers[0].data->stop_mutex);
				philosophers[0].data->stop = 1;
				pthread_mutex_unlock(&philosophers[0].data->stop_mutex);
				return NULL;
			}
			pthread_mutex_unlock(&philosophers[i].last_meal_mutex);
			i++;
		}
		if (philosophers[0].data->number_of_times_each_philosopher_must_eat != -1)
		{
			i = 0;
			while (i < philosophers[0].data->number_of_philosophers)
			{
				pthread_mutex_lock(&philosophers[i].eat_count_mutex);
				if (philosophers[i].eat_count < philosophers[0].data->number_of_times_each_philosopher_must_eat)
				{
					pthread_mutex_unlock(&philosophers[i].eat_count_mutex);
					break ;
				}
				pthread_mutex_unlock(&philosophers[i].eat_count_mutex);
				i++;
			}
			if (i == philosophers[0].data->number_of_philosophers)
			{
				pthread_mutex_lock(&philosophers[0].data->stop_mutex);
				philosophers[0].data->stop = 1;
				pthread_mutex_unlock(&philosophers[0].data->stop_mutex);
				return NULL;
			}
		}
	}
}

int main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}

	//setup
	t_data data = init_data(argc, argv);
	if (!data.number_of_philosophers || !data.time_to_die || !data.time_to_eat || !data.time_to_sleep || (argc == 6 && !data.number_of_times_each_philosopher_must_eat))
		return (1);
	pthread_mutex_t *forks = init_forks(data.number_of_philosophers);
	if (!forks)
		return (1);
	t_philo *philosophers = init_philosophers(&data, forks);
	if (!philosophers)
	{
		free(forks);
		return (1);
	}
	
	//start
	pthread_t *philo_threads = malloc(sizeof(pthread_t) * data.number_of_philosophers);
	pthread_t monitor_thread;
	int i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_create(&philo_threads[i], NULL, philo_loop, philosophers + i);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor, philosophers);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);

	//cleanup
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philosophers[i].last_meal_mutex);
		pthread_mutex_destroy(&philosophers[i].eat_count_mutex);
		i++;
	}
	pthread_mutex_destroy(&data.stop_mutex);
	free(philo_threads);
	free(philosophers);
	free(forks);
	return (0);
}