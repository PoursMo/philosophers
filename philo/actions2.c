/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:17:13 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/26 16:52:23 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

void	print_action(t_philo *philo, char *action)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_timestamp(philo->data->time_start);
	if (!is_stop(philo->data))
		printf("%05lld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
