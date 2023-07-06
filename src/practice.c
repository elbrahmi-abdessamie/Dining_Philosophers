#include "../Include/philo.h"

int x = 0;
pthread_mutex_t mutex;
void	*stat()
{
	for(int i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(&mutex);
		x++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
int		thread_init(pthread_t *threads, int n_thread)
{
	for(int i = 0; i < n_thread; i++)
	{
		printf("Thread %d started counting...\n", i + 1);
		printf("x => %d\n", x);
		if (pthread_create(&threads[i], NULL, &stat, NULL))
			return (puts("Failed to create thread\n"), 1);
		usleep(50000);
		if (pthread_join(threads[i], NULL))
			return (puts("Failed to join thread\n"), 2);
		printf("Thread %d end counting...\n", i + 1);
		printf("x => %d\n", x);
	}
	return 0;
}
int		t_create(char *av)
{
	int n_philo = atoi(av);
	pthread_t	tr[n_philo];
	pthread_mutex_init(&mutex, NULL);
	
	// if (pthread_create(&tr1, NULL, &stat, NULL))
	// 	return 1;
	// if (pthread_create(&tr2, NULL, &stat, NULL))
	// 	return 2;
	// pthread_join(tr1, NULL);
	// pthread_join(tr2, NULL);
	return (thread_init(tr, n_philo));
}
int main(int ac, char **av)
{
	if (t_create(av[1]))
		puts("Error\n");	
	printf("\b x value => %d\n", x);
	return 0;
}