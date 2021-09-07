/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:33:34 by ede-thom          #+#    #+#             */
/*   Updated: 2021/09/07 15:34:36 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	print_status(philo, PHILO_FORK_MESSAGE);
}

void	philo_eat(t_philo philo)
{
	print_status(philo, PHILO_EAT_MESSAGE);
	ft_usleep(philo.eat_time * 1000);
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
}

void	philo_sleep(t_philo philo)
{
	print_status(philo, PHILO_SLEEP_MESSAGE);
	ft_usleep(philo.sleep_time * 1000);
}

void	philo_think(t_philo philo)
{
	print_status(philo, PHILO_THINK_MESSAGE);
}

void	*philosopher(void *philo_ptr)
{
	t_philo	philo;
	t_philo	*philo_ptr2;

	philo = *(t_philo *)philo_ptr;
	philo_ptr2 = (t_philo *)philo_ptr;
	if (philo.id % 2 == 1)
	{
		usleep(1000 * (philo.eat_time / 2));
	}
	while (philo.remaining_meals != 0)
	{
		take_fork(philo, philo.left_fork);
		take_fork(philo, philo.right_fork);
		philo_ptr2->last_ate = get_time();
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (philo.remaining_meals > 0)
			philo.remaining_meals--;
	}
	philo_ptr2->finished_eating = 1;
	return (NULL);
}
