/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:38:25 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/09 15:26:05 by kdvarako         ###   ########.fr       */
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

	data = NULL;
	if (argc >= 5 && argc <= 6 && check_err(argc, argv) == 0)
	{
		data = init_data(argc, argv, philos);
		if (data != NULL)
		{
			init_forks(forks, data->number_philos);
			init_philos(philos, data, forks);
			start_threads(*data, philos, data->number_philos);
			destroy_mutexes(data, forks);
		}
	}
	else
	{
		printf("Error! Incorrectly entered data.\n");
		return (-1);
	}
	return (0);
}
