/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:19:10 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/11 17:17:06 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_philo_1(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo_thinking(philo);
	pthread_mutex_lock(philo->left);
	philo_print(philo, "has taken a fork");
	pthread_mutex_unlock(philo->left);
	return (NULL);
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo_thinking(philo);
	if (philo->num % 2 == 0)
		ft_usleep(10);
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
		if ((if_all_eaten(data->philos, data->number_philos) == 1) || \
			(if_any_died(data->philos, data->number_philos) == 1))
		{
			pthread_mutex_lock(&data->flag_mutex);
			data->flag_died = 1;
			pthread_mutex_unlock(&data->flag_mutex);
			break ;
		}
	}
	return (NULL);
}
