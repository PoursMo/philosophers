/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:17:13 by aloubry           #+#    #+#             */
/*   Updated: 2024/12/04 14:45:03 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	long long	timestamp;

	sem_wait(philo->data->print_sem);
	timestamp = get_timestamp(philo->data->time_start);
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

void	make_nb_sem_name(char *sem_name, const char *name, const char *nb)
{
	ft_strlcpy(sem_name, name, NAME_MAX - 4);
	ft_strlcat(sem_name, nb, NAME_MAX - 4);
}

void	clear_sem(char *sem_name, sem_t *sem_ptr)
{
	sem_close(sem_ptr);
	sem_unlink(sem_name);
}
