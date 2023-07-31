/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:22 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/07/31 02:58:08 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo_bonus.h"

t_bool	invalid_args(void)
{
	printf("usage : ./bin/philo number_of_philosophers");
	printf(" time_to_die time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	return (FAILED);
}

unsigned int	time_line(void)
{
	unsigned long	cur_time;
	struct timeval	s_time;

	cur_time = 0;
	if (gettimeofday(&s_time, NULL) == -1)
		return (printf("Gettimeofday function failed\n"), -1);	
	cur_time = (s_time.tv_sec * 1000) + (s_time.tv_usec / 1000);
	return (cur_time);
}

t_bool	ft_isdigit(int c)
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