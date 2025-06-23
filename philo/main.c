/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:05:23 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/23 08:23:44 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_args(char **argv)
{
	int	index;

	index = 0;
	while (argv[index] != NULL)
	{
		if (ft_isnemeric(argv[index]) == FALSE || ft_atoi(argv[index]) < 1)
			return (ERROR);
		index++;
	}
	if (index < 4 || index > 5)
		return (ERROR);
	return (SUCCESS);
}

static void	init_philos_and_sticks(t_args *args)
{
	int	idx;

	idx = 0;
	while (idx < args->number_of_philos)
	{
		args->philos[idx].args = args;
		args->philos[idx].nr = idx + 1;
		args->philos[idx].meals_counter = 0;
		args->philos[idx].last_time_eaten = args->startup;
		args->philos[idx].left_stick = &args->sticks[idx];
		args->philos[idx].right_stick = &args->sticks[(idx + 1) % \
		args->number_of_philos];
		idx++;
	}
	idx = 0;
	while (idx < args->number_of_philos)
	{
		pthread_mutex_init(&args->sticks[idx], NULL);
		idx++;
	}
	pthread_mutex_init(&args->end, NULL);
	pthread_mutex_init(&args->mcounter, NULL);
	pthread_mutex_init(&args->lteat, NULL);
	pthread_mutex_init(&args->strup, NULL);
	pthread_mutex_init(&args->start_mutex, NULL);
	pthread_mutex_init(&args->phcounter, NULL);
}

static int	init_args(char **argv, t_args **args)
{
	if (validate_args(argv) == ERROR)
		return (ERROR);
	*args = (t_args *)malloc(sizeof(t_args));
	(*args)->number_of_philos = ft_atoi(argv[0]);
	(*args)->time_to_die = ft_atoi(argv[1]);
	(*args)->time_to_eat = ft_atoi(argv[2]);
	(*args)->time_to_sleep = ft_atoi(argv[3]);
	(*args)->time_to_think = ft_atoi(argv[1]) - ft_atoi(argv[2]) \
	- ft_atoi(argv[3]);
	(*args)->minimum_meals = -1;
	if (argv[4] != NULL)
		(*args)->minimum_meals = ft_atoi(argv[4]);
	(*args)->someone_dead = 0;
	(*args)->sticks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* (*args)->number_of_philos);
	(*args)->philos = (t_philo *)malloc(sizeof(t_philo) \
		* (*args)->number_of_philos);
	(*args)->startup = ft_current_time();
	(*args)->end_of_story = FALSE;
	(*args)->start = FALSE;
	(*args)->philos_counter = 0;
	init_philos_and_sticks(*args);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_args		*args;
	pthread_t	watcher;

	(void)argc;
	if (init_args(argv + 1, &args))
	{
		write (STDERR_FILENO, "error: invalid arguments\n", 26);
		return (ERROR);
	}
	pthread_create(&watcher, NULL, watcher_job, args);
	action(args);
	pthread_join(watcher, NULL);
	return (SUCCESS);
}
