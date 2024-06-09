/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:02:21 by yaboulan          #+#    #+#             */
/*   Updated: 2024/06/09 22:04:17 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, int first_fork, int second_fork)
{
	if (philo->table->death == 1)
	{
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		pthread_mutex_unlock(&philo->table->forks[second_fork]);
		pthread_mutex_unlock(&philo->table->death_flag);
		return (1);
	}
	return (0);
}

void	switch_forks(t_philo *philo, int *first_fork, int *second_fork)
{
	if (philo->id == philo->table->philo_num)
	{
		if (philo->r_fork > philo->l_fork)
		{
			*first_fork = philo->l_fork;
			*second_fork = philo->r_fork;
		}
	}
}

int	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = philo->r_fork;
	second_fork = philo->l_fork;
	switch_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(&philo->table->forks[first_fork]);
	pthread_mutex_lock(&philo->table->death_flag);
	if (philo->table->death == 1)
	{
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		pthread_mutex_unlock(&philo->table->death_flag);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_flag);
	printf("%llu %d has taken a fork\n", get_time() - philo->table->start_time,
		philo->id);
	pthread_mutex_lock(&philo->table->forks[second_fork]);
	pthread_mutex_lock(&philo->table->death_flag);
	if (check_death(philo, first_fork, second_fork))
		return (1);
	printf("%llu %d has taken a fork\n", get_time() - philo->table->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->table->death_flag);
	return (0);
}
