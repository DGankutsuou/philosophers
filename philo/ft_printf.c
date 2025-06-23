/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:38:24 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/23 09:50:37 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_printf(t_philo *philo, char *str)
{
	static pthread_mutex_t	print = PTHREAD_MUTEX_INITIALIZER;
	int						ret;

	pthread_mutex_lock(&print);
	ret = printf ("%ld %d %s\n", ft_current_time() - \
		philo->args->startup, philo->nr, str);
	pthread_mutex_unlock(&print);
	return (ret);
}
