/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:42:28 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/24 14:05:44 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// eat > sleep > think > eat
//fork: 0 = taken, 1 = free

void philo_take_left_fork(void *void_data)
{
	t_philo *philo = (t_philo *)void_data;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if(philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	printf("%05lld %d has taken a fork\n", get_timestamp(philo->data->time_start), philo->id);
}

void philo_take_right_fork(void *void_data)
{
	t_philo *philo = (t_philo *)void_data;
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if(philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	printf("%05lld %d has taken a fork\n", get_timestamp(philo->data->time_start), philo->id);
}

void philo_eat(void *void_data)
{
	t_philo *philo = (t_philo *)void_data;
	pthread_mutex_lock(&philo->data->stop_mutex);
	if(philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	printf("%05lld %d is eating\n", get_timestamp(philo->data->time_start), philo->id);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo_sleep(void_data);
}

void *philo_think(void *void_data)
{
	t_philo *philo = (t_philo *)void_data;
	pthread_mutex_lock(&philo->data->stop_mutex);
	if(philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return NULL;
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	printf("%05lld %d is thinking\n", get_timestamp(philo->data->time_start), philo->id);
	if(philo->id % 2 == 0)
	{
		philo_take_right_fork(void_data);
		philo_take_left_fork(void_data);
	}
	else
	{
		philo_take_left_fork(void_data);
		philo_take_right_fork(void_data);
	}
	philo_eat(void_data);
	return NULL;
}

void *philo_sleep(void *void_data)
{
	t_philo *philo = (t_philo *)void_data;
	pthread_mutex_lock(&philo->data->stop_mutex);
	if(philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return NULL;
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	printf("%05lld %d is sleeping\n", get_timestamp(philo->data->time_start), philo->id);
	usleep(philo->data->time_to_sleep * 1000);
	philo_think(void_data);
	return NULL;
}