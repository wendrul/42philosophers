/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:16:46 by wendrul           #+#    #+#             */
/*   Updated: 2021/07/08 03:45:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"
#include "ft_error.h"

int parse_args(int argc, char **argv, t_philo **philos_ptr)
{
	t_philo referece_philo;
	t_philo *philos;
	int amount;
	int i;

	if (argc != 4 && argc != 5)
		return (error_exit(WRONG_NUMBER_OF_ARGS, -1));
	amount = ft_atoi(argv[1]);
	referece_philo.death_time = ft_atoi(argv[2]);
	referece_philo.eat_time = ft_atoi(argv[3]);
	referece_philo.sleep_time = ft_atoi(argv[4]);
	referece_philo.remaining_meals = -1;
	if (argc == 5)
		referece_philo.remaining_meals = ft_atoi(argv[4]);
	philos = (t_philo*)malloc(sizeof(t_philo) * (amount + 1));
	if (!philos)
		return (error_exit(MALLOC_FAIL, -1));
	i = -1;
	while (++i < amount)
	{
		philos[i].id = i + 1;
		philos[i].death_time = referece_philo.death_time;
		philos[i].eat_time = referece_philo.eat_time;
		philos[i].sleep_time = referece_philo.sleep_time;
		philos[i].remaining_meals = referece_philo.remaining_meals;
	}
	*philos_ptr = philos;
	return (amount);
}

static int start_threads(t_philo *philos, int amount)
{
	int i;
	pthread_t th_id;

	i= -1;
	while (++i < amount)
	{
		if (pthread_create(&th_id, NULL, philosopher, (void*)&philos[i]) != 0)
			return (error_exit(THREAD_CREATE_FAIL, -1));
		usleep(1000);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_philo *philos;
	int amount;

	amount = parse_args(argc, argv, &philos);
	if (amount == -1)
		return (1);
	if (start_threads(philos, amount) == -1)
		return (1);
	return (0);
}