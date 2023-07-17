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

int main(int ac, char **av)
{
	t_share_data data;
	t_philo		philos[MAX_P];
	if (ac < 4)
		return (puts("error\n"), 1);
	if (!data_init(ac, av, &data))
		return (puts("Error\n"), 1);
	printf("philo num = %lu | time to eat = %lu | time to die = %lu | time to sleep = %lu", data.philo_num, data.time_to_eat, data.time_to_die, data.time_to_sleep);
}