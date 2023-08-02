/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_wraper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:09:03 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/08/02 09:39:11 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo_bonus.h"

void	ft_killall(t_share_data	*data)
{
	int	iter;

	iter = 0;
	while (iter < data->philo_num)
		kill(data->philo[iter++].pid, SIGKILL);
	sem_close(data->d_lock);
	sem_close(data->w_lock);
	sem_close(data->g_lock);
}

pid_t	ft_fork(t_share_data *data)
{
	pid_t	id;

	id = fork();
	if (id == ERROR)
	{
		ft_killall(data);
		perror("fork ");
		exit(FAILED);
	}
	return (id);
}

void	ft_usleep(unsigned int time)
{
	unsigned int	start_time;

	start_time = 0;
	start_time = time_line();
	while ((time_line() - start_time) < time)
		usleep(time / 10);
}

void	ft_exit(const char *err_msg)
{
	perror(err_msg);
	exit(FAILED);
}
