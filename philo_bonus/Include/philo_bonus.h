/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:50 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/08/02 09:36:45 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>		
# include <math.h>
# include <string.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>
# include <stdatomic.h>
# define MAX_P 210
# define ERROR -1
# define FAILED 1
# define SUCCESS 0

typedef struct s_philo	t_philo;

typedef enum e_bool{
	false,
	true
}	t_bool;

typedef enum s_stat{
	TS_ALIVE,
	TS_TERMINATED
}	t_stat;

typedef struct s_share_data{
	sem_t			*g_lock;
	sem_t			*w_lock;
	sem_t			*d_lock;
	unsigned long	philo_num;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	num_of_meals;
	unsigned long	start_sim_time;
	t_philo			*philo;
}	t_share_data;

typedef struct s_philo{
	t_share_data			*data;
	pthread_t				tid;
	sem_t					*t_lock;
	int						id;
	int						pid;
	_Atomic unsigned int	last_meal;
	_Atomic int				num_of_meal_taken;
}	t_philo;

unsigned long	ft_atoi_parse(char *str);
unsigned int	time_line(void);
void			ft_usleep(unsigned int time);
void			p_init(t_share_data *data);
void			ft_killall(t_share_data	*data);
void			ft_exit(const char *err_msg);
pid_t			ft_fork(t_share_data *data);
t_bool			invalid_args(void);
t_bool			data_init(int ac, char **av, t_share_data *data);
t_bool			open_sem(t_share_data *data);
void			ft_write_stat(char *str, t_philo *p, int flg);
void			canva(void);
int				simulate(t_share_data *data, t_philo *p);
#endif