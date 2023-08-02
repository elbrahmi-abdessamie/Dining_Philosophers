/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:22 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/07/31 08:34:56 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

unsigned int	time_line(void)
{
	unsigned long	cur_time;
	struct timeval	s_time;

	cur_time = 0;
	if (gettimeofday(&s_time, NULL) == -1)
		return (puts("Gettimeofday function failed\n"), -1);	
	cur_time = (s_time.tv_sec * 1000) + (s_time.tv_usec / 1000);
	return (cur_time);
}

void	ft_usleep(unsigned int time)
{
	unsigned int	start_time;

	start_time = 0;
	start_time = time_line();
	while ((time_line() - start_time) < time)
		usleep(time / 10);
}

t_bool ft_isdigit(int c)
{
	return ((c >= 0x30) & (c <= 0x39));
}

unsigned long	ft_atoi_parse(char *str)
{
	unsigned long	res;

	res = 0;
	if (*str == 0x2D)
		return (-1);
	if (*str == 0x2B)
		str++;
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		res = res * 0xA + (*(str++) - 0x30);
		if (res > __INT64_MAX__)
			return (-1); 
	}
	return (res);
}

void	ft_write_stat(char *str, t_philo *p)
{
	unsigned long	time;
	unsigned int	cur;

	pthread_mutex_lock(&p->data->write_mtx);
	cur = p->data->start_sim_time;
	time = time_line() - cur;
	if (time >= 0 && !p->data->sim)
	{
		printf(" | %11lu         |", time);
		printf(" | PHILO | | %4lu    | | %19s", p->pid, str);
	}
	pthread_mutex_unlock(&p->data->write_mtx);

}