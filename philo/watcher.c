/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:46:16 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/26 09:41:39 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unlocker(t_args *args)
{
	int	idx;

	idx = 0;
	pthread_mutex_lock(&args->end);
	args->end_of_story = TRUE;
	pthread_mutex_unlock(&args->end);
}

static int	is_all_finish(t_args *args)
{
	int	idx;

	if (args->minimum_meals == -1)
		return (FALSE);
	idx = 0;
	while (idx < args->number_of_philos)
	{
		pthread_mutex_lock(&args->philos[idx].mcounter);
		if (args->philos[idx].meals_counter < args->minimum_meals)
			return (FALSE);
		pthread_mutex_unlock(&args->philos[idx].mcounter);
		idx++;
	}
	return (TRUE);
}

void	*watcher_job(void *data)
{
	int		idx;
	t_args	*args;

	args = (t_args *)data;
	idx = 0;
	ft_sleep_until_start(args, e_watcher);
	// args->startup = ft_current_time();
	while (1)
	{
		if (is_all_finish(args) == TRUE)
			break ;
		pthread_mutex_lock(&args->lteat);
		if (ft_current_time() - args->philos[idx].last_time_eaten \
		> (size_t)args->time_to_die)
		{
			pthread_mutex_lock(&args->strup);
			ft_printf (&args->philos[idx], "died");
			pthread_mutex_unlock(&args->strup);
			pthread_mutex_unlock(&args->lteat);
			break ;
		}
		pthread_mutex_unlock(&args->lteat);
		idx++;
		if (idx == args->number_of_philos)
			idx = 0;
	}
	unlocker(args);
	return (NULL);
}
