/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:02:13 by yaboulan          #+#    #+#             */
/*   Updated: 2024/06/09 22:04:08 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table
{
	long long		start_time;
	int				death;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_time_to_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_flag;
	pthread_mutex_t	finish_eating;
}					t_table;

typedef struct s_philo
{
	int				r_fork;
	int				l_fork;
	int				eat;
	int				i;
	unsigned long	last_meal;
	pthread_mutex_t	mtx;
	t_table			*table;
	pthread_t		thread_id;
	int				id;
}					t_philo;

int					philosophers(t_table *utils, t_philo *philo, char **av,
						int ac);
int					ft_isdigit(int arg);
int					ft_usleep(size_t time);
int					ft_atoi(const char *pt);
int					philo_init(t_table *utils, t_philo *philo, char **av,
						int ac);
int					parse(t_table *utils, int ac, char **av);
size_t				get_time(void);
void				philo_init_helper(t_philo *philo, t_table *utils);
int					is_sleeping(t_philo *philo);
int					drop_forks(t_philo *philo);
int					check_death(t_philo *philo, int first_fork,
						int second_fork);
int					take_forks(t_philo *philo);
int					eating_checkers(t_philo *philo);
int					is_eating(t_philo *philo);
int					check_death_flag(t_philo *philo);
int					checkers(t_philo *philo);
void				*supervisor(void *arg);
void				*dinning_philo(void *arg);
void				switch_forks(t_philo *philo, int *first_fork,
						int *second_fork);
int					case_one_philo(t_philo *philo, t_table *table);
int					init_struct(char **av, int ac);
int					fill_struct(t_table *table, char **av);

#endif
