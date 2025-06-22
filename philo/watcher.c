/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:46:16 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/22 07:02:36 by aabouriz         ###   ########.fr       */
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
	while (idx < args->number_of_philos)
	{
		pthread_mutex_unlock(args->philos[idx].left_stick);
		pthread_mutex_unlock(args->philos[idx].right_stick);
		idx++;
	}
}

static int	is_all_finish(t_args *args)
{
	int	idx;

	if (args->minimum_meals == -1)
		return (FALSE);
	idx = 0;
	while (idx < args->number_of_philos)
	{
		pthread_mutex_lock(&args->mcounter);
		if (args->philos[idx].meals_counter < args->minimum_meals)
			return (FALSE);
		pthread_mutex_unlock(&args->mcounter);
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
			printf ("%ld %d died\n", ft_current_time() - \
			args->startup, args->philos[idx].nr);
			pthread_mutex_unlock(&args->lteat);
			break ;
		}
		idx++;
		if (idx == args->number_of_philos)
			idx = 0;
	}
	unlocker(args);
	return (NULL);
}
