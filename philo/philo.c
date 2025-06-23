/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:05:31 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/23 09:49:03 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	eat_sleep_think(t_philo *philo)
{
	int	stat;

	stat = 0;
	pthread_mutex_lock(&philo->args->strup);
	ft_printf (philo, "is eating");
	pthread_mutex_unlock(&philo->args->strup);

	stat = ft_sleep(philo->args->time_to_eat, philo->args);
	pthread_mutex_unlock(philo->left_stick);
	pthread_mutex_unlock(philo->right_stick);

	pthread_mutex_lock(&philo->args->end);
	if (stat == -1 || philo->args->end_of_story == TRUE)
		return (pthread_mutex_unlock(&philo->args->end), -1);
	pthread_mutex_unlock(&philo->args->end);

	pthread_mutex_lock(&philo->args->strup);
	ft_printf (philo, "is sleeping");
	pthread_mutex_unlock(&philo->args->strup);

	stat = ft_sleep(philo->args->time_to_sleep, philo->args);

	pthread_mutex_lock(&philo->args->end);
	if (philo->args->end_of_story == TRUE)
		return (pthread_mutex_unlock(&philo->args->end), -1);
	pthread_mutex_unlock(&philo->args->end);

	pthread_mutex_lock(&philo->args->strup);
	ft_printf (philo, "is thinking");
	pthread_mutex_unlock(&philo->args->strup);

	stat = ft_sleep (philo->args->time_to_think, philo->args);
	return (stat);
}

// static void take_left_fork(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->left_stick);
// 	pthread_mutex_lock(&philo->args->end);
// 	if (philo->args->end_of_story == TRUE)
// 	{
// 		pthread_mutex_unlock(&philo->args->end);
// 		pthread_mutex_unlock(philo->left_stick);
// 	}
// }

static void	*left_handed_philo(t_philo *philo)
{
	while (TRUE)
	{
		pthread_mutex_lock(philo->left_stick);
		pthread_mutex_lock(&philo->args->end);

		if (philo->args->end_of_story == TRUE)
		{
			pthread_mutex_unlock(&philo->args->end);
			pthread_mutex_unlock(philo->left_stick);
			break ;
		}

		pthread_mutex_unlock(&philo->args->end);
		pthread_mutex_lock(&philo->args->strup);
		ft_printf (philo, "has taken a lfork");
		pthread_mutex_unlock(&philo->args->strup);
		pthread_mutex_lock(philo->right_stick);
		pthread_mutex_lock(&philo->args->end);

		if (philo->args->end_of_story == TRUE)
		{
			pthread_mutex_unlock(&philo->args->end);
			pthread_mutex_unlock(philo->left_stick);
			pthread_mutex_unlock(philo->right_stick);
			break ;
		}

		pthread_mutex_unlock(&philo->args->end);
		pthread_mutex_lock(&philo->args->strup);
		ft_printf (philo, "has taken a rfork");
		pthread_mutex_unlock(&philo->args->strup);
		pthread_mutex_lock(&philo->args->lteat);
		philo->last_time_eaten = ft_current_time();
		pthread_mutex_unlock(&philo->args->lteat);
		pthread_mutex_lock(&philo->args->mcounter);
		philo->meals_counter++;
		pthread_mutex_unlock(&philo->args->mcounter);
		pthread_mutex_lock(&philo->args->end);

		if (philo->args->end_of_story == TRUE)
		{
			pthread_mutex_unlock(&philo->args->end);
			pthread_mutex_unlock(philo->left_stick);
			pthread_mutex_unlock(philo->right_stick);
			break ;
		}

		pthread_mutex_unlock(&philo->args->end);
		if (eat_sleep_think(philo) == FAILURE)
			break ;
	}
	return (printf ("%d returned\n", philo->nr), NULL);
}

static void	*right_handed_philo(t_philo *philo)
{
	while (TRUE)
	{
		pthread_mutex_lock(philo->right_stick);
		pthread_mutex_lock(&philo->args->end);
		if (philo->args->end_of_story == TRUE)
		{
			pthread_mutex_unlock(&philo->args->end);
			pthread_mutex_unlock(philo->right_stick);
			break ;
		}
		pthread_mutex_unlock(&philo->args->end);
		pthread_mutex_lock(&philo->args->strup);
		ft_printf (philo, "has taken a rfork");
		pthread_mutex_unlock(&philo->args->strup);
		pthread_mutex_lock(philo->left_stick);
		pthread_mutex_lock(&philo->args->end);
		if (philo->args->end_of_story == TRUE)
		{
			pthread_mutex_unlock(&philo->args->end);
			pthread_mutex_unlock(philo->left_stick);
			pthread_mutex_unlock(philo->right_stick);
			break ;
		}
		pthread_mutex_unlock(&philo->args->end);
		pthread_mutex_lock(&philo->args->strup);
		ft_printf (philo, "has taken a lfork");
		pthread_mutex_unlock(&philo->args->strup);
		pthread_mutex_lock(&philo->args->lteat);
		philo->last_time_eaten = ft_current_time();
		pthread_mutex_unlock(&philo->args->lteat);
		pthread_mutex_lock(&philo->args->mcounter);
		philo->meals_counter++;
		pthread_mutex_unlock(&philo->args->mcounter);
		pthread_mutex_lock(&philo->args->end);
		if (philo->args->end_of_story == TRUE)
		{
			pthread_mutex_unlock(&philo->args->end);
			pthread_mutex_unlock(philo->left_stick);
			pthread_mutex_unlock(philo->right_stick);
			break ;
		}
		pthread_mutex_unlock(&philo->args->end);
		if (eat_sleep_think(philo) == FAILURE)
			break ;
	}
	return (printf ("%d returned\n", philo->nr), NULL);
}

void	*life_cycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_sleep_until_start(philo->args, e_watcher);
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
		pthread_mutex_lock(&args->phcounter);
		args->philos_counter++;
		pthread_mutex_unlock(&args->phcounter);
	}
	idx = 0;
	while (args->number_of_philos > idx)
	{
		pthread_join(args->philos[idx].thread_id, NULL);
		idx++;
	}
}
