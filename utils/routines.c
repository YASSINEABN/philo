

#include "philo.h"

int	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_flag);
	if (philo->table->death == 1)
	{
		pthread_mutex_unlock(&philo->table->death_flag);
		return (1);
	}
	printf("%llu %d is sleeping\n", get_time() - philo->table->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->table->death_flag);
	ft_usleep(philo->table->time_to_sleep);
	return (0);
}

int	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->l_fork]);
	if (is_sleeping(philo))
		return (1);
	pthread_mutex_lock(&philo->table->death_flag);
	if (philo->table->death == 1)
	{
		pthread_mutex_unlock(&philo->table->death_flag);
		return (1);
	}
	printf("%llu %d is thinking\n", get_time() - philo->table->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->table->death_flag);
	return (0);
}
