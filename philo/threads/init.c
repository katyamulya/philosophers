/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:39:37 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/09 14:41:44 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philos_forks(int i, t_prog_data *data, pthread_mutex_t *forks)
{
	if (i == 0)
	{
		data->philos[i].left = &forks[i];
		data->philos[i].right = &forks[data->number_philos - 1];
	}
	else
	{
		data->philos[i].left = &forks[i];
		data->philos[i].right = &forks[i - 1];
	}
}

void	init_philos(t_philo *philos, t_prog_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		data->philos[i].num = i + 1;
		data->philos[i].t_die = data->t_die;
		data->philos[i].t_eat = data->t_eat;
		data->philos[i].t_sleep = data->t_sleep;
		data->philos[i].number_eat = data->number_eat;
		philos_forks(i, data, forks);
		gettimeofday(&data->philos[i].last_eat, 0);
		data->philos[i].start_prog = &data->start_prog;
		data->philos[i].print_mutex = &data->print_mutex;
		data->philos[i].flag_mutex = &data->flag_mutex;
		data->philos[i].flag_died = &data->flag_died;
		data->philos[i].eaten_mutex = &data->eaten_mutex;
		philos[i].total_eat = 0;
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
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	gettimeofday(&data->start_prog, NULL);
	if (argc == 6)
		data->number_eat = ft_atoi(argv[5]);
	else
	{
		if (data->number_philos == 1)
			data->number_eat = 1;
		else
			data->number_eat = -1;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->flag_mutex, NULL);
	pthread_mutex_init(&data->eaten_mutex, NULL);
	data->flag_died = 0;
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
