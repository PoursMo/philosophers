/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:06 by aloubry           #+#    #+#             */
/*   Updated: 2024/12/02 17:31:39 by aloubry          ###   ########.fr       */
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

	long long start = get_time() + 5;
	philos[0].data->time_start = start;
	i = 0;
	while (i < philos[0].data->nb_philo)
	{
		philos[i].last_meal = start;
		philos[0].data->philo_processes[i] = fork();
		if(philos[0].data->philo_processes[i] == 0)
		{
			while(get_time() < start)
				;
			pthread_create(&philos[i].philo_monitor, NULL, monitor_philo, (void *)(philos + i));
			philo_loop(philos + i);
		}
		i++;
	}
}

void	wait_all(pid_t *processes, int nb_philo, pthread_t stop_thread)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		printf("waiting for process %d\n", processes[i]);
		waitpid(processes[i], NULL, 0);
		i++;
	}
	printf("joining stop_thread\n");
	pthread_join(stop_thread, NULL);
}

void	cleanup(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		sem_close(philos[i].eat_count_sem);
		sem_close(philos[i].last_meal_sem);
		i++;
	}
	sem_close(data->stop_sem);
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	sem_close(data->full_philos_sem);
	free(philos);
	free(data->philo_processes);
}

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
	wait_all(data.philo_processes, data.nb_philo, stop_thread);
	if (data.nb_philo_eat != -1)
	{
		data.nb_philo_eat = -1;
		sem_post(data.full_philos_sem);
		printf("joining fullness_thread\n");
		pthread_join(fullness_thread, NULL);
	}
	printf("cleaning\n");
	cleanup(&data, philosophers);
	return (0);
}
