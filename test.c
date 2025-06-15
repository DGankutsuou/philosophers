# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

void	*lion(void *data)
{
	sem_t	*sem = (sem_t *)data;

	sem_wait(sem);
	printf ("Rwaaaaaaaaaaaaaaaaaaaaaaaaaaar\n");
	sleep(1);
	sem_post(sem);
	exit (0);
	return (NULL);
}

int	main(void)
{
	sem_t	*sem;
	int		pid1;
	int		pid2;

	sem = sem_open("/semsem", O_CREAT, 0666, 1);
	pid1 = fork();
	if (pid1 == 0)
		lion(sem);
	pid2 = fork();
	if (pid2 == 0)
		lion(sem);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
