/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:05:31 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/15 09:13:01 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	eat_sleep_think(t_philo *philo)
{
	int	stat;

	stat = 0;
	printf ("%ld %d is eating\n", ft_current_time() - \
	philo->args->startup, philo->nr);
	stat = ft_sleep(philo->args->time_to_eat, philo->args);
	sem_post(philo->args->sem);
	sem_post(philo->args->sem);
	if (stat == -1 || philo->args->end_of_story == TRUE)
		return (-1);
	printf ("%ld %d is sleeping\n", ft_current_time() - \
	philo->args->startup, philo->nr);
	stat = ft_sleep(philo->args->time_to_sleep, philo->args);
	if (philo->args->end_of_story == TRUE)
		return (-1);
	printf ("%ld %d is thinking\n", ft_current_time() - \
	philo->args->startup, philo->nr);
	stat = ft_sleep (philo->args->time_to_think, philo->args);
	return (stat);
}

void	*life_cycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (TRUE)
	{
		sem_wait(philo->args->sem);
		if (philo->args->end_of_story == TRUE)
			break ;
		printf ("%ld %d has taken a rfork\n", ft_current_time() - \
		philo->args->startup, philo->nr);
		sem_wait(philo->args->sem);
		if (philo->args->end_of_story == TRUE)
			break ;
		printf ("%ld %d has taken a lfork\n", ft_current_time() - \
		philo->args->startup, philo->nr);
		philo->last_time_eaten = ft_current_time();
		philo->meals_counter++;
		if (philo->args->end_of_story == TRUE)
			break ;
		if (eat_sleep_think(philo) == FAILURE)
			break ;
	}
	return (printf ("%d returned\n", philo->nr), NULL);
}

void	action(t_args *args)
{
	int	idx;
	int	pid;

	idx = 0;
	while (args->number_of_philos > idx)
	{
		pid = fork();
		if (pid != 0)
			args->philos[idx].id = pid;
		if (pid == 0)
		{
			life_cycle(&args->philos[idx]);
			exit (0);
		}
		idx++;
	}
	idx = 0;
	while (args->number_of_philos > idx)
	{
		waitpid(args->philos[idx].id, NULL, 0);
		idx++;
	}
}
