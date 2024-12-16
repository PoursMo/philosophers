/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:06 by aloubry           #+#    #+#             */
/*   Updated: 2024/12/16 17:20:12 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocations(t_data *dt, t_philo **ps, pthread_mutex_t **fs, pthread_t **ts)
{
	*fs = init_forks(dt->nb_philo);
	if (!*fs)
		return (0);
	*ps = init_philosophers(dt, *fs);
	if (!*ps)
	{
		free(*fs);
		return (0);
	}
	*ts = malloc(sizeof(pthread_t) * dt->nb_philo);
	if (!*ts)
	{
		free(*fs);
		free(*ps);
		return (0);
	}
	return (1);
}

void	create_threads(pthread_t *threads, t_philo *philos, pthread_t *monitor)
{
	int	i;

	i = 0;
	pthread_create(monitor, NULL, monitor_philos, philos);
	while (i < philos[0].data->nb_philo)
	{
		pthread_create(&threads[i], NULL, philo_loop, &philos[i]);
		i++;
	}
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

void	cleanup(t_data *data, t_philo *ps, pthread_mutex_t *fs, pthread_t *ts)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&fs[i]);
		pthread_mutex_destroy(&ps[i].last_meal_mutex);
		pthread_mutex_destroy(&ps[i].eat_count_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free(fs);
	free(ps);
	free(ts);
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
	if (data.nb_philo <= 0 || data.time_to_die <= 0 || data.time_to_eat <= 0
		|| data.time_to_sleep <= 0 || (argc == 6 && data.nb_philo_eat <= 0))
	{
		print_usage(argv[0]);
		return (1);
	}
	if (!allocations(&data, &philosophers, &forks, &philo_threads))
		return (1);
	create_threads(philo_threads, philosophers, &monitor_thread);
	join_threads(philo_threads, data.nb_philo, monitor_thread);
	cleanup(&data, philosophers, forks, philo_threads);
	return (0);
}
