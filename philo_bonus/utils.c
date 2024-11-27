/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:17:13 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/27 13:37:07 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_stop(t_data *data)
{
	int	stop;

	sem_wait(data->stop_sem);
	stop = data->stop;
	sem_post(data->stop_sem);
	return (stop);
}

void	print_action(t_philo *philo, char *action)
{
	long long	timestamp;

	sem_wait(philo->data->print_sem);
	timestamp = get_timestamp(philo->data->time_start);
	if (!is_stop(philo->data))
		printf("%05lld %d %s\n", timestamp, philo->id, action);
	sem_post(philo->data->print_sem);
}

void	print_usage(char *program)
{
	printf("Usage: %s ", program);
	printf("number_of_philosopher ");
	printf("time_to_die ");
	printf("time_to_eat ");
	printf("time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
}
