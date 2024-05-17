#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "philo.h"

int i = -1;

size_t get_time()
{
     struct timeval	time;
     return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

    void ft_sleep(t_philo *philo)
    {
        pthread_mutex_lock(&philo->mtx);
        usleep(philo->table->time_to_sleep);
        pthread_mutex_unlock(&philo->mtx);
    }

    void ft_eating(t_philo *philo)
    {
        pthread_mutex_lock(&philo->mtx);
        usleep(philo->table->time_to_eat);
        pthread_mutex_unlock(&philo->mtx);
    }

void ft_philo(t_philo *philo )
{
    size_t gettime = get_time();

    pthread_mutex_lock(&philo->table->forks[philo->fr_fork]);
    printf(" id  == %d   has taken a fork at %ld\n",philo->id,gettime);
    pthread_mutex_lock(&philo->table->forks[philo->sc_fork]);
    printf(" id  == %d   has taken a fork at %ld\n",philo->id , gettime);
    printf(" id == %d is eating \n",philo->id);
     ft_eating(philo);
     printf(" id == %d is sleeping \n",philo->id);
     ft_sleep(philo);
    pthread_mutex_unlock(&philo->table->forks[philo->fr_fork]);
    pthread_mutex_unlock(&philo->table->forks[philo->sc_fork]);
}

void mutex_handle(pthread_mutex_t *mtx)
{
    pthread_mutex_init(mtx,NULL);
}

void mutex_handle2(pthread_mutex_t *mtx)
{
    pthread_mutex_init(mtx,NULL);
}

void *application(void *philo)
{
     t_philo *philoo = philo;
    if(philoo->id % 2 == 0)
        usleep(150);
    ft_philo(philoo);
    
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
     table->nbr_philos = atoi(argv[0]);
    table->philos = malloc(sizeof(t_philo) * atoi(argv[0]));
    table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
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
        table->philos[i].fr_fork = i;
        table->philos[i].sc_fork= (i+1) % table->nbr_philos;
        table->philos[i].meals_count = 0;
        table->philos[i].table = table;
        mutex_handle(&(table->philos[i].mtx));
        mutex_handle2(&(table->forks[i]));
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
