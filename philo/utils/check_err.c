/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:12:37 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/11 11:13:02 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		num = num * 10;
		num = num + str[i] - 48;
		i++;
	}
	if (num < -2147483648 || num > 2147483647)
		num = 0;
	return (num);
}

int	check_ifnum(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] < '0' || s[i] > '9'))
			return (-1);
		i++;
	}
	return (0);
}

int	check_edge_cases(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (-1);
	if (ft_atoi(argv[2]) < 60)
		return (-1);
	if (ft_atoi(argv[3]) < 60)
		return (-1);
	if (ft_atoi(argv[4]) < 60)
		return (-1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0)
			return (-1);
	}
	return (0);
}

int check_err(int argc, char **argv)
{
	// all should be numbers > 0, number_eat can be 0, number_philos <= 200
	int i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (check_ifnum(argv[i]) == -1)
		{
			printf("Error! Args should be positive numbers\n");
			return (-1);
		}
		i++;
	}
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_atoi(argv[i]) == 0 && ft_strlen(argv[i]) > 1)
		{
			printf("Error! Wrong data\n");
			return (-1);
		}
		i++;
	}
	if (check_edge_cases(argc, argv) == -1)
	{
		printf("Error! Edge cases\n");
		return (-1);
	}
	return (0);
}
