/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:42:28 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/27 15:47:17 by aloubry          ###   ########.fr       */
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
	sem_wait(*philo->left_fork);
	print_action(philo, "has taken a fork");
	if (philo->data->nb_philo == 1)
	{
		ft_usleep(philo->data->time_to_die);
		sem_post(*philo->left_fork);
		return ;
	}
	sem_post(*philo->right_fork);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_time();
	sem_post(philo->last_meal_sem);
	ft_usleep(philo->data->time_to_eat);
	sem_post(*philo->left_fork);
	sem_post(*philo->right_fork);
	sem_wait(philo->eat_count_sem);
	philo->eat_count++;
	sem_post(philo->eat_count_sem);
}

void	*philo_loop(void *void_data)
{
	t_philo	*philo;

	philo = (t_philo *)void_data;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_stop(philo->data))
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
