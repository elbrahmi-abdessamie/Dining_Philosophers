/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:12 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/08/02 06:20:12 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"
void	istner(t_share_data *data)
{
	int	iter;

	iter = 0;
	while (!data->sim && data->philo_num > 1)
	{
		if (iter == data->philo_num - 1)
			iter = 0;
		ft_usleep(data->time_to_die + 1);
		if ((time_line() - data->philo[iter].last_meal) >= data->time_to_die)
		{
			ft_write_stat("died ||\n", &data->philo[iter]);
			data->sim = 1;
			data->philo[iter].stat = TS_TERMINATED;
			return ;
		}
		iter++;
	}
}
int main(int ac, char **av)
{
	t_share_data data;
	t_philo		philos[MAX_P];
	int 		iter;

	iter = 0;
	if (ac < 5 || ac > 6)
		return (puts("error\n"), 1);
	if (!data_init(ac, av, &data))
		return (puts("Error\n"), 1);
	simulate(&data, philos);
	// istner(&data);
	// while (!data.sim && data.philo_num > 1)
	// {
	// 	if (iter == data.philo_num - 1)
	// 		iter = 0;
	// 	ft_usleep(data.time_to_die + 1);
	// 	if ((time_line() - philos[iter].last_meal) >= data.time_to_die && !data.sim)
	// 	{
	// 		ft_write_stat("died ||\n", &philos[iter]);
	// 		data.sim = 1;
	// 		philos[iter].stat = TS_TERMINATED;
	// 		break ;
	// 	}
	// 	iter++;
	// }
	halt_simulation(&data);
}
