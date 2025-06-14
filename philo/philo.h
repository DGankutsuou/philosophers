/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:05:34 by aabouriz          #+#    #+#             */
/*   Updated: 2025/06/14 18:10:32 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args	t_args;

# define FALSE 0
# define TRUE 1
# define ERROR 1
# define SUCCESS 0
# define FAILURE -1

typedef struct s_philo
{
	pthread_t		thread_id;
	int				nr;
	unsigned long	last_time_eaten;
	int				meals_counter;
	pthread_mutex_t	*left_stick;
	pthread_mutex_t	*right_stick;
	t_args			*args;
}	t_philo;

struct s_args
{
	int				number_of_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_think;
	int				minimum_meals;
	int				someone_dead;
	int				end_of_story;
	unsigned long	startup;
	pthread_mutex_t	*sticks;
	t_philo			*philos;
};

int				ft_isnemeric(char *s);
int				ft_atoi(const char *str);
void			action(t_args *args);
unsigned long	ft_current_time(void);
int				ft_sleep(unsigned long ms, t_args *args);
void			*watcher_job(void *data);

#endif
