#include "philo.h"

void ft_eating(t_philo *philo) {

    size_t start_time = get_time();
    pthread_mutex_lock(&philo->meal);
    philo->last_meal = start_time;
        pthread_mutex_unlock(&philo->meal);

    while (get_time() - start_time < philo->table->time_to_eat) {
        usleep(100);
    }
}

void ft_sleeping(t_philo *philo) {
    size_t start_time = get_time();
    while (get_time() - start_time < philo->table->time_to_sleep) {
        usleep(100);
    }
}

int dinner_start(t_table *table) {
    int i = -1;
    table->time_start = get_time();

    while (++i < table->nbr_philos) {
        table->philos[i].last_meal = get_time();
        pthread_create(&(table->philos[i].thread_id), NULL, &application, &table->philos[i]);
        usleep(100);
    }

    if(monitor_philos(table))
        return 1;

    i = -1;
    while (++i < table->nbr_philos) {
        pthread_join(table->philos[i].thread_id, NULL);
    }
    return 0;
}