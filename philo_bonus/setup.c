/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:02:49 by aloubry           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/29 13:09:22 by aloubry          ###   ########.fr       */
=======
/*   Updated: 2024/11/27 14:02:13 by aloubry          ###   ########.fr       */
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
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
<<<<<<< HEAD
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
=======
	data.stop = 0;
	sem_unlink("stop_sem");
	data.stop_sem = sem_open("stop_sem", O_CREAT, 0644, 1);
	sem_unlink("print_sem");
	data.print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	return (data);
}



sem_t	**init_forks(int number_of_forks)
{
	sem_t	**forks;
	char *sem_name;
	char *itoa;
	int				i;

	forks = malloc(sizeof(sem_t *) * number_of_forks);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < number_of_forks)
	{
		itoa = ft_itoa(i);
		sem_name = ft_strjoin("philo_fork_", itoa);
		free(itoa);
		sem_unlink(sem_name);
		forks[i] = sem_open(sem_name, O_CREAT, 0644, 1);
		free(sem_name);
		i++;
	}
	return (forks);
}

t_philo	*init_philosophers(t_data *data, sem_t **forks)
{
	int		i;
	t_philo	*philosophers;
	char *itoa;
	char *sem_name;
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2

	philosophers = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philosophers[i].id = i + 1;
<<<<<<< HEAD
=======
		philosophers[i].left_fork = &forks[i];
		if (i == data->nb_philo - 1 && data->nb_philo > 1)
			philosophers[i].right_fork = &forks[0];
		else if (i < data->nb_philo - 1)
			philosophers[i].right_fork = &forks[i + 1];
		else
			philosophers[i].right_fork = NULL;
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
		philosophers[i].data = data;
		philosophers[i].last_meal = data->time_start;
		philosophers[i].eat_count = 0;
		itoa = ft_itoa(i);
<<<<<<< HEAD
		ft_strlcpy(sem_name, "/last_meal_", NAME_MAX - 4);
		ft_strlcat(sem_name, itoa, NAME_MAX - 4);
		sem_unlink(sem_name);
		philosophers[i].last_meal_sem = sem_open(sem_name, O_CREAT, 1);
		ft_strlcpy(sem_name, "/eat_count_", NAME_MAX - 4);
		ft_strlcat(sem_name, itoa, NAME_MAX - 4);
		sem_unlink(sem_name);
		philosophers[i].eat_count_sem = sem_open(sem_name, O_CREAT, 1);
		free(itoa);
=======
		sem_name = ft_strjoin("last_meal_", itoa);
		sem_unlink(sem_name);
		philosophers[i].last_meal_sem = sem_open(sem_name, O_CREAT, 0644, 1);
		free(sem_name);
		sem_name = ft_strjoin("eat_count_", itoa);
		free(itoa);
		sem_unlink(sem_name);
		philosophers[i].last_meal_sem = sem_open(sem_name, O_CREAT, 0644, 1);
		free(sem_name);
>>>>>>> fb68f8d3794aae15e24533301de9e451f61966f2
		i++;
	}
	return (philosophers);
}
