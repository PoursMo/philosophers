/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:02:49 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/29 13:21:21 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *nptr)
{
	int	mult;
	int	num;

	mult = 1;
	while (*nptr && ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' '))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			mult = -1;
		nptr++;
	}
	num = 0;
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		num = num * 10 + (*nptr - 48);
		nptr++;
	}
	return (num * mult);
}

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
	data.time_start = get_time();
	sem_unlink("/stop_sem");
	data.stop_sem = sem_open("/stop", O_CREAT, 0);
	sem_unlink("/print_sem");
	data.print_sem = sem_open("/print", O_CREAT, 1);
	sem_unlink("/philo_forks");
	data.forks_sem = sem_open("/philo_forks", O_CREAT, data.nb_philo);
	return (data);
}

t_philo	*init_philosophers(t_data *data)
{
	int		i;
	t_philo	*philosophers;
	char sem_name[NAME_MAX - 4];
	char *itoa;

	philosophers = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].data = data;
		philosophers[i].last_meal = data->time_start;
		philosophers[i].eat_count = 0;
		itoa = ft_itoa(i);
		ft_strlcpy(sem_name, "/last_meal_", NAME_MAX - 4);
		ft_strlcat(sem_name, itoa, NAME_MAX - 4);
		sem_unlink(sem_name);
		philosophers[i].last_meal_sem = sem_open(sem_name, O_CREAT, 1);
		ft_strlcpy(sem_name, "/eat_count_", NAME_MAX - 4);
		ft_strlcat(sem_name, itoa, NAME_MAX - 4);
		sem_unlink(sem_name);
		philosophers[i].eat_count_sem = sem_open(sem_name, O_CREAT, 1);
		free(itoa);
		i++;
	}
	return (philosophers);
}
