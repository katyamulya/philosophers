
#include "../philo.h"

/*int	is_eaten(t_philo *philo)
{
	pthread_mutex_lock(philo->eaten_mutex);
	//printf("total %d, number %d ", philo->total_eat, philo->number_eat);
	if (philo->total_eat >= philo->number_eat)
		return (pthread_mutex_unlock(philo->eaten_mutex), 1);
	pthread_mutex_unlock(philo->eaten_mutex);
	return (0);
}*/

int	if_all_eaten(t_philo *philos, int num_philos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < num_philos)
	{
		//if (is_eaten(&philos[i]) == 1)
		//{
		pthread_mutex_lock(philos[i].eaten_mutex);
		//printf("total %d, number %d ", philo->total_eat, philo->number_eat);
		if (philos[i].total_eat >= philos[i].number_eat)
			count++;
		pthread_mutex_unlock(philos[i].eaten_mutex);
		//}
		i++;
	}
	//printf("count = %d ", count);
	if (count == num_philos)
	{
		pthread_mutex_lock(philos[0].flag_mutex);
		printf("All %d have eaten \n", count);
		*philos[0].flag_died = 1;
		pthread_mutex_unlock(philos[0].flag_mutex);
		return (1);
	}
	return (0);
}
