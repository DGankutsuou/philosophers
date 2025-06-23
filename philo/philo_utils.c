/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:21:37 by blessed           #+#    #+#             */
/*   Updated: 2025/06/23 09:19:10 by aabouriz         ###   ########.fr       */
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

void	ft_sleep_until_start(t_args *args, t_identity philo_or_watcher)
{
	if (philo_or_watcher == e_watcher)
	{
		pthread_mutex_lock(&args->phcounter);
		while (args->philos_counter < args->number_of_philos)
		{
			pthread_mutex_unlock(&args->phcounter);
			usleep(1);
			pthread_mutex_lock(&args->phcounter);
		}
		pthread_mutex_unlock(&args->phcounter);
		pthread_mutex_lock(&args->strup);
		args->startup = ft_current_time();
		pthread_mutex_unlock(&args->strup);
		pthread_mutex_lock(&args->start_mutex);
		args->start = TRUE;
		pthread_mutex_unlock(&args->start_mutex);
	}
	else if (philo_or_watcher == e_philo)
	{
		while (args->start == FALSE)
		{
			usleep(1);
		}
	}

}

int	ft_sleep(unsigned long ms, t_args *args)
{
	unsigned long	current;
	unsigned long	startup;

	startup = ft_current_time();
	current = ft_current_time();
	while (current - startup < ms)
	{
		usleep(1);
		pthread_mutex_lock(&args->end);
		if (args->end_of_story == TRUE)
			return (pthread_mutex_unlock(&args->end), ERROR);
		pthread_mutex_unlock(&args->end);
		current = ft_current_time();
	}
	return (SUCCESS);
}
