/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:38:25 by kdvarako          #+#    #+#             */
/*   Updated: 2024/08/26 17:28:35 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_prog_data *data, pthread_mutex_t *forks)
{
	int	i;

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->flag_mutex);
	pthread_mutex_destroy(&data->eaten_mutex);
	i = 0;
	while (i < data->number_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			philos[300];
	pthread_mutex_t	forks[300];
	t_prog_data		*data;
	int				i;

	data = NULL;
	i = 0;
	if (argc >= 5 && argc <= 6)
	{
		if (check_err(argc, argv) == 0)
		{
			data = init_data(argc, argv, philos);
			//printf("aftervinit number_philos = %d\n", data->number_philos);
			if (data != NULL)
			{
				/*printf("num = %d\n", data->number_philos);
				printf("time_to_die = %zu\n", data->t_die);
				printf("time_to_eat = %zu\n", data->t_eat);
				printf("time_to_sleep = %zu\n", data->t_sleep);
				printf("num_eat = %d\n", data->number_eat);
				printf("count_eat = %d\n", data->count_eaten);*/
				init_forks(forks, data->number_philos);
				init_philos(philos, data, forks);
				/*i = 0;
				while (i < data->number_philos)
				{
					printf("philos[%d]: %d\n", i, philos[i].num);
					i++;
				}*/
				/*if (create_threads(data, philos, data->number_philos) == 1)
					return (1);*/
				create_threads(*data, philos, data->number_philos);
				destroy_mutexes(data, forks);
			}
		}
	}
	else
	{
		printf("Error! Wrong amount of args\n");
		return (-1);
	}
	return (0);
}