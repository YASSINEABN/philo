/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:29:28 by ibenaiss          #+#    #+#             */
/*   Updated: 2024/06/08 00:08:44 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_flag);
	if (philo->table->death == 1)
	{
		pthread_mutex_unlock(&philo->table->death_flag);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_flag);
	return (0);
}

int	checkers(t_philo *philo)
{
	if (check_death_flag(philo))
		return (1);
	pthread_mutex_lock(&philo->mtx);
	if (philo->eat == 0)
	{
		pthread_mutex_unlock(&philo->mtx);
		return (1);
	}
	return (0);
}

void	supervisor_helper(t_philo *philo)
{
	philo->table->death = 1;
	printf("%llu %d died\n", get_time() - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->death_flag);
}

void	*supervisor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (checkers(philo))
			return (NULL);
		if (get_time()
			- philo->last_meal >= (unsigned long)philo->table->time_to_die)
		{
			pthread_mutex_unlock(&philo->mtx);
			pthread_mutex_lock(&philo->table->death_flag);
			if (philo->table->death == 1)
			{
				pthread_mutex_unlock(&philo->table->death_flag);
				return (NULL);
			}
			supervisor_helper(philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mtx);
		ft_usleep(10);
	}
	return (NULL);
}
