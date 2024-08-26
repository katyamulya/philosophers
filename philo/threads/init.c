/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:39:37 by kdvarako          #+#    #+#             */
/*   Updated: 2024/08/26 17:28:42 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philos(t_philo *philos, t_prog_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		philos[i].num = i + 1;
		philos[i].t_die = data->t_die;
		philos[i].t_eat = data->t_eat;
		philos[i].t_sleep = data->t_sleep;
		philos[i].number_eat = data->number_eat;
		philos[i].count_eaten = 0;
		//philo[i]->must_die = 0;
		if (i == data->number_philos - 1)
		{
			philos[i].left = &forks[0];
			philos[i].right = &forks[i];
		}
		else
		{
			philos[i].left = &forks[i];
			philos[i].right = &forks[i + 1];
		}
		philos[i].print_mutex = &data->print_mutex;
		philos[i].flag_mutex = &data->flag_mutex;
		philos[i].flag_died = &data->flag_died;
		philos[i].eaten_mutex = &data->eaten_mutex;
		philos[i].count_eaten = &data->count_eaten;
		//printf("philo_count_eat = %d\n", *philos[i].count_eaten);
		i++;
	}
}

t_prog_data	*init_data(int argc, char **argv, t_philo *philos)
{
	t_prog_data	*data;

	data = (t_prog_data *)malloc(sizeof(t_prog_data));
	if (!data)
		return (NULL);
	data->number_philos = ft_atoi(argv[1]);
	data->philos = philos;
	data->t_die = ft_atoi(argv[2]) * 1000;
	data->t_eat = ft_atoi(argv[3]) * 1000;
	data->t_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		data->number_eat = ft_atoi(argv[5]);
	else
		data->number_eat = 1;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->flag_mutex, NULL);
	pthread_mutex_init(&data->eaten_mutex, NULL);
	data->flag_died = 0;
	data->count_eaten = 0;
	return (data);
}

void	init_forks(pthread_mutex_t *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
