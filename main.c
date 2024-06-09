

#include "utils/philo.h"

int	case_one_philo(t_philo *philo, t_table *table)
{
	pthread_mutex_init(&table->death_flag, NULL);
	philo->id = 1;
	table->start_time = 0;
	pthread_mutex_lock(&table->death_flag);
	printf("%llu %d has taken a fork\n", table->start_time, philo->id);
	pthread_mutex_unlock(&table->death_flag);
	pthread_mutex_lock(&table->death_flag);
	printf("%llu %d died\n", table->time_to_die - table->start_time, philo->id);
	pthread_mutex_unlock(&table->death_flag);
	pthread_mutex_destroy(&table->death_flag);
	return (1);
}

int	main(int ac, char **av)
{
	t_table	table;
	t_philo	*philo;

	if (ac == 1)
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!philo)
		return (1);
	if (philosophers(&table, philo, av + 1, ac) == 1)
		return (1);
	else
		return (0);
}
