/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_section.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:37:15 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/08/02 08:54:47 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

static void	syncro(t_philo *p)
{
	if (!(p->pid % 2))
		ft_usleep(p->data->time_to_eat / 10);
}

static int	phil_death_check(t_philo *p)
{
	pthread_mutex_lock(&p->data->termainate);
	if (p->stat == TS_TERMINATED)
	{
		pthread_mutex_unlock(&p->data->termainate);
		return (1);
	}
	pthread_mutex_unlock(&p->data->termainate);
	return (0); 
}

void	*thread(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	syncro(phil);
	while (!phil_death_check(phil) && !phil->data->sim)
	{
		if (!routine(phil))
			return (NULL);
		if (phil->data->philo_num == 1)
		{
			ft_write_stat("dead ||\n", phil);
			break ;
		}
	}
	return (NULL);
}

t_bool	simulate(t_share_data *data, t_philo *p)
{
	int	iter;

	iter = 0;
	data->philo = p;
	if (!p_init(data))
		return (false);
	canva();
	while (iter < (int)data->philo_num)
	{
		if (pthread_create(&data->philo[iter].tid, \
		NULL, thread, &data->philo[iter]))
			return (_err_(P_CRT));
		iter++;
	}
	return (true);
}

void	halt_simulation(t_share_data *data)
{
	int	iter;

	iter = -1;
	while (++iter < (int)data->philo_num)
		pthread_join(data->philo[iter].tid, NULL);
	iter = -1;
	while (++iter < (int)data->philo_num)
		pthread_mutex_destroy(&data->philo[iter].l_fork);
	pthread_mutex_destroy(&data->write_mtx);
	pthread_mutex_destroy(&data->termainate);
	pthread_mutex_destroy(&data->l_eat_time);
	pthread_mutex_destroy(&data->stat_p);
}
