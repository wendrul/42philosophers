/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:31:54 by ede-thom          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:10 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PHILO_EAT_MESSAGE "is eating"
# define PHILO_SLEEP_MESSAGE "is sleeping"
# define PHILO_THINK_MESSAGE "is thinking"
# define PHILO_FORK_MESSAGE "has taken a fork"
# define PHILO_FINISHED_MESSAGE "has taken a fork"
# define PHILO_DIED_MESSAGE "died"

# define USLEEP_INCREMENT 500

# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	int				remaining_meals;
	long			death_time;
	long			sleep_time;
	long			eat_time;
	int				finished_eating;
	time_t			last_ate;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}t_philo;

time_t	get_time(void);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *str, int fd);

void	*philosopher(void *philo);
void	print_status(t_philo philo, char *msg);

void	ft_usleep(useconds_t time_val);

#endif