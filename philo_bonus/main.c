/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:06 by aloubry           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/29 13:02:49 by aloubry          ###   ########.fr       */
=======
/*   Updated: 2024/11/27 15:45:31 by aloubry          ###   ########.fr       */
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

<<<<<<< HEAD
int	allocations(t_data *dt, t_philo **ps, pthread_mutex_t **fs, pthread_t **ts)
{
=======
int	allocations(t_data *dt, t_philo **ps, sem_t ***fs, pid_t **ts)
{
	*fs = init_forks(dt->nb_philo);
	if (!*fs)
		return (0);
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
	*ps = init_philosophers(dt, *fs);
	if (!*ps)
	{
		free(*fs);
		return (0);
	}
<<<<<<< HEAD
	*ts = malloc(sizeof(pthread_t) * dt->nb_philo);
=======
	*ts = malloc(sizeof(pid_t) * dt->nb_philo);
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
	if (!*ts)
	{
		free(*fs);
		free(*ps);
		return (0);
	}
	return (1);
}

<<<<<<< HEAD
void	create_threads(pthread_t *threads, t_philo *philos, pthread_t *monitor)
=======
void	create_processes(pid_t *processes, t_philo *philos, pthread_t *monitor)
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
{
	int	i;

	i = 0;
	while (i < philos[0].data->nb_philo)
	{
<<<<<<< HEAD
		pthread_create(&threads[i], NULL, philo_loop, &philos[i]);
=======
		processes[i] = fork();
		if(processes[i])
		{
			philo_loop(&philos[i]);
			exit(0);
		}
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
		i++;
	}
	pthread_create(monitor, NULL, monitor_philos, philos);
}

<<<<<<< HEAD
void	join_threads(pthread_t *threads, int nb_philo, pthread_t monitor)
=======
void	join_threads(pid_t *processes, int nb_philo, pthread_t monitor)
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
<<<<<<< HEAD
		pthread_join(threads[i], NULL);
=======
		waitpid(processes[i], NULL, 0);
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
		i++;
	}
	pthread_join(monitor, NULL);
}

<<<<<<< HEAD
void	cleanup(t_data *data, t_philo *ps, pthread_mutex_t *fs, pthread_t *ts)
{
	int	i;
=======
void	cleanup(t_data *data, t_philo *ps, sem_t **fs, pid_t *ts)
{
	int	i;
	char *itoa;
	char *sem_name;
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2

	i = 0;
	while (i < data->nb_philo)
	{
<<<<<<< HEAD
		pthread_mutex_destroy(&fs[i]);
		pthread_mutex_destroy(&ps[i].last_meal_mutex);
		pthread_mutex_destroy(&ps[i].eat_count_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->print_mutex);
=======
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
	sem_unlink("stop_sem");
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
	free(fs);
	free(ps);
	free(ts);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philosophers;
<<<<<<< HEAD
	pthread_t		*philo_threads;
=======
	sem_t	**forks;
	pid_t		*philo_pids;
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
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
<<<<<<< HEAD
	if (!allocations(&data, &philosophers, &forks, &philo_threads))
		return (1);
	create_threads(philo_threads, philosophers, &monitor_thread);
	join_threads(philo_threads, data.nb_philo, monitor_thread);
	cleanup(&data, philosophers, forks, philo_threads);
=======
	if (!allocations(&data, &philosophers, &forks, &philo_pids))
		return (1);
	create_processes(philo_pids, philosophers, &monitor_thread);
	join_threads(philo_pids, data.nb_philo, monitor_thread);
	cleanup(&data, philosophers, forks, philo_pids);
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
	return (0);
}
