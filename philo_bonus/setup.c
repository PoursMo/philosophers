/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:02:49 by aloubry           #+#    #+#             */
/*   Updated: 2024/12/04 13:24:09 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	parse_and_init_data(int argc, char **argv)
{
	t_data	data;

	data.nb_philo = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.nb_philo_eat = ft_atoi(argv[5]);
	else
		data.nb_philo_eat = -1;
	sem_unlink("/stop");
	data.stop_sem = sem_open("/stop", O_CREAT, 0644, 0);
	sem_unlink("/print");
	data.print_sem = sem_open("/print", O_CREAT, 0644, 1);
	sem_unlink("/philo_forks");
	data.forks_sem = sem_open("/philo_forks", O_CREAT, 0644, data.nb_philo);
	sem_unlink("/philo_full");
	data.full_philos_sem = sem_open("/philo_full", O_CREAT, 0644, 0);
	return (data);
}

t_philo	*init_philosophers(t_data *data)
{
	int		i;
	t_philo	*philosophers;
	char	sem_name[NAME_MAX - 4];
	char	*itoa;

	philosophers = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].data = data;
		philosophers[i].eat_count = 0;
		itoa = ft_itoa(i);
		make_nb_sem_name(sem_name, "/last_meal_", itoa);
		sem_unlink(sem_name);
		philosophers[i].last_meal_sem = sem_open(sem_name, O_CREAT, 0644, 1);
		make_nb_sem_name(sem_name, "/eat_count_", itoa);
		sem_unlink(sem_name);
		philosophers[i].eat_count_sem = sem_open(sem_name, O_CREAT, 0644, 1);
		free(itoa);
		i++;
	}
	return (philosophers);
}
