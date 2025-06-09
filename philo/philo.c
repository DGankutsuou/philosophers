/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:05:31 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/09 10:56:05 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*left_handed_philo(t_philo *philo)
{
	while (TRUE)
	{
		int	stat;

		stat = 0;
		if (philo->args->end_of_story == TRUE)
			return (NULL);
		pthread_mutex_lock(philo->left_stick);
		printf ("%ld %d has taken a fork\n", ft_current_time() - philo->args->startup, philo->nr);
		pthread_mutex_lock(philo->right_stick);
		printf ("%ld %d has taken a fork\n", ft_current_time() - philo->args->startup, philo->nr);
		philo->last_time_eaten = ft_current_time();
		philo->meals_counter++;
		printf ("%ld %d is eating\n", ft_current_time() - philo->args->startup, philo->nr);
		stat = ft_sleep(philo->args->time_to_eat, philo->args);
		if (stat == -1 || philo->args->end_of_story == TRUE)
			return (NULL);
		pthread_mutex_unlock(philo->left_stick);
		pthread_mutex_unlock(philo->right_stick);
		printf ("%ld %d is sleeping\n", ft_current_time() - philo->args->startup, philo->nr);
		stat = ft_sleep(philo->args->time_to_sleep, philo->args);
		if (stat == -1 || philo->args->end_of_story == TRUE)
			return (NULL);
		printf ("%ld %d is thinking\n", ft_current_time() - philo->args->startup, philo->nr);
	}
	return (NULL);
}

static void	*right_handed_philo(t_philo *philo)
{
	while (TRUE)
	{
		int	stat;

		stat = 0;
		if (philo->args->end_of_story == TRUE)
			return (NULL);
		pthread_mutex_lock(philo->right_stick);
		printf ("%ld %d has taken a fork\n", ft_current_time() - philo->args->startup, philo->nr);
		pthread_mutex_lock(philo->left_stick);
		printf ("%ld %d has taken a fork\n", ft_current_time() - philo->args->startup, philo->nr);
		philo->last_time_eaten = ft_current_time();
		philo->meals_counter++;
		printf ("%ld %d is eating\n", ft_current_time() - philo->args->startup, philo->nr);
		stat = ft_sleep(philo->args->time_to_eat, philo->args);
		if (stat == -1 || philo->args->end_of_story == TRUE)
			return (NULL);
		pthread_mutex_unlock(philo->left_stick);
		pthread_mutex_unlock(philo->right_stick);
		printf ("%ld %d is sleeping\n", ft_current_time() - philo->args->startup, philo->nr);
		stat = ft_sleep(philo->args->time_to_sleep, philo->args);
		if (stat == -1 || philo->args->end_of_story == TRUE)
			return (NULL);
		printf ("%ld %d is thinking\n", ft_current_time() - philo->args->startup, philo->nr);
	}
	return (NULL);
}

void	*life_cycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->args->number_of_philos % 2 == 0)
		return (left_handed_philo(philo));
	else
		return (right_handed_philo(philo));
	return (NULL);
}

void	action(t_args *args)
{
	int	idx;

	idx = 0;
	while (args->number_of_philos > idx)
	{
		if (pthread_create(&args->philos[idx].thread_id, \
			NULL, life_cycle, &args->philos[idx]) == -1)
			{
				printf ("Error: failed to creat thread\n");
				return ;
			}
		idx++;
	}
	idx = 0;
	while (args->number_of_philos > idx)
	{
		pthread_join(args->philos[idx].thread_id, NULL);
		idx++;
	}
}
