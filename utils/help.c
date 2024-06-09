

#include "philo.h"

int	check_args(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			return (1);
		}
		str++;
	}
	return (0);
}

int	init_struct(char **av, int ac)
{
	int	i;

	i = -1;
	if ((ac > 4 && ac < 6) || ac == 6)
	{
		while (av[++i])
		{
			if (check_args(av[i]))
			{
				printf("ERROR ON ARGS \n");
				return (1);
			}
		}
	}
	else
	{
		printf("wrong on nubers of parametres \n");
		return (1);
	}
	return (0);
}

int	fill_struct(t_table *table, char **av)
{
	table->philo_num = ft_atoi(av[0]);
	table->time_to_die = ft_atoi(av[1]);
	table->time_to_eat = ft_atoi(av[2]);
	table->time_to_sleep = ft_atoi(av[3]);
	if (table->philo_num < 0 || table->time_to_die < 0 || table->time_to_eat < 0
		|| table->time_to_sleep < 0)
	{
		printf("wrong parametres");
		return (1);
	}
	if (av[4])
	{
		table->num_of_time_to_eat = ft_atoi(av[4]);
		if (check_args(av[4]) == 1 || table->num_of_time_to_eat < 0
			|| ft_atoi(av[4]) == -1)
		{
			printf("Wrong arguments\n");
			return (0);
		}
	}
	return (0);
}
