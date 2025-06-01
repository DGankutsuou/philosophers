/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:05:34 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/01 11:10:11 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_args	t_args;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				sr;
	unsigned long	last_time_eaten;
	int				meals_counter;
	pthread_mutex_t	left_stick;
	pthread_mutex_t	right_stick;
	t_args			*args;
}	t_philo;

struct s_args
{
	int				number_of_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				minimum_meals;
	int				someone_dead;
	pthread_mutex_t	*sticks;
	t_philo			*philos;
};

#endif
