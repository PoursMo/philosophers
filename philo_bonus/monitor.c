/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:57:15 by aloubry           #+#    #+#             */
/*   Updated: 2024/12/02 17:29:43 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_death(t_philo philo)
{
	sem_wait(philo.last_meal_sem);
	if (get_time() - philo.last_meal >= philo.data->time_to_die)
	{
		sem_wait(philo.data->print_sem);
		printf("%05lld %d died\n", get_timestamp(philo.data->time_start), philo.id);
		sem_post(philo.data->stop_sem);
	}
	sem_post(philo.last_meal_sem);
}

static void	check_fullness(t_philo philo)
{
	static int is_full;

	if(!is_full)
	{
		sem_wait(philo.eat_count_sem);
		if (philo.eat_count >= philo.data->nb_philo_eat)
		{
			is_full = 1;
			sem_post(philo.data->full_philos_sem);
		}
		sem_post(philo.eat_count_sem);
	}
}

void	*monitor_philo(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (1)
	{
		check_death(*philo);
		check_fullness(*philo);
	}
	return (NULL);
}

void *monitor_stop(void *void_data)
{
	t_data *data;
	int i;

	data = (t_data *)void_data;
	sem_wait(data->stop_sem);
	i = 0;
	while(i < data->nb_philo)
	{
		kill(data->philo_processes[i], SIGTERM);
		i++;
	}
	return (NULL);
}

void *monitor_fulls(void *void_data)
{
	int count;
	t_data *data;

	count = 0;
	data = (t_data *)void_data;
	while(data->nb_philo_eat != -1)
	{
		sem_wait(data->full_philos_sem);
		count++;
		if(count >= data->nb_philo)
		{
			sem_post(data->stop_sem);
			return (NULL);
		}
	}
	return (NULL);
}