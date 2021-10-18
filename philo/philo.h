/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:31:54 by ede-thom          #+#    #+#             */
/*   Updated: 2021/09/08 15:52:42 by ede-thom         ###   ########.fr       */
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
	int				amount_of_philos;
	int				remaining_meals;
	long			death_time;
	long			sleep_time;
	long			eat_time;
	int				finished_eating;
	char			*simulation_end;
	time_t			last_ate;
	time_t			born_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t *get_time_lock;
	pthread_mutex_t	*printer;
}t_philo;

time_t	get_time();
time_t	get_time_protected(t_philo philo);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *str, int fd);

int		is_sim_end(t_philo philo);
void	end_sim(t_philo philo);

int		parse_args(int argc, char **argv, t_philo **philos_ptr);
int		get_ref(int argc, char **argv, t_philo *ref_philo);

void	*philosopher(void *philo);
void	print_status(t_philo philo, char *msg, int death);

void	ft_usleep(useconds_t time_val);

#endif