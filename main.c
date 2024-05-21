#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "philo.h"


size_t get_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

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
            pthread_mutex_lock(&table->philos[i].mtx);
            pthread_mutex_lock(&table->philos[i].meal);
            if (get_time() - table->philos[i].last_meal > table->time_to_die) {
                            pthread_mutex_unlock(&table->philos[i].meal);

                table->philo_died = 1;
                printf("%ld %d died\n", get_time() - table->time_start, table->philos[i].id);
                pthread_mutex_unlock(&table->philos[i].mtx);

                exit(1);
            }
                                        pthread_mutex_unlock(&table->philos[i].meal);

            pthread_mutex_unlock(&table->philos[i].mtx);
        }
            pthread_mutex_unlock(&table->philo_died_mutex);

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

void init_struct(int argc, char **argv, t_table *table) {
    int i = -1;
    table->nbr_philos = atoi(argv[0]);
    table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
    table->time_to_die = atoi(argv[1]);
    table->time_to_eat = atoi(argv[2]);
    table->time_to_sleep = atoi(argv[3]);
    table->nbr_limit_eat = -1;
    table->philo_died = 0;

    if (argv[4]) {
        table->nbr_limit_eat = atoi(argv[4]);
    }

    while (++i < table->nbr_philos) {
        table->philos[i].id = i + 1;
        table->philos[i].fr_fork = i;
        table->philos[i].sc_fork = (i + 1) % table->nbr_philos;
        table->philos[i].meals_count = 0;
        table->philos[i].table = table;
        pthread_mutex_init(&table->philos[i].mtx, NULL);
        pthread_mutex_init(&table->forks[i], NULL);
         pthread_mutex_init(&table->philos[i].meal,NULL);
    }
    pthread_mutex_init(&table->philo_died_mutex ,NULL);
       

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
