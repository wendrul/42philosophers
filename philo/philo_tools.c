#include "philo.h"

void	print_status(t_philo philo, char *msg)
{
	static time_t start_time = 0;

	if (start_time == 0)
		start_time = get_time();
	printf("%-7ld %-2d %s\n", get_time() - start_time, philo.id, msg);
}