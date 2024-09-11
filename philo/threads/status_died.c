/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_died.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:55:51 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/11 11:11:09 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_died(t_philo *philo)
{
	struct timeval	current;

	pthread_mutex_lock(philo->eaten_mutex);
	gettimeofday(&current, NULL);
	//>= || >?
	if (convert_ms(current) - convert_ms(philo->last_eat) > philo->t_die)
		return (pthread_mutex_unlock(philo->eaten_mutex), 1);
	pthread_mutex_unlock(philo->eaten_mutex);
	return (0);
}

int	if_any_died(t_philo *philos, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (is_died(&philos[i]) == 1)
		{
			pthread_mutex_lock(philos[i].flag_mutex);
			*philos[i].flag_died = 1;
			pthread_mutex_unlock(philos[i].flag_mutex);
			philo_print(&philos[i], " died");
			return (1);
		}
		i++;
	}
	return (0);
}
