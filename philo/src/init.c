/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:26:01 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/08/05 16:24:36 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

t_bool	data_init(int ac, char **av, t_share_data *data)
{
	memset(data, 0, sizeof(t_share_data));
	data->start_sim_time = (unsigned long)time_line();
	data->philo_num = ft_atoi_parse(av[1]);
	if (data->philo_num == (unsigned long)-1 || data->philo_num > 200)
		return (false);
	data->time_to_die = ft_atoi_parse(av[2]);
	if (data->time_to_die == (unsigned long)-1)
		return (false);
	data->time_to_eat = ft_atoi_parse(av[3]);
	if (data->time_to_eat == (unsigned long)-1)
		return (false);
	data->time_to_sleep = ft_atoi_parse(av[4]);
	if (data->time_to_sleep == (unsigned long)-1)
		return (false);
	if (ac == 6)
	{
		data->num_of_meals = ft_atoi_parse(av[5]);
		if (data->num_of_meals == (unsigned long)-1)
			return (false);
	}
	return (true);
}

int	p_init(t_share_data *data)
{
	int	i;

	i = 0;
	if (!inti_mtx(data))
		return (_err_(MTX_INIT));
	while (i < (int)data->philo_num)
	{
		data->philo[i].pid = i + 1;
		data->philo[i].data = data;
		data->philo[i].stat = TS_ALIVE;
		data->philo[i].last_meal = data->start_sim_time;
		data->philo[i].num_of_meal_taken = 0;
		data->philo[i].r_fork = NULL;
		if (pthread_mutex_init(&data->philo[i].l_fork, NULL))
			return (_err_(MTX_INIT));
		if (data->philo_num == 1)
			return (1);
		if (i == (int)(data->philo_num - 1))
			data->philo[i].r_fork = &data->philo[0].l_fork;
		else
			data->philo[i].r_fork = &data->philo[i + 1].l_fork;
		i++;
	}
	return (1);
}

int	_err_(int err_id)
{
	if (err_id == MTX_INIT)
		printf("\033[31;1m Failed to initialize a mutex\n");
	if (err_id == W_ARGS)
	{
		printf("\033[31;1musage : ./bin/philo number_of_philosophers");
		printf(" time_to_die time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
	}
	if (err_id == P_CRT)
		printf("\033[31;1mfailed to create thread\n");
	return (0);
}

t_bool	inti_mtx(t_share_data *data)
{
	if (pthread_mutex_init(&data->write_mtx, NULL))
		return (false);
	if (pthread_mutex_init(&data->termainate, NULL))
		return (false);
	if (pthread_mutex_init(&data->l_eat_time, NULL))
		return (false);
	if (pthread_mutex_init(&data->stat_p, NULL))
		return (false);
	return (true);
}

void	canva(void)
{
	printf(" \033[32;1m+----------------------+");
	printf("------------+-----------+---------+-------\n");
	printf(" |       TIME(ms)      +   PROFIL  +    ");
	printf("ID   +        EVENT       |\n");
	printf(" +---------------------+-----------");
	printf("+---------+--------------------+\n");
}
