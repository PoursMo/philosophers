/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:57:15 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/26 20:13:27 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->nb_philo)
	{
		pthread_mutex_lock(&philos[i].last_meal_mutex);
		if (get_time() - philos[i].last_meal >= philos[i].data->time_to_die)
		{
			pthread_mutex_unlock(&philos[i].last_meal_mutex);
			print_action(philos + i, "died");
			pthread_mutex_lock(&philos[0].data->stop_mutex);
			philos[0].data->stop = 1;
			pthread_mutex_unlock(&philos[0].data->stop_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philos[i].last_meal_mutex);
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
		pthread_mutex_lock(&philos[i].eat_count_mutex);
		if (philos[i].eat_count < philos[0].data->nb_philo_eat)
		{
			pthread_mutex_unlock(&philos[i].eat_count_mutex);
			break ;
		}
		pthread_mutex_unlock(&philos[i].eat_count_mutex);
		i++;
	}
	if (i == philos[0].data->nb_philo)
	{
		pthread_mutex_lock(&philos[0].data->stop_mutex);
		philos[0].data->stop = 1;
		pthread_mutex_unlock(&philos[0].data->stop_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *void_data)
{
	t_philo	*philos;

	philos = (t_philo *)void_data;
	while (1)
	{
		if (check_death(philos) || (philos[0].data->nb_philo_eat != -1 && check_eats(philos)))
			return (NULL);
	}
}
