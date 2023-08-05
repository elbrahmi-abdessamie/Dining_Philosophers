/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:24:50 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/08/05 16:30:49 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo_bonus.h"

static void	*monitor(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	while (true)
	{
		ft_usleep(phil->data->time_to_die);
		sem_wait(phil->data->d_lock);
		if ((time_line() - phil->last_meal) >= phil->data->time_to_die)
		{
			ft_write_stat("died ||\n", phil, 1);
			exit(TS_TERMINATED);
		}
		sem_post(phil->data->d_lock);
		sem_wait(phil->data->d_lock);
		if (phil->num_of_meal_taken >= phil->data->num_of_meals \
		&& phil->num_of_meal_taken != (unsigned long)-1)
		{
			ft_write_stat(NULL, phil, 0);
			exit(TS_TERMINATED);
		}
		sem_post(phil->data->d_lock);
	}
	return (NULL);
}

static void	routine(t_philo *p)
{
	sem_wait(p->data->g_lock);
	ft_write_stat("take the fork ||\n", p, 1);
	sem_wait(p->data->g_lock);
	ft_write_stat("take the fork ||\n", p, 1);
	ft_write_stat("eating ||\n", p, 1);
	p->last_meal = time_line();
	ft_usleep(p->data->time_to_eat);
	if (p->num_of_meal_taken != (unsigned long)-1)
		p->num_of_meal_taken++;
	sem_post(p->data->g_lock);
	sem_post(p->data->g_lock);
	ft_write_stat("is sleeping ||\n", p, 1);
	ft_usleep(p->data->time_to_sleep);
	ft_write_stat("is thinking ||\n", p, 1);
}

static void	start_sim(t_philo *p)
{
	pthread_t	listner;

	p->last_meal = time_line();
	p->last_meal = time_line();
	p->num_of_meal_taken = 0;
	if (pthread_create(&listner, NULL, monitor, p) || \
	pthread_detach(listner))
		return ;
	while (true)
		routine(p);
}

static void	child(t_philo *p)
{
	p->pid = ft_fork(p->data);
	if (!p->pid)
	{
		start_sim(p);
		exit(SUCCESS);
	}
}

int	simulate(t_share_data *data, t_philo *p)
{
	int	iter;
	int	stat;

	iter = 0;
	data->philo = p;
	p_init(data);
	canva();
	while (iter < (int)data->philo_num)
	{
		child(&p[iter]);
		usleep(100);
		iter++;
	}
	while (waitpid(-1, &stat, 0) > 0)
		if (WIFEXITED(stat))
			ft_killall(data);
	return (true);
}
