/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:52:39 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/08/02 09:39:25 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo_bonus.h"

t_bool	data_init(int ac, char **av, t_share_data *data)
{
	memset(data, 0, sizeof(t_share_data));
	data->start_sim_time = (unsigned long)time_line();
	data->philo_num = ft_atoi_parse(av[1]);
	if (data->philo_num == (unsigned long)-1)
		return (false);
	data->time_to_die = ft_atoi_parse(av[2]);
	if (data->time_to_die == (unsigned long)-1)
		return (false);
	data->time_to_eat = ft_atoi_parse(av[3]);
	if (data->time_to_eat == (unsigned long)-1)
		return (false);
	data->time_to_sleep = ft_atoi_parse(av[4]);
	if (data->time_to_eat == (unsigned long)-1)
		return (false);
	data->num_of_meals = (unsigned long)-1;
	if (ac == 6)
	{
		data->num_of_meals = ft_atoi_parse(av[5]);
		if (data->num_of_meals == (unsigned long)-1)
			return (false);
	}
	return (true);
}

t_bool	open_sem(t_share_data *data)
{
	sem_unlink("/fork_lock");
	data->g_lock = sem_open("/fork_lock", O_CREAT, 0644, \
	(unsigned int)data->philo_num);
	if (data->g_lock == SEM_FAILED)
		return (false);
	sem_unlink("/write_lock");
	data->w_lock = sem_open("/write_lock", O_CREAT, 0644, 1);
	if (data->w_lock == SEM_FAILED)
		return (false);
	sem_unlink("/d_lock");
	data->d_lock = sem_open("/d_lock", O_CREAT, 0644, 1);
	if (data->d_lock == SEM_FAILED)
		return (false);
	return (true);
}

void	p_init(t_share_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philo[i].id = i + 1;
		data->philo[i].pid = -1;
		data->philo[i].data = data;
		i++;
	}
}

void	ft_write_stat(char *str, t_philo *p, int flg)
{
	unsigned long	time;
	unsigned int	cur;

	if (!flg)
	{
		ft_usleep(p->data->time_to_eat);
		sem_wait(p->data->w_lock);
		printf("\b Simulation ended\n");
		sem_post(p->data->w_lock);
		return ;
	}
	sem_wait(p->data->w_lock);
	cur = p->data->start_sim_time;
	time = (unsigned long)time_line() - cur;
	if (time >= 0 && time < INT64_MAX)
	{
		printf(" | %11lu         |", time);
		printf(" | PHILO | | %4d    | | %19s", p->id, str);
	}
	sem_post(p->data->w_lock);
}
