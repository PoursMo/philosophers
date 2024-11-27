/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:57:15 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/27 13:46:57 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->nb_philo)
	{
		sem_wait(philos[i].last_meal_sem);
		if (get_time() - philos[i].last_meal >= philos[i].data->time_to_die)
		{
			sem_post(philos[i].last_meal_sem);
			print_action(philos + i, "died");
			sem_wait(philos[0].data->stop_sem);
			philos[0].data->stop = 1;
			sem_post(philos[0].data->stop_sem);
			return (1);
		}
		sem_post(philos[i].last_meal_sem);
		i++;
	}
	return (0);
}

static int	check_eats(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->nb_philo)
	{
		sem_wait(philos[i].eat_count_sem);
		if (philos[i].eat_count < philos[0].data->nb_philo_eat)
		{
			sem_post(philos[i].eat_count_sem);
			break ;
		}
		sem_post(philos[i].eat_count_sem);
		i++;
	}
	if (i == philos[0].data->nb_philo)
	{
		sem_wait(philos[0].data->stop_sem);
		philos[0].data->stop = 1;
		sem_post(philos[0].data->stop_sem);
		return (1);
	}
	return (0);
}

void	*monitor_philos(void *void_data)
{
	t_philo	*philos;

	philos = (t_philo *)void_data;
	while (1)
	{
		if (check_death(philos)
			|| (philos[0].data->nb_philo_eat != -1 && check_eats(philos)))
			return (NULL);
	}
}
