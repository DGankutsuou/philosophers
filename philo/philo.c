/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blessed <blessed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:05:31 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/09 17:10:17 by blessed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*left_handed_philo(t_philo *philo)
{
	while (TRUE)
	{
		int	stat;

		stat = 0;
		pthread_mutex_lock(philo->left_stick);
		if (philo->args->end_of_story == TRUE)
			break ;
		printf ("%ld %d has taken a lfork\n", ft_current_time() - philo->args->startup, philo->nr);
		pthread_mutex_lock(philo->right_stick);
		if (philo->args->end_of_story == TRUE)
			break ;
		printf ("%ld %d has taken a rfork\n", ft_current_time() - philo->args->startup, philo->nr);
		philo->last_time_eaten = ft_current_time();
		philo->meals_counter++;
		if (stat == -1 || philo->args->end_of_story == TRUE)
			break ;
		printf ("%ld %d is eating\n", ft_current_time() - philo->args->startup, philo->nr);
		stat = ft_sleep(philo->args->time_to_eat, philo->args);
		pthread_mutex_unlock(philo->left_stick);
		pthread_mutex_unlock(philo->right_stick);
		if (stat == -1 || philo->args->end_of_story == TRUE)
			break ;
		printf ("%ld %d is sleeping\n", ft_current_time() - philo->args->startup, philo->nr);
		stat = ft_sleep(philo->args->time_to_sleep, philo->args);
		if (philo->args->end_of_story == TRUE)
			break ;
		printf ("%ld %d is thinking\n", ft_current_time() - philo->args->startup, philo->nr);
	}
	return (printf ("%d returned\n", philo->nr), NULL);
}

static void	*right_handed_philo(t_philo *philo)
{
	while (TRUE)
	{
		int	stat;

		stat = 0;
		pthread_mutex_lock(philo->right_stick);
		if (philo->args->end_of_story == TRUE)
			break ;
		printf ("%ld %d has taken a rfork\n", ft_current_time() - philo->args->startup, philo->nr);
		pthread_mutex_lock(philo->left_stick);
		if (philo->args->end_of_story == TRUE)
			break ;
		printf ("%ld %d has taken a lfork\n", ft_current_time() - philo->args->startup, philo->nr);
		philo->last_time_eaten = ft_current_time();
		philo->meals_counter++;
		if (stat == -1 || philo->args->end_of_story == TRUE)
			break ;
		printf ("%ld %d is eating\n", ft_current_time() - philo->args->startup, philo->nr);
		stat = ft_sleep(philo->args->time_to_eat, philo->args);
		pthread_mutex_unlock(philo->left_stick);
		pthread_mutex_unlock(philo->right_stick);
		if (stat == -1 || philo->args->end_of_story == TRUE)
			break ;
		printf ("%ld %d is sleeping\n", ft_current_time() - philo->args->startup, philo->nr);
		stat = ft_sleep(philo->args->time_to_sleep, philo->args);
		if (philo->args->end_of_story == TRUE)
			break ;
		printf ("%ld %d is thinking\n", ft_current_time() - philo->args->startup, philo->nr);
	}
	return (printf ("%d returned\n", philo->nr), NULL);
}

void	*life_cycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->nr % 2 == 0)
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
