/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:12 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/08/05 16:29:31 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo_bonus.h"

int	main(int ac, char **av)
{
	t_share_data	data;
	t_philo			philos[MAX_P];
	int				iter;

	iter = 0;
	if (ac < 5 || ac > 6)
		return (invalid_args());
	if (!data_init(ac, av, &data))
		return (FAILED);
	if (!data.philo_num)
		return (FAILED);
	if (!open_sem(&data))
		ft_exit("sem_open ");
	simulate(&data, philos);
	return (SUCCESS);
}
