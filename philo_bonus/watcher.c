/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:46:16 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/15 16:51:13 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_them_all(t_args *args)
{
	int	iter;

	iter = 0;
	while (iter < args->number_of_philos)
	{
		kill(args->philos[iter].id, SIGKILL);
		iter++;
	}
	sem_close(args->sem);
}

static int	is_all_finish(t_args *args)
{
	int	idx;

	if (args->minimum_meals == -1)
		return (FALSE);
	idx = 0;
	while (idx < args->number_of_philos)
	{
		if (args->philos[idx].meals_counter < args->minimum_meals)
			return (FALSE);
		idx++;
	}
	return (TRUE);
}

void	*watcher_job(void *data)
{
	int		idx;
	t_args	*args;
	int		finishers;

	args = (t_args *)data;
	idx = 0;
	finishers = 0;
	while (1)
	{
		if (is_all_finish(args) == TRUE)
			break ;
		if (ft_current_time() - args->philos[idx].last_time_eaten \
		> (size_t)args->time_to_die)
		{
			printf ("%ld %d died\n", ft_current_time() - \
			args->startup, args->philos[idx].nr);
			break ;
		}
		idx++;
		if (idx == args->number_of_philos)
			idx = 0;
	}
	kill_them_all(args);
	return (NULL);
}
