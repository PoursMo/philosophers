/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:06 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/26 21:34:44 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_usage(char *program)
{
	printf("Usage: %s ", program);
	printf("number_of_philosopher ");
	printf("time_to_die ");
	printf("time_to_eat ");
	printf("time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
}

void	create_threads(pthread_t *threads, t_philo *philos, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < philos[0].data->nb_philo)
	{
		pthread_create(&threads[i], NULL, philo_loop, &philos[i]);
		i++;
	}
	pthread_create(monitor, NULL, monitor, philos);
}

void	join_threads(pthread_t *threads, int nb_philo, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

void	cleanup(t_data *data, t_philo *philos, pthread_mutex_t *forks, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].last_meal_mutex);
		pthread_mutex_destroy(&philos[i].eat_count_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free(forks);
	free(philos);
	free(threads);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	pthread_t		*philo_threads;
	pthread_t		monitor_thread;

	if (argc < 5 || argc > 6)
	{
		print_usage(argv[0]);
		return (1);
	}
	data = parse_and_init_data(argc, argv);
	if (!data.nb_philo || !data.time_to_die || !data.time_to_eat
		|| !data.time_to_sleep || (argc == 6 && !data.nb_philo_eat))
	{
		print_usage(argv[0]);
		return (1);
	}
	forks = init_forks(data.nb_philo);
	if (!forks)
		return (1);
	philosophers = init_philosophers(&data, forks);
	if (!philosophers)
	{
		free(forks);
		return (1);
	}
	philo_threads = malloc(sizeof(pthread_t) * data.nb_philo);
	if (!philo_threads)
	{
		free(forks);
		free(philosophers);
		return (1);
	}
	create_threads(philo_threads, philosophers, &monitor_thread);
	join_threads(philo_threads, data.nb_philo, monitor_thread);
	cleanup(&data, philosophers, forks, philo_threads);
	return (0);
}
