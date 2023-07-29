/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:56:12 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/07/29 01:47:20 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo_bonus.h"

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
	data->num_of_meals = (unsigned long)-1;
	if (ac == 6)
	{
		data->num_of_meals = ft_atoi_parse(av[5]);
		if (data->num_of_meals == (unsigned long)-1)
			return (false);
	}
	return 1;
}
int	open_sem(t_share_data *data)
{
	sem_unlink("/fork_lock");
	data->g_lock = sem_open("/fork_lock", O_CREAT, 0644, (unsigned int)data->philo_num);
	if (data->g_lock == SEM_FAILED)
        return 0;
	sem_unlink("/write_lock");
	data->w_lock = sem_open("/write_lock", O_CREAT, 0644, 1);
	if (data->w_lock == SEM_FAILED)
        return 0;
	sem_unlink("/d_lock");
	data->d_lock = sem_open("/d_lock", O_CREAT, 0644, 1);
	if (data->d_lock == SEM_FAILED)
        return 0;
	sem_unlink("/stop_lock");
	data->s_lock = sem_open("/stop_lock", O_CREAT, 0644, 1);
	if (data->s_lock == SEM_FAILED)
        return 0;
	// sem_unlink("/b_lock");
	// data->b_lock = sem_open("/b_lock", O_CREAT, 0644, 1);
	// if (data->b_lock == SEM_FAILED)
    //     return 0;
	return 1;
}
int	p_init(t_share_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philo[i].id = i + 1;
		data->philo[i].pid = -1;
		data->philo[i].data = data;
		data->philo[i].stat = TS_ALIVE;
		data->philo[i].last_meal = data->start_sim_time;
		data->philo[i].num_of_meal_taken = 0;	
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
	sem_wait(p->data->d_lock);
	if (p->stat == TS_TERMINATED)
	{
		sem_post(p->data->d_lock);
		return (1);
	}	
	sem_post(p->data->d_lock);
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
	unsigned int	cur;

	sem_wait(p->data->w_lock);
	cur = p->data->start_sim_time;
	time = time_line() - cur;
	if (time >= 0 && time < INT64_MAX)
	{
		printf(" | %11lu         |", time);
		printf(" | PHILO | | %4d    | | %19s", p->id, str);
		// printf("%lu   %d   %s", time, p->pid, str);
	}
	sem_post(p->data->w_lock);

}
void routine(t_philo *p)
{
	sem_wait(p->data->g_lock);
	ft_write_stat("take the fork ||\n", p);
	sem_wait(p->data->g_lock);
	ft_write_stat("take the fork ||\n", p);
	ft_write_stat("eating ||\n", p);
	// sem_wait(p->data->e_lock);
	p->last_meal = time_line();
	sem_post(p->data->b_lock);
	ft_usleep(p->data->time_to_eat);
	if (p->num_of_meal_taken != (unsigned long)-1)
		p->num_of_meal_taken++;
	sem_post(p->data->g_lock);
	sem_post(p->data->g_lock);
	ft_write_stat("is sleeping ||\n", p);
	ft_usleep(p->data->time_to_sleep);
	ft_write_stat("is thinking ||\n", p);
}

void *thread(void *arg)
{
	t_philo	*phil;
	unsigned int alo; 
	phil = (t_philo *)arg;
	// syncro(phil);
	while (1)
	{
		ft_usleep(phil->data->time_to_die + 1);
		sem_wait(phil->data->d_lock);
		sem_wait(phil->data->b_lock);
		if ((time_line() - phil->last_meal) >= phil->data->time_to_die)
		{
			// sem_post(phil->data->b_lock);	
			ft_write_stat("died ||\n", phil);
			exit(TS_TERMINATED);
		}
		// sem_post(phil->data->b_lock);	

		sem_post(phil->data->d_lock);
		sem_wait(phil->data->d_lock);
		if (phil->num_of_meal_taken >= phil->data->num_of_meals && phil->num_of_meal_taken != (unsigned long)-1)
		{
			sem_wait(phil->data->w_lock);
			printf("\b Simulation ended\n");
			sem_post(phil->data->w_lock);
			// sem_post(phil->data->d_lock);
			// sem_post(phil->data->s_lock);
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
	pthread_create(&listner, NULL, thread, p);
	pthread_detach(listner);
	// syncro(p);
	while (1)
		routine(p);
}
void	child(t_philo *p)
{

	p->pid = fork();
	if (p->pid == -1)
	{
		perror("fork");
		exit(12);
	}	
	else if (!p->pid)
	{
		start_sim(p);
		exit(0);
	}	
		
	// while (waitpid(-1, &stat, 0) > 0)
	// 	;
	
}
void	ft_killall(t_share_data	*data)
{
	int	iter;

	iter = 0;
	while (iter < data->philo_num)
		kill(data->philo[iter++].pid, SIGKILL);
	sem_close(data->d_lock);
	sem_close(data->w_lock);
	sem_close(data->s_lock);
	sem_close(data->g_lock);
}
int	simulate(t_share_data *data, t_philo *p)
{
	int	iter;
	int	stat;
	
	iter = 0;
	data->philo = p;

	if (!p_init(data))
		return (0);
	canva();
	// sem_wait(data->s_lock);
	while (iter < data->philo_num)
	{
		child(&p[iter]);
		// usleep(1000);
		// printf("%d\n", p[iter].id);
		iter++;
	}
	while (waitpid(-1, &stat, 0) > 0)
		if (WIFEXITED(stat))
			ft_killall(data);
	// sem_wait(data->s_lock);
	return (1);
}
// void	halt_simulation(t_share_data *data)
// {
// 	sem_close(data->g_lock);
// 	sem_unlink("/sem");
// 	sem_close(data->d_lock);
// 	sem_unlink("/d_");
// 	sem_close(data->w_lock);
// 	sem_unlink("/w_");
// 	sem_close(data->e_lock);
// 	sem_unlink("/e_");
// 	sem_close(data->e_lock);
// 	sem_unlink("/b_");
// }

int main(int ac, char **av)
{
	t_share_data data;
	t_philo		philos[MAX_P];
	int 		iter;

	iter = 0;
	if (ac <= 4)
		return (puts("error\n"), 1);
	
	if (!data_init(ac, av, &data))
		return (puts("Error\n"), 1);
	if (!open_sem(&data))
		exit(10);
	simulate(&data, philos);
	// printf("%lu", data.philo_num);
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
	// halt_simulation(&data);
}
