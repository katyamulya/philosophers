/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:59:50 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/11 17:16:43 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_print(t_philo *philo, char *msg)
{
	struct timeval	current;
	size_t			time;

	if (check_flag_died(philo) == 1 && ft_strcmp(msg, " died") != 0)
		return ;
	pthread_mutex_lock(philo->print_mutex);
	gettimeofday(&current, NULL);
	time = convert_ms(current) - convert_ms(*philo->start_prog);
	printf("%zu %d %s\n", time, philo->num, msg);
	pthread_mutex_unlock(philo->print_mutex);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right);
	philo_print(philo, "has taken a fork");
	philo_print(philo, "is eating");
	pthread_mutex_lock(philo->eaten_mutex);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(philo->eaten_mutex);
	ft_usleep(philo->t_eat);
	pthread_mutex_lock(philo->eaten_mutex);
	philo->total_eat = philo->total_eat + 1;
	pthread_mutex_unlock(philo->eaten_mutex);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	philo_sleeping(t_philo *philo)
{
	philo_print(philo, "is sleeping");
	ft_usleep(philo->t_sleep);
}

void	philo_thinking(t_philo *philo)
{
	philo_print(philo, "is thinking");
}
