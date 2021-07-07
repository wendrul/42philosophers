#ifndef PHILO_H
# define PHILO_H


typedef struct s_philo
{
	int		id;
	int		remaining_meals;
	long	death_time;
	long	sleep_time;
	long	eat_time;
}t_philo;

#endif