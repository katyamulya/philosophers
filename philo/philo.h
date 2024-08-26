/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:46:27 by kdvarako          #+#    #+#             */
/*   Updated: 2024/08/26 16:41:48 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_philo
{
	pthread_t		id;
	int				num;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				number_eat;
	//int				eaten;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	struct timeval	last_eat;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*flag_mutex;
	pthread_mutex_t	*eaten_mutex;
	int				*flag_died;
	int				*count_eaten;
}   t_philo;

typedef struct s_prog_data
{
	int				number_philos;
	t_philo			*philos;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				number_eat;
	int				flag_died;
	int				count_eaten;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	flag_mutex;
	pthread_mutex_t	eaten_mutex;
}	t_prog_data;

int			check_err(int argc, char **argv);
t_prog_data	*init_data(int argc, char **argv, t_philo *philos);
void		init_philos(t_philo *philos, t_prog_data *data, \
						pthread_mutex_t *forks);
void		init_forks(pthread_mutex_t *forks, int num);
int			create_threads(t_prog_data *data, t_philo *philos, int number);
int			ft_atoi(const char *str);
void		ft_usleep(int ms);
void		philo_eating(t_philo *philo);
void		philo_sleeping(t_philo *philo);
void		philo_thinking(t_philo *philo);

#endif

