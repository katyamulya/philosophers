/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:21:12 by kdvarako          #+#    #+#             */
/*   Updated: 2024/08/26 15:23:28 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(int ms)
{
	struct timeval	start;
	struct timeval	after;

	gettimeofday(&start, 0);
	gettimeofday(&after, 0);

	while (((after.tv_sec - start.tv_sec) * 1000 + \
		(after.tv_usec - start.tv_usec) / 1000) < ms)
	{
		usleep(10);
		gettimeofday(&after, 0);
	}
}
