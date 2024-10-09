/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:38:46 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/09 15:19:49 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_threads(pthread_t *th_monitor, t_prog_data *data, \
	t_philo *philos, int number)
{
	int	i;

	if (pthread_create(th_monitor, NULL, &ft_monitor, data) != 0)
		return (1);
	if (data->number_philos == 1)
	{
		if (pthread_create(&philos[0].id, NULL, \
			&ft_philo_1, &data->philos[0]) != 0)
			return (1);
	}
	else
	{
		i = 0;
		while (i < number)
		{
			if (pthread_create(&philos[i].id, NULL, \
				&ft_philo, &data->philos[i]) != 0)
				return (1);
			i++;
		}
	}
	return (0);
}

int	join_threads(pthread_t	*th_monitor, t_prog_data *data, int number)
{
	int	i;

	if (pthread_join(*th_monitor, NULL) != 0)
		return (1);
	if (data->number_philos == 1)
	{
		if (pthread_join(data->philos[0].id, NULL) != 0)
			return (1);
	}
	else
	{
		i = 0;
		while (i < number)
		{
			if (pthread_join(data->philos[i].id, NULL) != 0)
				return (1);
			i++;
		}
	}
	return (0);
}

int	start_threads(t_prog_data data, t_philo *philos, int number)
{
	pthread_t	th_monitor;
	int			*result;
	int			i;

	if (create_threads(&th_monitor, &data, philos, number) == 1)
	{
		printf("Failed to create threads");
		return (1);
	}
	if (join_threads(&th_monitor, &data, number) == 1)
	{
		printf("Failed to join threads");
		return (1);
	}
	return (0);
}
