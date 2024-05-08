#include<pthread.h>
#include <sys/time.h>

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

}t_table;
