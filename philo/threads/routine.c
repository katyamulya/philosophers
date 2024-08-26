/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:59:50 by kdvarako          #+#    #+#             */
/*   Updated: 2024/08/26 16:50:28 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("Philo %d %s\n", philo->num, msg);
	pthread_mutex_unlock(philo->print_mutex);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	philo_print(philo, "took a left fork");
	pthread_mutex_lock(philo->right);
	philo_print(philo, "took a right fork");
	philo_print(philo, "is eating");
	//gettimeofday(&philo.last_eat, 0);
	ft_usleep(philo->t_eat);
	pthread_mutex_lock(philo->eaten_mutex);
	*(philo->count_eaten) = *(philo->count_eaten) + 1;
	printf("%d\n", *philo->count_eaten);
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
	//ft_usleep(philo->t_sleep);
}
