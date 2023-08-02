/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_act.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:32:40 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/08/02 08:53:55 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

static t_bool	pick_fork(t_philo *p)
{
	pthread_mutex_lock(&p->l_fork);
	ft_write_stat("take the fork ||\n", p);
	if (!p->r_fork)
	{
		ft_usleep(p->data->time_to_die + 1);
		return (false);
	}
	pthread_mutex_lock(p->r_fork);
	ft_write_stat("take the fork ||\n", p);
	return (true);
}

static void	eat(t_philo *p)
{
	ft_write_stat("eating ||\n", p);
	pthread_mutex_lock(&p->data->l_eat_time);
	p->last_meal = time_line();
	p->num_of_meal_taken++;
	pthread_mutex_unlock(&p->data->l_eat_time);
	ft_usleep(p->data->time_to_eat);
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(&p->l_fork);
}

static void	sleep_nap(t_philo *p)
{
	ft_write_stat("is sleeping ||\n", p);
	ft_usleep(p->data->time_to_sleep);
	ft_write_stat("is thinking ||\n", p);
}

t_bool	routine(t_philo *p)
{
	if (!pick_fork(p))
		return (true);
	eat(p);
	sleep_nap(p);
	if (p->num_of_meal_taken == (int)p->data->num_of_meals)
	{
		pthread_mutex_lock(&p->data->stat_p);
		p->data->philo_die++;
		p->stat = TS_TERMINATED;
		if (p->data->philo_die == p->data->philo_num)
		{
			p->data->sim = 1;
			pthread_mutex_unlock(&p->data->stat_p);
		}
		pthread_mutex_unlock(&p->data->stat_p);
		return (false);
	}
	return (true);
}
