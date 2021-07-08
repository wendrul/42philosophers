#include "philo.h"

char *philo_message(int status)
{
	if (status == PHILO_EAT)
		return (PHILO_EAT_MESSAGE);
	else if (status == PHILO_SLEEP)
		return (PHILO_SLEEP_MESSAGE);
	else if (status == PHILO_THINK)
		return (PHILO_THINK_MESSAGE);
	else if (status == PHILO_DIED)
		return (PHILO_DIED_MESSAGE);
	else if (status == PHILO_FORK)
		return (PHILO_FORK_MESSAGE);
	else
		return("unknown status");
}

void	print_status(t_philo philo, int status)
{
	static time_t start_time = 0;

	if (start_time == 0)
		start_time = get_time();
	printf("%-10ld %-2d %s\n", get_time() - start_time, philo.id, philo_message(status));
}