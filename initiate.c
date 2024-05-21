#include "philo.h"

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