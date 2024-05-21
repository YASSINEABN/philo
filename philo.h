 #ifndef PHILO_H
 #define  PHILO_H

#include<pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_table t_table;
typedef struct philo t_philo;



typedef struct philo
{
    int id;
    size_t start_time;
    pthread_t thread_id;
    int meals_count;
    int full;
    long last_meal;
    char *state;
    t_table *table;
    pthread_mutex_t mtx;
    int fr_fork;
    int sc_fork;
      pthread_mutex_t meal;

    
}t_philo;

typedef struct  s_table
{
    long time_to_die;
    long time_to_sleep;
    long time_to_eat;
    size_t time_start;
    int nbr_philos;
    int nbr_limit_eat;
    t_philo *philos;
     pthread_mutex_t *forks;
     int philo_died;
     pthread_mutex_t philo_died_mutex;
}t_table;

size_t get_time();
void ft_eating(t_philo *philo);
void ft_sleeping(t_philo *philo);
int dinner_start(t_table *table);
void init_struct(int argc, char **argv, t_table *table);
void *application(void *arg);
int monitor_philos(t_table *table);

#endif