/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:38:46 by kdvarako          #+#    #+#             */
/*   Updated: 2024/08/26 17:29:30 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_died(t_philo philo)
{
	struct timeval	current;

	if (((current.tv_sec * 1000 + current.tv_usec / 1000) - \
		(philo.last_eat.tv_sec * 1000 + philo.last_eat.tv_usec / 1000)) \
			> philo.t_die)
		return (1);
	else
		return (0);
}

int	is_eaten(t_prog_data *data)
{
	//printf("Philo %d, eaten = %d\n", philo.num, philo.eaten);
	pthread_mutex_lock(&data->eaten_mutex);
	if (data->count_eaten != 0)
		printf("Count_eaten  = %d\n", data->count_eaten);
	if ((data->count_eaten != 0) && (data->count_eaten >= data->number_eat \
		* data->number_philos))
		return (pthread_mutex_unlock(&data->eaten_mutex), 1);
	pthread_mutex_unlock(&data->eaten_mutex);
	return (0);
}

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
	t_philo philo = *(t_philo *)arg;

	if (philo.num % 2 == 0)
		ft_usleep(1);

	//+ global mutex for printf from args

	while (check_flag_died(&philo) == 0)
	{
		philo_eating(&philo);
		philo_sleeping(&philo);
		philo_thinking(&philo);
	}
	return (NULL);
}

void	*monitoring(void *arg)
{
	/*t_philo	*philos;
	int		*result;

	result = malloc(sizeof(int));
	philos = (t_philo *)arg;
	*result = 0;*/
	t_prog_data	*data;

	data = (t_prog_data *)arg;
	//printf("count = %d\n", data->count_eaten);
	while (1)
	{
		if (is_eaten(data) == 1)
			break ;
	}
	//return ((void *) result);
	return (NULL);
}

int create_threads(t_prog_data *data, t_philo *philos, int number)
{
	pthread_t	th_monitor;
	int			*result;

	/*if (pthread_create(&th_monitor, NULL, &monitoring, &philos) != 0)
		return (1);*/
	if (pthread_create(&th_monitor, NULL, &monitoring, &data) != 0)
		return (1);
	for (int i = 0; i < number; i++)
	{
		if (pthread_create(&philos[i].id, NULL, &ft_philo, &philos[i]) != 0)
		{
			perror("Failed to create thread");
			return (i);
		}
		//pthread_detach(philos[i].id);
	}
	if (pthread_join(th_monitor, NULL) != 0)
		return (2);
	for (int i = 0; i < number; i++)
	{
		if (pthread_join(philos[i].id, NULL) != 0)
		{
			perror("Failed to join thread");
			return (i);
		}
	}
	/*if (pthread_join(th_monitor, (void **)&result) != 0)
		return (2);*/
	return (0);
}
