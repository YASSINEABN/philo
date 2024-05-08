#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "philo.h"

int i = 0;


size_t get_time()
{
     struct timeval	time;
     return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void assign_fork()
{
    
}

void mutex_handle(pthread_mutex_t *mtx)
{
    pthread_mutex_init(mtx,NULL);
}

void *application(void *philo)
{
     t_philo *philoo = philo;
     pthread_mutex_lock(&philoo->mtx);
    printf("%d \n",++i);
     pthread_mutex_unlock(&philoo->mtx);
}

void dinner_start(t_table *table)
{
    int i = -1;
    table->time_start = get_time();

    while(++i <table->nbr_philos)
    {
        table->philos[i].start_time = get_time();
        pthread_create(&(table->philos[i].thread_id),NULL,&application,&table->philos[i]);
         usleep(100);
    }

    i = -1;
    while (++i < table->nbr_philos)
    {
        pthread_join(table->philos[i].thread_id, NULL);
    }
    
}

void init_struct(int argc , char **argv, t_table *table)
{
    int i = -1;

    table->philos = malloc(sizeof(t_philo) * atoi(argv[0]));

    table->nbr_philos = atoi(argv[0]);
    table->time_to_die = atoi(argv[1]);
    table->time_to_eat = atoi(argv[2]);
    table->time_to_sleep = atoi(argv[3]);

    if(argv[4])
    {
        table->nbr_limit_eat = atoi(argv[4]);
    }


    while (++i < table->nbr_philos)
    {
        table->philos[i].id = i+1;
        table->philos[i].full = 0;
        table->philos[i].meals_count = 0;
        table->philos[i].table = table;
        mutex_handle(&(table->philos[i].mtx));
    }
}
int main(int argc , char **argv)
{
    t_table table;
    if(argc >= 7 || argc <= 4)
        return -1;
    else 
    {
        // struct timeval	time;
        // printf("%ld \n",time.tv_sec * 1000 + time.tv_usec / 1000);
        init_struct(argc , argv+1 , &table);
        dinner_start(&table);
    }
}