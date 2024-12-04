/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:06 by aloubry           #+#    #+#             */
/*   Updated: 2024/12/04 14:58:55 by aloubry          ###   ########.fr       */
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

void	launch_all(t_philo *philos, pthread_t *stop_thread,
		pthread_t *fullness_thread)
{
	int			i;
	long long	start;

	pthread_create(stop_thread, NULL, monitor_stop, philos[0].data);
	if (philos[0].data->nb_philo_eat != -1)
		pthread_create(fullness_thread, NULL, monitor_fulls, philos[0].data);
	start = get_time() + 5;
	philos[0].data->time_start = start;
	i = 0;
	while (i < philos[0].data->nb_philo)
	{
		philos[i].last_meal = start;
		philos[0].data->philo_processes[i] = fork();
		if (philos[0].data->philo_processes[i] == 0)
		{
			while (get_time() < start)
				;
			pthread_create(&philos[i].philo_monitor,
				NULL, monitor_philo, (void *)(philos + i));
			philo_loop(philos + i);
		}
		i++;
	}
}

void	wait_all(t_data *data, pthread_t stop_thread, pthread_t fullness_thread)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		waitpid(data->philo_processes[i], NULL, 0);
		i++;
	}
	pthread_join(stop_thread, NULL);
	if (data->nb_philo_eat != -1)
	{
		data->nb_philo_eat = -1;
		sem_post(data->full_philos_sem);
		pthread_join(fullness_thread, NULL);
	}
}

void	cleanup(t_data *data, t_philo *philos)
{
	int		i;
	char	*itoa;
	char	sem_name[NAME_MAX - 4];

	i = 0;
	while (i < data->nb_philo)
	{
		itoa = ft_itoa(i);
		make_nb_sem_name(sem_name, "/last_meal_", itoa);
		clear_sem(sem_name, philos[i].last_meal_sem);
		make_nb_sem_name(sem_name, "/eat_count_", itoa);
		clear_sem(sem_name, philos[i].eat_count_sem);
		free(itoa);
		i++;
	}
	clear_sem("/stop", data->stop_sem);
	clear_sem("/philo_forks", data->forks_sem);
	clear_sem("/print", data->print_sem);
	clear_sem("/philo_full", data->full_philos_sem);
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
	launch_all(philosophers, &stop_thread, &fullness_thread);
	wait_all(&data, stop_thread, fullness_thread);
	cleanup(&data, philosophers);
	return (0);
}
