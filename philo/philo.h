/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:46:27 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/09 15:34:32 by kdvarako         ###   ########.fr       */
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
	struct timeval	last_eat;
	struct timeval	*start_prog;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*flag_mutex;
	pthread_mutex_t	*eaten_mutex;
	int				*flag_died;
	int				total_eat;
}	t_philo;

typedef struct s_prog_data
{
	int				number_philos;
	t_philo			*philos;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	struct timeval	start_prog;
	int				number_eat;
	int				flag_died;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	flag_mutex;
	pthread_mutex_t	eaten_mutex;
}	t_prog_data;

int			check_err(int argc, char **argv);
t_prog_data	*init_data(int argc, char **argv, t_philo *philos);
void		init_philos(t_philo *philos, t_prog_data *data, \
						pthread_mutex_t *forks);
void		init_forks(pthread_mutex_t *forks, int num);
int			start_threads(t_prog_data data, t_philo *philos, int number);
void		*ft_philo_1(void *arg);
void		*ft_philo(void *arg);
void		*ft_monitor(void *arg);
int			ft_atoi(const char *str);
void		ft_usleep(int ms);
int			ft_strcmp(char *s1, char *s2);
size_t		convert_ms(struct timeval time);
void		philo_eating(t_philo *philo);
void		philo_sleeping(t_philo *philo);
void		philo_thinking(t_philo *philo);
void		philo_print(t_philo *philo, char *msg);
int			if_any_died(t_philo *philos, int number_philos);
int			if_all_eaten(t_philo *philos, int num_philos);
int			check_flag_died(t_philo *philo);

#endif
