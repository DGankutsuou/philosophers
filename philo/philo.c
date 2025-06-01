/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blessed <blessed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:05:31 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/01 21:30:03 by blessed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life_cycle(void *data)
{
	t_args	*args;

	args = (t_args *)data;
	if (args->number_of_philos % 2 == 0)
		even_cycle(args);
	else
		even_cycle(args);
}
