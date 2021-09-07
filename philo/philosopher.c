#include "philo.h"



void	take_fork(t_philo philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	print_status(philo, PHILO_FORK_MESSAGE);
}

void	philo_eat(t_philo philo)
{
	print_status(philo, PHILO_EAT_MESSAGE);
	usleep(philo.eat_time);
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
}

void	philo_sleep(t_philo philo)
{
	print_status(philo, PHILO_SLEEP_MESSAGE);
	usleep(philo.sleep_time);
}

void	philo_think(t_philo philo)
{
	print_status(philo, PHILO_THINK_MESSAGE);
	usleep(philo.sleep_time);
}

void	*philosopher(void *philo_ptr)
{
	t_philo philo;

	philo = *(t_philo*)philo_ptr;
	while (philo.remaining_meals != 0)
	{
		take_fork(philo, philo.left_fork);
		take_fork(philo, philo.right_fork);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (philo.remaining_meals > 0)
			philo.remaining_meals--;
	}
	print_status(philo, "Finished eating bye");
	return (NULL);
}