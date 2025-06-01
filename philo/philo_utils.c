/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blessed <blessed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:21:37 by blessed           #+#    #+#             */
/*   Updated: 2025/06/01 18:18:10 by blessed          ###   ########.fr       */
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
