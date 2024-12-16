/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:42:28 by aloubry           #+#    #+#             */
/*   Updated: 2024/12/16 17:21:09 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

static void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

static void	philo_eat(t_philo *philo)
{
	sem_wait(philo->data->forks_sem);
	print_action(philo, "has taken a fork");
	if (philo->data->nb_philo == 1)
	{
		ft_usleep(philo->data->time_to_die);
		sem_post(philo->data->forks_sem);
		return ;
	}
	sem_wait(philo->data->forks_sem);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_time();
	sem_post(philo->last_meal_sem);
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
	sem_wait(philo->eat_count_sem);
	philo->eat_count++;
	sem_post(philo->eat_count_sem);
}

void	philo_loop(t_philo *philo)
{
	while (1)
	{
		philo_think(philo);
		usleep(500);
		philo_eat(philo);
		philo_sleep(philo);
	}
}
