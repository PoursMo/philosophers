/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:42:28 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/22 18:35:50 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// eat > sleep > think > eat
//fork: 0 = taken, 1 = free

void *philo_take_left_fork(void *void_data);
void *philo_take_right_fork(void *void_data);
void *philo_eat(void *void_data);
void *philo_think(void *void_data);
void *philo_sleep(void *void_data);

void *philo_take_left_fork(void *void_data)
{
	t_philo *philo = (t_philo *)void_data;
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->status = 0;
	printf("%05lld %d has taken a fork\n", get_timestamp(philo->data->time_start), philo->id);
	return NULL;
}

void *philo_take_right_fork(void *void_data)
{
	t_philo *philo = (t_philo *)void_data;
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->status = 0;
	printf("%05lld %d has taken a fork\n", get_timestamp(philo->data->time_start), philo->id);
	return NULL;
}

void *philo_eat(void *void_data)
{
	t_philo philo = *(t_philo *)void_data;
	printf("%05lld %d is eating\n", get_timestamp(philo.data->time_start), philo.id);
	usleep(philo.data->time_to_eat * 1000);
	philo.left_fork->status = 1;
	pthread_mutex_unlock(&philo.left_fork->mutex);
	philo.right_fork->status = 1;
	pthread_mutex_unlock(&philo.right_fork->mutex);
	philo_sleep(void_data);
	return NULL;
}

void *philo_think(void *void_data)
{
	t_philo philo = *(t_philo *)void_data;
	printf("%05lld %d is thinking\n", get_timestamp(philo.data->time_start), philo.id);
	philo_take_left_fork(void_data);
	philo_take_right_fork(void_data);
	philo_eat(void_data);
	return NULL;
}

void *philo_sleep(void *void_data)
{
	t_philo philo = *(t_philo *)void_data;
	printf("%05lld %d is sleeping\n", get_timestamp(philo.data->time_start), philo.id);
	usleep(philo.data->time_to_sleep * 1000);
	philo_think(void_data);
	return NULL;
}