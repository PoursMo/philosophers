/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:06 by aloubry           #+#    #+#             */
/*   Updated: 2024/12/01 20:50:40 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocations(t_data *data, t_philo **philos)
{
	*philos = init_philosophers(data);
	if (!*philos)
		return (0);
	data->philo_processes = malloc(sizeof(pid_t) * data->nb_philo);
	if (!data->philo_processes)
	{
		free(*philos);
		return (0);
	}
	return (1);
}

void	launch_processes(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->nb_philo)
	{
		philos[0].data->philo_processes[i] = fork();
		if(philos[0].data->philo_processes[i] == 0)
		{
			pthread_create(&philos[i].philo_monitor, NULL, monitor_philo, (void *)(philos + i));
			philo_loop(philos + i);
		}
		i++;
	}
}

void	wait_processes(pid_t *processes, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		waitpid(processes[i], NULL, 0);
		i++;
	}
}

// void	cleanup(t_data *data, t_philo *ps, pthread_mutex_t *fs, pthread_t *ts)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->nb_philo)
// 	{
// 		pthread_mutex_destroy(&fs[i]);
// 		pthread_mutex_destroy(&ps[i].last_meal_mutex);
// 		pthread_mutex_destroy(&ps[i].eat_count_mutex);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&data->stop_mutex);
// 	pthread_mutex_destroy(&data->print_mutex);
// 	free(fs);
// 	free(ps);
// 	free(ts);
// }

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philosophers;
	pthread_t		stop_thread;
	pthread_t		fullness_thread;

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
	if (!allocations(&data, &philosophers))
		return (1);
	pthread_create(&stop_thread, NULL, monitor_stop, &data);
	if (data.nb_philo_eat != -1)
		pthread_create(&fullness_thread, NULL, monitor_fulls, (void *)&data);
	launch_processes(philosophers);
	wait_processes(data.philo_processes, data.nb_philo);
	// cleanup(&data, philosophers, forks, philo_threads);
	return (0);
}
