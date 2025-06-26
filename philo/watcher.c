/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:46:16 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/26 15:56:31 by aabouriz         ###   ########.fr       */
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
	if (args->number_of_philos == 1)
		pthread_mutex_unlock(args->philos[0].right_stick);
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
			return (pthread_mutex_unlock(&args->philos[idx].mcounter), FALSE);
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
		pthread_mutex_lock(&args->philos[idx].lteat);
		if (ft_current_time() - args->philos[idx].last_time_eaten \
		> (size_t)args->time_to_die)
		{
			ft_printf (&args->philos[idx], "died");
			pthread_mutex_unlock(&args->philos[idx].lteat);
			break ;
		}
		pthread_mutex_unlock(&args->philos[idx].lteat);
		idx++;
		if (idx == args->number_of_philos)
			idx = 0;
	}
	unlocker(args);
	return (NULL);
}
