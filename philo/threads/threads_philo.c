/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:38:46 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/05 16:57:02 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_flag_died(t_philo *philo)
{
	pthread_mutex_lock(philo->flag_mutex);
	if (*philo->flag_died == 1)
		return (pthread_mutex_unlock(philo->flag_mutex), 1);
	pthread_mutex_unlock(philo->flag_mutex);
	return (0);
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 == 0)
		ft_usleep(1);

	while (check_flag_died(philo) == 0)
	{
		philo_eating(philo);
		if (check_flag_died(philo) == 1)
			break ;
		philo_sleeping(philo);
		if (check_flag_died(philo) == 1)
			break ;
		philo_thinking(philo);
	}
	return (NULL);
}

void	*ft_monitor(void *arg)
{
	t_prog_data	*data;

	data = (t_prog_data *)arg;

	while (1)
	{
		if ((if_any_died(data->philos, data->number_philos) == 1) || \
			if_all_eaten(data->philos, data->number_philos) == 1)
		{
			pthread_mutex_lock(&data->flag_mutex);
			data->flag_died = 1;
			pthread_mutex_unlock(&data->flag_mutex);
			break ;
		}
	}
	return (NULL);
}

int create_threads(t_prog_data data, t_philo *philos, int number)
{
	pthread_t	th_monitor;
	int			*result;

	if (pthread_create(&th_monitor, NULL, &ft_monitor, &data) != 0)
		return (1);
	for (int i = 0; i < number; i++)
	{
		if (pthread_create(&philos[i].id, NULL, &ft_philo, &data.philos[i]) != 0)
		{
			perror("Failed to create thread");
			return (i);
		}
	}
	if (pthread_join(th_monitor, NULL) != 0)
		return (2);
	for (int i = 0; i < number; i++)
	{
		if (pthread_join(data.philos[i].id, NULL) != 0)
		{
			perror("Failed to join thread");
			return (i);
		}
	}
	return (0);
}
