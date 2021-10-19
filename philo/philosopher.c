#include "philo.h"

int take_forks(t_philo philo)
{
    while (!*(philo.simulation_end))
    {
        if (pthread_mutex_lock(philo.left_fork))
        {
            if (pthread_mutex_lock(philo.right_fork))
                return (1);
            pthread_mutex_unlock(philo.left_fork);
        }
    }
    return (0);
}

void	philo_eat(t_philo philo)
{
	print_status(philo, PHILO_EAT_MESSAGE, 0);
	ft_usleep(philo.eat_time * 1000, philo);
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
}

void	philo_sleep(t_philo philo)
{
	print_status(philo, PHILO_SLEEP_MESSAGE, 0);
	ft_usleep(philo.sleep_time * 1000, philo);
}

void	philo_think(t_philo philo)
{
	print_status(philo, PHILO_THINK_MESSAGE, 0);
}

void	*philosopher(void *philo_ptr)
{
	t_philo	philo;
	t_philo	*philo_ptr2;

	philo = *(t_philo *)philo_ptr;
	philo_ptr2 = (t_philo *)philo_ptr;
    while(philo.remaining_meals != 0)
    {
        if (take_forks(philo))
        {
            print_status(philo, PHILO_FORK_MESSAGE, 0);
            print_status(philo, PHILO_FORK_MESSAGE, 0);
        }
        else
            break;
        pthread_mutex_lock(philo.get_time_lock);
        philo_ptr2->last_ate = get_time();
        pthread_mutex_unlock(philo.get_time_lock);
        if (philo.remaining_meals > 0)
			philo.remaining_meals--;
        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
    }
    printf("hey %d finished\n", philo.id);
    philo_ptr2->finished_eating = 1;
    return (NULL);
}