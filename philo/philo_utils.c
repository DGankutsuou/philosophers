/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:21:37 by blessed           #+#    #+#             */
/*   Updated: 2025/06/08 15:38:58 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isnemeric(char *s)
{
	if (!s)
		return (FALSE);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (FALSE);
		s++;
	}
	return (TRUE);
}

int	ft_atoi(const char *str)
{
	int	nbr;
	int	sign;

	if (!str)
		return (0);
	nbr = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + *str - '0';
		str++;
	}
	return (nbr * sign);
}

unsigned long	ft_current_time(void)
{
	struct timeval	tv;
	unsigned long	ctime;

	ctime = 0;
	gettimeofday(&tv, NULL);
	ctime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ctime);
}
