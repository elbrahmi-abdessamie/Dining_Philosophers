#include "../Include/philo.h"

// int x = 0;
// pthread_mutex_t mutex;
// void	*stat()
// {
// 	for(int i = 0; i < 10000; i++)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		x++;
// 		pthread_mutex_unlock(&mutex);
// 	}
// 	return NULL;
// }
// void	*russ_roll()
// {
// 	int val = (rand() % 6) + 1;
// 	x += val;
// 	printf("U've got => %d\n", val);
// 	return (NULL);
// }
// int		thread_init(pthread_t *threads, int n_thread)
// {
// 		puts("--------------- Dream on --------------\n");
// 		puts("---------- GET THE LUCKY ¬12¬ ------------\n");
// 	for(int i = 0; i < n_thread; i++)
// 	{
// 		// printf("Thread %d started counting...\n", i + 1);
// 		// printf("x => %d\n", x);
// 		if (pthread_create(&threads[i], NULL, &russ_roll, NULL))
// 			return (puts("Failed to create thread\n"), 1);
// 		// usleep(50000);
// 	}
// 	for(int i = 0; i < n_thread; i++)
// 	{
// 		if (pthread_join(threads[i], NULL))
// 			return (puts("Failed to join thread\n"), 2);
// 		// printf("Thread %d end counting...\n", i + 1);
// 		// printf("x => %d\n", x);
// 	}
// 		puts("---------------- wake up ---------------\n");
// 	return 0;
// }

// int		t_create(char *av)
// {
// 	int n_philo = atoi(av);
// 	pthread_t	tr[n_philo];
// 	pthread_mutex_init(&mutex, NULL);
	
// 	// if (pthread_create(&tr1, NULL, &stat, NULL))
// 	// 	return 1;
// 	// if (pthread_create(&tr2, NULL, &stat, NULL))
// 	// 	return 2;
// 	// pthread_join(tr1, NULL);
// 	// pthread_join(tr2, NULL);
// 	return (thread_init(tr, n_philo));
// }
// int main(int ac, char **av)
// {
// 	srand(time(NULL));
// 	float prs = 0.0000001;
// 	if (t_create(av[1]))
// 		puts("Error\n");	
// 	if (x == 12)
// 	{
// 		if (atoi(av[1]) == 2)
// 			printf("GOOD GAME YOU GOT %.7fBTC>\n", prs / pow(10, 2));
// 		else if (atoi(av[1]) > 2)
// 			printf("GOOD GAME YOU GOT %.7fBTC>\n", (prs * pow(10, (double)atoi(av[1]))));
// 	}	
// 	else{
// 		printf("GOOD LUCK NEXT TIMEπ\n");
// 	}
// 	return 0;
// }
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
	// data->philo[0].data = data;

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

void	ft_write_stat(char *str, t_philo *p)
{
	unsigned long	time;
	unsigned int	cur = p->data->start_sim_time;
	time = time_line() - cur;
	if (time >= 0 && !phil_death_check(p))
	{
		printf(" | %9lu |", time);
		printf(" | PHILO | | %d | | %s  %d   %d", p->pid, str, p->num_of_meal_taken, p->data->sim);
		// printf(" | PHILO | | %6d | | %18s ", p->pid, str);

	}
}
void routine(t_philo *p)
{
	pthread_mutex_lock(&p->l_fork);
	pthread_mutex_lock(&p->data->write_mtx);
	ft_write_stat("take the fork ||\n", p);
	pthread_mutex_unlock(&p->data->write_mtx);
	if (!p->r_fork)
	{
		ft_usleep(p->data->time_to_die + 1);

		return ;
	}
	pthread_mutex_lock(p->r_fork);
	pthread_mutex_lock(&p->data->write_mtx);
	ft_write_stat("take the fork ||\n", p);
	pthread_mutex_unlock(&p->data->write_mtx);
	pthread_mutex_lock(&p->data->write_mtx);
	ft_write_stat("eating ||\n", p);
	pthread_mutex_lock(&p->data->l_eat_time);
	p->last_meal = time_line();
	pthread_mutex_unlock(&p->data->l_eat_time);
	pthread_mutex_unlock(&p->data->write_mtx);
	ft_usleep(p->data->time_to_eat);
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(&p->l_fork);
	pthread_mutex_lock(&p->data->write_mtx);
	ft_write_stat("is sleeping ||\n", p);
	pthread_mutex_unlock(&p->data->write_mtx);
	ft_usleep(p->data->time_to_sleep);
	pthread_mutex_lock(&p->data->write_mtx);
	ft_write_stat("is thinking ||\n", p);
	pthread_mutex_unlock(&p->data->write_mtx);
}

void *thread(void *arg)
{
	t_philo	*phil;

	phil = (t_philo *)arg;
	syncro(phil);
	while (!phil_death_check(phil))
	{
		routine(phil);
		if (++phil->num_of_meal_taken == phil->data->num_of_meals)
		{
			pthread_mutex_lock(&phil->data->stat_p);
			phil->stat = TS_TERMINATED;
			phil->data->philo_die++;
			if (phil->data->philo_die == phil->data->philo_num)
			{
				pthread_mutex_unlock(&phil->data->stat_p);
				phil->data->sim = 1;
				phil_death_check(phil);
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
	// philos[0].pid = 2;
	// data.philo = philos;
	if (ac < 4)
		return (puts("error\n"), 1);
	if (!data_init(ac, av, &data))
		return (puts("Error\n"), 1);
	simulate(&data, philos);
	halt_simulation(&data);
}