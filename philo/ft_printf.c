/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:38:24 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/26 14:26:24 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_printf(t_philo *philo, char *str)
{
	int	ret;

	pthread_mutex_lock(&philo->args->strup);
	ret = printf ("%ld %d %s\n", ft_current_time() - \
		philo->args->startup, philo->nr, str);
	pthread_mutex_unlock(&philo->args->strup);
	return (ret);
}
