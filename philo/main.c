/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:06 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/22 14:35:13 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_data
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
	int 	time_start;
} t_data;

int	ft_atoi(const char *nptr)
{
	int	mult;
	int	num;

	mult = 1;
	while (*nptr && ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' '))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			mult = -1;
		nptr++;
	}
	num = 0;
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		num = num * 10 + (*nptr - 48);
		nptr++;
	}
	return (num * mult);
}

int get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

t_data parse_argv(int argc, char **argv)
{
	t_data	data;

	data.number_of_philosophers = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data.number_of_times_each_philosopher_must_eat = -1;
	data.time_start = get_time();
	return (data);
}

int get_timestamp(t_data data)
{
	return (get_time() - data.time_start);
}

 // eat > sleep > think > eat

void *philo_sleep(void *void_data)
{
	t_data data = *(t_data *)void_data;
	printf("%d %d is sleeping\n", get_timestamp(data), data.number_of_philosophers);
	usleep(data.time_to_sleep * 1000);
	// philo_think(data);
	return NULL;
}

void *philo_think(void *void_data)
{
	t_data data = *(t_data *)void_data;
	printf("%d %d is thinking\n", get_timestamp(data), data.number_of_philosophers);
	philo_sleep(void_data);
	// philo_eat(data);
	return NULL;
}

int main(int argc, char **argv)
{
	if(argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	t_data data = parse_argv(argc, argv);
	pthread_t *philosophers = malloc(sizeof(pthread_t) * data.number_of_philosophers);
	for (int i = 0; i < data.number_of_philosophers; i++)
	{
		pthread_create(&philosophers[i], NULL, philo_think, &data);
	}
	for (int i = 0; i < data.number_of_philosophers; i++)
	{
		pthread_join(philosophers[i], NULL);
	}
	free(philosophers);
}