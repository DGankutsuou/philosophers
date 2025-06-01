/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blessed <blessed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:05:23 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/01 18:31:56 by blessed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_args(char **argv)
{
	int	index;

	index = 0;
	while (argv[index] != NULL)
	{
		if (ft_isnemeric(argv[index]) == FALSE || ft_atoi(argv[index] < 1))
			return (ERROR);
		index++;
	}
	if (index < 3 || index > 4)
		return (ERROR);
	return (SUCCESS);
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
	if (argv[4] != NULL)
		(*args)->minimum_meals = ft_atoi(argv[4]);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_args	*args;

	if (init_args(argv + 1, &args))
	{
		write (STDERR_FILENO, "error: invalid arguments\n", 26);
		return (ERROR);
	}
	printf("- %d -\n", );
}
