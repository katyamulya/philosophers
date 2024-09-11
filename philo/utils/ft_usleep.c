/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:21:12 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/11 11:13:14 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(int ms)
{
	struct timeval	start;
	struct timeval	after;

	gettimeofday(&start, 0);
	gettimeofday(&after, 0);
	while ((convert_ms(after) - convert_ms(start)) < ms)
	{
		usleep(500);
		gettimeofday(&after, NULL);
	}
}

size_t	convert_ms(struct timeval time)
{
	size_t	time_ms;

	time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_ms);
}
