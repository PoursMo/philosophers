/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:06 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/29 14:58:00 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocations(t_data *data, t_philo **philos, pid_t **processes)
{
	*philos = init_philosophers(data);
	if (!*philos)
		return (0);
	*processes = malloc(sizeof(pid_t) * data->nb_philo);
	if (!*processes)
	{
		free(*philos);
		return (0);
	}
	return (1);
}

void	launch_processes(pid_t *processes, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->nb_philo)
	{
		processes[i] = fork();
		if(processes[i] != 0)
		{
			if(processes[i] % 2 == 0)
			{
				ft_usleep(2000);
				printf("philo %d dead\n", philos[i].id);
				sem_post(philos[0].data->stop_sem);
			}
			else
			{
				while(1)
					printf("oui\n");
			}
			exit(0);
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
	pid_t			*philo_processes;
	// pthread_t		monitor_thread;

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
	printf("data.stop_sem: %p\n", (void *)data.stop_sem);
	printf("data.print_sem: %p\n", (void *)data.print_sem);
	if (!allocations(&data, &philosophers, &philo_processes))
		return (1);
	launch_processes(philo_processes, philosophers);
	sem_wait(data.stop_sem);
	kill(0, 1);
	wait_processes(philo_processes, data.nb_philo);
	// cleanup(&data, philosophers, forks, philo_threads);
	return (0);
}
