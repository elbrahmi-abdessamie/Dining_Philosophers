#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>		
#include <math.h>
#include <string.h>
#include <sys/time.h>
# define MAX_P 210
typedef struct s_philo t_philo;
typedef enum {
    false,
    true
}   t_bool;

typedef enum s_stat{
	TS_ALIVE,
	TS_TERMINATED
}	t_stat;

typedef struct s_share_data{
	pthread_mutex_t	write_mtx;
	pthread_mutex_t	termainate;
	pthread_mutex_t	l_eat_time;
	pthread_mutex_t	stat_p;
	unsigned long	philo_num;
	unsigned long	philo_die;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	num_of_meals;
	unsigned long	start_sim_time;
	int				sim;
	t_philo			*philo;
}	t_share_data;

typedef struct s_philo{
	t_share_data	*data;
	pthread_t		tid;
	unsigned long	pid;
	unsigned int	last_meal;
	int				num_of_meal_taken;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	int				stat;
}	t_philo;

unsigned long	ft_atoi_parse(char *str);
unsigned int	time_line(void);
void			ft_usleep(unsigned int time);
#endif