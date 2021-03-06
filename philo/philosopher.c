/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:32:22 by ede-thom          #+#    #+#             */
/*   Updated: 2021/10/18 13:11:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo philo)
{
	while (!is_sim_end(philo))
	{
		if (pthread_mutex_lock(philo.left_fork) == 0)
		{
			if (pthread_mutex_lock(philo.right_fork) == 0)
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
	pthread_mutex_unlock(philo.right_fork);
	pthread_mutex_unlock(philo.left_fork);
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
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (philo->remaining_meals != 0)
	{
		if (take_forks(*philo))
		{
			print_status(*philo, PHILO_FORK_MESSAGE, 0);
			print_status(*philo, PHILO_FORK_MESSAGE, 0);
		}
		else
			break ;
		philo->last_ate = get_time();
		if (philo->remaining_meals > 0)
			philo->remaining_meals--;
		philo_eat(*philo);
		philo_sleep(*philo);
		philo_think(*philo);
		usleep(10);
	}
	philo->finished_eating = 1;
	return (NULL);
}
