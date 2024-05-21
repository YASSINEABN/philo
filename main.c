#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "philo.h"


void *application(void *arg) {
    t_philo *philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        usleep(150);
    pthread_mutex_lock(&philo->table->philo_died_mutex);
    while (!philo->table->philo_died) {
            pthread_mutex_unlock(&philo->table->philo_died_mutex);

        pthread_mutex_lock(&philo->table->forks[philo->fr_fork]);
        printf("%ld %d has taken fork \n", get_time() - philo->table->time_start,philo->id);
        
        pthread_mutex_lock(&philo->table->forks[philo->sc_fork]);
        printf("%ld %d has taken fork \n",get_time() - philo->table->time_start, philo->id);
        
        printf("%ld %d is eating\n", get_time() - philo->table->time_start, philo->id);
        ft_eating(philo);
    
        pthread_mutex_unlock(&philo->table->forks[philo->fr_fork]);
        pthread_mutex_unlock(&philo->table->forks[philo->sc_fork]);

        if (philo->table->nbr_limit_eat != -1 && ++philo->meals_count >= philo->table->nbr_limit_eat)
            break;

        printf("%ld %d is sleeping\n", get_time() - philo->table->time_start, philo->id);
        ft_sleeping(philo);
    
        printf("%ld %d is thinking\n", get_time() - philo->table->time_start, philo->id);
    }
        pthread_mutex_unlock(&philo->table->philo_died_mutex);

    return NULL;
}

int monitor_philos(t_table *table) {
    pthread_mutex_lock(&table->philo_died_mutex);
    
    while (!table->philo_died) {
            pthread_mutex_unlock(&table->philo_died_mutex);

        for (int i = 0; i < table->nbr_philos; i++) {
            pthread_mutex_lock(&table->philos[i].meal);
            if (get_time() - table->philos[i].last_meal > table->time_to_die) {
                   pthread_mutex_unlock(&table->philos[i].meal);
        pthread_mutex_lock(&table->philo_died_mutex);

                table->philo_died = 1;
                            pthread_mutex_unlock(&table->philo_died_mutex);

                printf("%ld %d died\n", get_time() - table->time_start, table->philos[i].id);

                exit(1);
            }
             pthread_mutex_unlock(&table->philos[i].meal);
        }
            pthread_mutex_unlock(&table->philo_died_mutex);

        usleep(100);
    }
}


int main(int argc, char **argv) {
    t_table table;
    if (argc < 5 || argc > 6) {
        fprintf(stderr, "Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return -1;
    }

    init_struct(argc, argv + 1, &table);
    if(dinner_start(&table))
    {
        return 0;
    }

    free(table.philos);
    free(table.forks);

    return 0;
}
