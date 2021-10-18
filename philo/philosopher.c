/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:33:34 by ede-thom          #+#    #+#             */
/*   Updated: 2021/10/18 13:17:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	print_status(philo, PHILO_FORK_MESSAGE, 0);
}

void	philo_eat(t_philo philo)
{
	print_status(philo, PHILO_EAT_MESSAGE, 0);
	ft_usleep(philo.eat_time * 1000);
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
}

void	philo_sleep(t_philo philo)
{
	print_status(philo, PHILO_SLEEP_MESSAGE, 0);
	ft_usleep(philo.sleep_time * 1000);
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
	if (philo.id % 2 == 1)
		usleep(1000 * (philo.eat_time / 2));
	while (!is_sim_end(philo) && philo.remaining_meals != 0)
	{
		take_fork(philo, philo.left_fork);
		if (philo.amount_of_philos == 1)
			return (NULL);
		take_fork(philo, philo.right_fork);
		pthread_mutex_lock(philo.get_time_lock);
		philo_ptr2->last_ate = get_time();
		pthread_mutex_unlock(philo.get_time_lock);
		philo_eat(philo);
		if (philo.remaining_meals > 0)
			philo.remaining_meals--;
		if (philo.remaining_meals == 0 || is_sim_end(philo))
			break;
		philo_sleep(philo);
		philo_think(philo);
	}
	philo_ptr2->finished_eating = 1;
	return (NULL);
}
