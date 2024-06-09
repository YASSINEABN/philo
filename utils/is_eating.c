

#include "philo.h"

int	eating_checkers(t_philo *philo)
{
	if (philo->eat == 0)
		return (1);
	if (take_forks(philo))
		return (1);
	pthread_mutex_lock(&philo->table->death_flag);
	if (philo->table->death == 1)
	{
		pthread_mutex_unlock(&philo->table->death_flag);
		return (1);
	}
	return (0);
}

int	is_eating(t_philo *philo)
{
	if (eating_checkers(philo))
		return (1);
	printf("%llu %d is eating\n", get_time() - philo->table->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->table->death_flag);
	pthread_mutex_lock(&philo->mtx);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mtx);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->mtx);
	if (philo->eat > 0)
		philo->eat--;
	if (philo->eat == 0)
	{
		pthread_mutex_unlock(&philo->mtx);
		pthread_mutex_unlock(&philo->table->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->l_fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo->mtx);
	if (drop_forks(philo))
		return (1);
	return (0);
}
