/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_eaten.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:26:26 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/08 17:56:04 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	if_all_eaten(t_philo *philos, int num_philos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (num_philos != 1 && philos[0].number_eat == -1)
		return (0);
	while (i < num_philos)
	{
		pthread_mutex_lock(philos[i].eaten_mutex);
		if (philos[i].total_eat >= philos[i].number_eat)
			count++;
		pthread_mutex_unlock(philos[i].eaten_mutex);
		i++;
	}
	if (count == num_philos)
	{
		pthread_mutex_lock(philos[0].flag_mutex);
		//printf("All %d have eaten \n", count);
		*philos[0].flag_died = 1;
		pthread_mutex_unlock(philos[0].flag_mutex);
		return (1);
	}
	return (0);
}
