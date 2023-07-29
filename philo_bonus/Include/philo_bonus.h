/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:50 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/07/29 01:46:57 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>		
#include <math.h>
#include <string.h>
#include <semaphore.h>
#include <sys/time.h>
#include <signal.h>
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
	sem_t			*g_lock;
	sem_t			*w_lock;
	sem_t			*d_lock;
	sem_t			*s_lock;
	sem_t			*b_lock;
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
	sem_t			*t_lock;
	pthread_t		tid;
	int				id;
	int				pid;
	unsigned int	last_meal;
	int				num_of_meal_taken;
	int				stat;
}	t_philo;

unsigned long	ft_atoi_parse(char *str);
unsigned int	time_line(void);
void			ft_usleep(unsigned int time);
#endif