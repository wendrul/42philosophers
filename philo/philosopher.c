#include "philo.h"

void	*philosopher(void *philo_ptr)
{
	t_philo *philo;

	philo = (t_philo*)philo_ptr;
	print_status(*philo, PHILO_FORK);
	return (NULL);
}