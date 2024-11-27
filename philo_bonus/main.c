/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:06 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/27 14:08:45 by aloubry          ###   ########.fr       */
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
	while (i < philos[0].data->nb_philo)
	{
		pthread_create(&threads[i], NULL, philo_loop, &philos[i]);
		i++;
	}
	pthread_create(monitor, NULL, monitor_philos, philos);
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

void	cleanup(t_data *data, t_philo *ps, sem_t **fs, pthread_t *ts)
{
	int	i;
	char *itoa;
	char *sem_name;

	i = 0;
	while (i < data->nb_philo)
	{
		itoa = ft_itoa(i);
		sem_close(fs[i]);
		sem_name = ft_strjoin("philo_fork_", itoa);
		sem_unlink(sem_name);
		free(sem_name);
		sem_close(ps[i].last_meal_sem);
		sem_name = ft_strjoin("last_meal_", itoa);
		sem_unlink(sem_name);
		free(sem_name);
		sem_close(ps[i].eat_count_sem);
		sem_name = ft_strjoin("eat_count_", itoa);
		free(itoa);
		sem_unlink(sem_name);
		free(sem_name);
		i++;
	}
	sem_close(data->stop_sem);
	sem_unlink("stop_sem");
	sem_close(data->print_sem);
	free(fs);
	free(ps);
	free(ts);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philosophers;
	sem_t	**forks;
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
	if (!allocations(&data, &philosophers, &forks, &philo_threads))
		return (1);
	create_threads(philo_threads, philosophers, &monitor_thread);
	join_threads(philo_threads, data.nb_philo, monitor_thread);
	cleanup(&data, philosophers, forks, philo_threads);
	return (0);
}
