/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:29:23 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/06/09 16:20:30 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinning_philo(void *arg)
{
	t_philo		*philo;
	pthread_t	supervisor_thread_id;

	philo = (t_philo *)arg;
	
	if (philo->table->philo_num == 1)
	{
		case_one_philo(&philo[0], philo->table);
		return (0);
	}
	
	
	if (philo->id % 2 == 0)
		usleep(100);
	if (pthread_create(&supervisor_thread_id, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (1)
	{
		if (is_eating(philo))
			break ;
		usleep(10);
	}
	pthread_join(supervisor_thread_id, NULL);
	return (NULL);
}

void	philo_init_helper(t_philo *philo, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
	{
		philo[i].eat = table->num_of_time_to_eat;
		philo[i].table = table;
		philo[i].id = i + 1;
		philo[i].r_fork = i;
		philo[i].l_fork = (i + 1) % table->philo_num;
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_mutex_init(&philo[i].mtx, NULL);
	}
}

int check_args(char *str)
{
	
	while (*str)
	{
		if(!ft_isdigit(*str))
		{
			return 1;
		}
		str++;
	}
	return 0;
}

int init_struct( char **av , int ac)
{

	int i = -1;
	
	if((ac > 4 && ac  < 6) || ac == 6)
	{
		
		while (av[++i])
		{
			if(check_args(av[i]) )
			{
				
				printf("ERROR ON ARGS \n");
				return 1;
			}
			
		}	
	}
	else
	{
		printf("wrong on nubers of parametres \n");
		return 1;
	}
	return 0;
}

int fill_struct(t_table *table  , char **av )
{
	table->philo_num = ft_atoi(av[0]);
	table->time_to_die = ft_atoi(av[1]);
	table->time_to_eat = ft_atoi(av[2]);
	table->time_to_sleep = ft_atoi(av[3]);
	if(table->philo_num <0 || table->time_to_die < 0 || table->time_to_eat < 0 || 
		table->time_to_sleep < 0)
		{
			printf("wrong parametres");
			return 1;
		}
		if (av[4])
		{
			table->num_of_time_to_eat = ft_atoi(av[4]);
			if (check_args(av[4]) == 1 || table->num_of_time_to_eat < 0 || ft_atoi(av[4]) == -1)
			{
				printf("Wrong arguments\n");
				return (0);
			}
		}
		return 0;
}

int	philo_init(t_table *table, t_philo *philo, char **av , int ac)
{

	int i = -1;
	if(init_struct(av,ac))
	{
		return 1;
	}
	if(fill_struct(table ,av  ))
	{
		return 1;
	}
	if (av[4])
	{
		while (++i < table->philo_num)
			philo[i].eat = table->num_of_time_to_eat;
	}
	else
		table->num_of_time_to_eat = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
		return (1);
	pthread_mutex_init(&table->death_flag, NULL);
	pthread_mutex_init(&table->finish_eating, NULL);
	philo_init_helper(philo, table);
	i = -1;
	return (0);
}

int	philosophers(t_table *table, t_philo *philo, char **av , int ac)
{
	int	i;

	i = -1;
	if (philo_init(table, philo, av, ac))
		return (1);
	
	table->start_time = get_time();
	// 	if (table->philo_num == 1)
	// {
	// 	case_one_philo(&philo[0], table);
	// 	free(table->forks);
	// 	 free(philo);
	// 	return (0);
	// }
	while (++i < table->philo_num)
	{
		philo[i].last_meal = get_time();
		pthread_create(&philo[i].thread_id, NULL, dinning_philo, &philo[i]);
		usleep(1);
	}

	i = -1;
	while (++i < table->philo_num)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < table->philo_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&philo[i].mtx);
	}
	pthread_mutex_destroy(&table->death_flag);
	free(table->forks);
	free(philo);
	return (0);
}
