/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:58:06 by aloubry           #+#    #+#             */
/*   Updated: 2024/11/22 17:31:11 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_data
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	long long	time_start;
} t_data;

typedef struct s_philo
{
	int		id;
	char 	*right_fork;
	char 	*left_fork;
	t_data 	*data;
} t_philo;



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

long long get_time()
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

long long get_timestamp(long long time_start)
{
	return (get_time() - time_start);
}

//0 = taken, 1 = free
void take_fork()
{

}

 // eat > sleep > think > eat

void *philo_think(void *void_data)
{
	t_philo philo = *(t_philo *)void_data;
	printf("%05lld %d is thinking\n", get_timestamp(philo.data->time_start), philo.id);
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


t_philo *init_philosophers(t_data *data, char *forks)
{
	int i;
	t_philo *philosophers;

	philosophers = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if(!philosophers)
		return (NULL);
	i = 0;
	while(i < data->number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].left_fork = &forks[i];
		if(i == data->number_of_philosophers - 1 && data->number_of_philosophers > 1)
			philosophers[i].right_fork = &forks[0];
		else if(i < data->number_of_philosophers - 1)
			philosophers[i].right_fork = &forks[i + 1];
		else
			philosophers[i].right_fork = NULL;
		philosophers[i].data = data;
		i++;
	}
	return (philosophers);
}

int main(int argc, char **argv)
{
	if(argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}

	//setup
	t_data data = parse_argv(argc, argv);
	char *forks = malloc(sizeof(char) * data.number_of_philosophers);
	if(!forks)
		return (1);
	memset(forks, 1, data.number_of_philosophers);
	t_philo *philosophers = init_philosophers(&data, forks);
	if(!philosophers)
	{
		free(forks);
		return (1);
	}
	
	//start
	pthread_t *philo_threads = malloc(sizeof(pthread_t) * data.number_of_philosophers);
	int i = 0;
	while(i < data.number_of_philosophers)
	{
		pthread_create(&philo_threads[i], NULL, philo_sleep, philosophers + i);
		i++;
	}
	i = 0;
	while(i < data.number_of_philosophers)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}
	free(philo_threads);
	free(philosophers);
	free(forks);
	return (0);
}