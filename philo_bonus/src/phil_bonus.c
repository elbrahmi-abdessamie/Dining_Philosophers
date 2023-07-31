/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:12 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/07/31 03:11:40 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo_bonus.h"

void	canva(void)
{
	printf(" \033[32;1m+---------------------+-----------+---------+--------------------+\n");
	printf(" |       TIME(ms)      +   PROFIL  +    ID   +        EVENT       |\n");\
	printf(" +---------------------+-----------+---------+--------------------+\n");
}
void	ft_write_stat(char *str, t_philo *p)
{
	unsigned long	time;
	unsigned int	cur;

	sem_wait(p->data->w_lock);
	cur = p->data->start_sim_time;
	time = time_line() - cur;
	if (time >= 0 && time < INT64_MAX)
	{
		printf(" | %11lu         |", time);
		printf(" | PHILO | | %4d    | | %19s", p->id, str);
	}
	sem_post(p->data->w_lock);
}

void	routine(t_philo *p)
{
	sem_wait(p->data->g_lock);
	ft_write_stat("take the fork ||\n", p);
	sem_wait(p->data->g_lock);
	ft_write_stat("take the fork ||\n", p);
	ft_write_stat("eating ||\n", p);
	p->last_meal = time_line();
	ft_usleep(p->data->time_to_eat);
	if (p->num_of_meal_taken != (unsigned long)-1)
		p->num_of_meal_taken++;
	sem_post(p->data->g_lock);
	sem_post(p->data->g_lock);
	ft_write_stat("is sleeping ||\n", p);
	ft_usleep(p->data->time_to_sleep);
	ft_write_stat("is thinking ||\n", p);
}

void	*monitor(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	while (true)
	{
		ft_usleep(phil->data->time_to_die);
		sem_wait(phil->data->d_lock);
		if ((time_line() - phil->last_meal) >= phil->data->time_to_die)
		{
			ft_write_stat("died ||\n", phil);
			exit(TS_TERMINATED);
		}
		sem_post(phil->data->d_lock);
		sem_wait(phil->data->d_lock);
		if (phil->num_of_meal_taken >= phil->data->num_of_meals && phil->num_of_meal_taken != (unsigned long)-1)
		{
			ft_usleep(phil->data->time_to_eat);
			sem_wait(phil->data->w_lock);
			printf("\b Simulation ended\n");
			sem_post(phil->data->w_lock);
			exit(TS_TERMINATED);
		}
		sem_post(phil->data->d_lock);
	}
	return (NULL);
}

void	start_sim(t_philo *p)
{
	pthread_t	listner;

	p->last_meal = time_line();
	pthread_create(&listner, NULL, monitor, p);
	pthread_detach(listner);
	p->last_meal = time_line();
	p->num_of_meal_taken = 0;
	while (true)
		routine(p);
}

void	child(t_philo *p)
{

	p->pid = ft_fork(p->data);
	if (!p->pid)
	{
		start_sim(p);
		exit(SUCCESS);
	}	
}

int	simulate(t_share_data *data, t_philo *p)
{
	int	iter;
	int	stat;
	
	iter = 0;
	data->philo = p;
	p_init(data);
	canva();
	while (iter < data->philo_num)
	{
		child(&p[iter]);
		usleep(100);
		iter++;
	}
	while (waitpid(-1, &stat, 0) > 0)
		if (WIFEXITED(stat))
			ft_killall(data);
	return (true);
}

int main(int ac, char **av)
{
	t_share_data data;
	t_philo		philos[MAX_P];
	int 		iter;

	iter = 0;
	if (ac < 5 || ac > 6)
		return (puts("error\n"), FAILED);
	if (!data_init(ac, av, &data))
		return (invalid_args());
	if (!open_sem(&data))
		ft_exit("sem_open ");
	simulate(&data, philos);
	return (SUCCESS);
}
