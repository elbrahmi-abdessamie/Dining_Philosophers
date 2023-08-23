/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:12 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/08/23 09:17:58 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

void	listner(t_share_data *data)
{
	int	iter;

	iter = 0;
	while (!data->sim && data->philo_num > 1)
	{
		if (iter == (int)(data->philo_num - 1))
			iter = 0;
		ft_usleep(data->time_to_die + 1);
		pthread_mutex_lock(&data->l_eat_time);
		if ((time_line() - data->philo[iter].last_meal) >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->l_eat_time);
			ft_write_stat("died ||\n", &data->philo[iter]);
			data->sim = 1;
			data->philo[iter].stat = TS_TERMINATED;
			return ;
		}
		pthread_mutex_unlock(&data->l_eat_time);
		iter++;
	}
	return ;
}

int	main(int ac, char **av)
{
	t_share_data	data;
	t_philo			philos[MAX_P];
	// int				iter;

	// iter = 0;
	if (ac < 5 || ac > 6)
		return (_err_(W_ARGS), 1);
	if (!data_init(ac, av, &data))
		return (_err_(DATA), 1);
	if (!data.philo_num)
		return (1);
	if (!simulate(&data, philos))
		return (1);
	listner(&data);
	halt_simulation(&data);
}
