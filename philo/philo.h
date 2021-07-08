#ifndef PHILO_H
# define PHILO_H

# define PHILO_EAT 69
# define PHILO_SLEEP 70
# define PHILO_THINK 71
# define PHILO_FORK 72
# define PHILO_DIED 73

# define PHILO_EAT_MESSAGE "is eating"
# define PHILO_SLEEP_MESSAGE "is sleeping"
# define PHILO_THINK_MESSAGE "is thinking"
# define PHILO_FORK_MESSAGE "has taken a fork"
# define PHILO_DIED_MESSAGE "died"

# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	int		id;
	int		remaining_meals;
	long	death_time;
	long	sleep_time;
	long	eat_time;
}t_philo;

time_t	get_time(void);
int		ft_atoi(char *str);

#endif