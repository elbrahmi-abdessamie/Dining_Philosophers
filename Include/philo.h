#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

# define MAX_P 210
typedef struct s_philo t_philo;
typedef enum {
    false,
    true
}   t_bool;

typedef struct s_share_data{
	pthread_mutex_t	write_mtx;
	unsigned long	philo_num;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	num_of_meals;
	t_philo			*philo;
}	t_share_data;

typedef struct s_philo{
	t_share_data	*data;
	pthread_t		tid;
	unsigned long	pid;
	unsigned long	last_meal;
	int				num_of_meal_taken;
	int				l_fork;
	int				r_fork;
	int				stat;
}	t_philo;

unsigned long	ft_atoi_parse(char *str);
#endif