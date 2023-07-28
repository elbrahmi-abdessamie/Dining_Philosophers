/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:12 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/07/27 10:22:35 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

short	data_init(int ac, char **av, t_share_data *data)
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
	if (ac == 6)
	{
		data->num_of_meals = ft_atoi_parse(av[5]);
		if (data->num_of_meals == (unsigned long)-1)
			return (false);
	}
	return 1;
}
void	inti_mtx(t_share_data *data)
{
	pthread_mutex_init(&data->write_mtx, NULL);
	pthread_mutex_init(&data->termainate, NULL);
	pthread_mutex_init(&data->l_eat_time, NULL);
	pthread_mutex_init(&data->stat_p, NULL);

}
int	p_init(t_share_data *data)
{
	int	i;

	i = 0;
	inti_mtx(data);
	while (i < data->philo_num)
	{
		data->philo[i].pid = i + 1;
		data->philo[i].data = data;
		data->philo[i].stat = TS_ALIVE;
		data->philo[i].last_meal = data->start_sim_time;
		data->philo[i].num_of_meal_taken = 0;
		data->philo[i].r_fork = NULL;
		pthread_mutex_init(&data->philo[i].l_fork, NULL);
		if (data->philo_num == 1)
			return (1);
		if (i == data->philo_num - 1)
			data->philo[i].r_fork = &data->philo[0].l_fork;
		else
			data->philo[i].r_fork = &data->philo[i + 1].l_fork;
		i++;
	}
	return (1);
}

void	syncro(t_philo *p)
{
	if (!(p->pid % 2))
		ft_usleep(p->data->time_to_eat / 10);
}

int	phil_death_check(t_philo *p)
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
void	canva(void)
{
	printf(" \033[32;1m+---------------------+-----------+---------+--------------------+\n");
	printf(" |       TIME(ms)      +   PROFIL  +    ID   +        EVENT       |\n");\
	printf(" +---------------------+-----------+---------+--------------------+\n");
}
void	ft_write_stat(char *str, t_philo *p)
{
	unsigned long	time;
	pthread_mutex_lock(&p->data->write_mtx);
	unsigned int	cur = p->data->start_sim_time;
	time = time_line() - cur;
	if (time >= 0 && !p->data->sim)
	{
		printf(" | %11lu         |", time);
		printf(" | PHILO | | %4lu    | | %19s", p->pid, str);
	}
	pthread_mutex_unlock(&p->data->write_mtx);

}
void routine(t_philo *p)
{
	pthread_mutex_lock(&p->l_fork);
	ft_write_stat("take the fork ||\n", p);
	if (!p->r_fork)
	{
		ft_usleep(p->data->time_to_die + 1);
		return ;
	}
	pthread_mutex_lock(p->r_fork);
	ft_write_stat("take the fork ||\n", p);
	ft_write_stat("eating ||\n", p);
	pthread_mutex_lock(&p->data->l_eat_time);
	p->last_meal = time_line();
	p->num_of_meal_taken++;
	pthread_mutex_unlock(&p->data->l_eat_time);
	ft_usleep(p->data->time_to_eat);
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(&p->l_fork);
	ft_write_stat("is sleeping ||\n", p);
	ft_usleep(p->data->time_to_sleep);
	ft_write_stat("is thinking ||\n", p);
}

void *thread(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	syncro(phil);
	while (!phil_death_check(phil) && !phil->data->sim)
	{
		routine(phil);
		if (phil->data->philo_num == 1)
		{
			ft_write_stat("dead ||\n", phil);
			break ;
		}
		if (phil->data->sim)
			break;
		if (phil->num_of_meal_taken == phil->data->num_of_meals)
		{
			pthread_mutex_lock(&phil->data->stat_p);
			phil->data->philo_die++;
			phil->stat = TS_TERMINATED;
			if (phil->data->philo_die == phil->data->philo_num)
			{
				phil->data->sim = 1;
				pthread_mutex_unlock(&phil->data->stat_p);
			}
			pthread_mutex_unlock(&phil->data->stat_p);
			return (NULL);
		}
	}
	return (NULL);
}
int	simulate(t_share_data *data, t_philo *p)
{
	int	iter;

	iter = 0;
	data->philo = p;

	if (!p_init(data))
		return (0);
	canva();
	while (iter < data->philo_num)
	{
		if (pthread_create(&data->philo[iter].tid, NULL, thread, &data->philo[iter]))
			return (puts("failed to create thread\n"), 0);
		iter++;
	}
	return (1);
}
void	halt_simulation(t_share_data *data)
{
	int	iter;

	iter = -1;
	
	while (++iter < data->philo_num)
		pthread_join(data->philo[iter].tid, NULL);
	iter = -1;
	while (++iter < data->philo_num)
		pthread_mutex_destroy(&data->philo[iter].l_fork);
	pthread_mutex_destroy(&data->write_mtx);
	pthread_mutex_destroy(&data->termainate);
	pthread_mutex_destroy(&data->l_eat_time);
	pthread_mutex_destroy(&data->stat_p);
	
}

int main(int ac, char **av)
{
	t_share_data data;
	t_philo		philos[MAX_P];
	int 		iter;

	iter = 0;
	if (ac < 4)
		return (puts("error\n"), 1);
	if (!data_init(ac, av, &data))
		return (puts("Error\n"), 1);
	simulate(&data, philos);
	while (!data.sim && data.philo_num > 1)
	{
		if (iter == data.philo_num - 1)
			iter = 0;
		ft_usleep(data.time_to_die + 1);
		if ((time_line() - philos[iter].last_meal) >= data.time_to_die && !data.sim)
		{
			ft_write_stat("died ||\n", &philos[iter]);
			data.sim = 1;
			philos[iter].stat = TS_TERMINATED;
			break ;
		}
		iter++;
	}
	halt_simulation(&data);
}
