/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:16:46 by wendrul           #+#    #+#             */
/*   Updated: 2021/09/07 14:47:58 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"
#include "ft_error.h"

int parse_args(int argc, char **argv, t_philo **philos_ptr)
{
	t_philo reference_philo;
	t_philo *philos;
	int amount;
	int i;

	if (argc != 5 && argc != 6)
		return (error_exit(WRONG_NUMBER_OF_ARGS, -1));
	amount = ft_atoi(argv[1]);
	reference_philo.death_time = ft_atoi(argv[2]);
	reference_philo.eat_time = ft_atoi(argv[3]);
	reference_philo.sleep_time = ft_atoi(argv[4]);
	reference_philo.remaining_meals = -1;
	reference_philo.finished_eating = 0;
	reference_philo.last_ate = get_time();
	if (argc == 6)
		reference_philo.remaining_meals = ft_atoi(argv[5]);
	philos = (t_philo*)malloc(sizeof(t_philo) * (amount + 1));
	if (!philos)
		return (error_exit(MALLOC_FAIL, -1));
	i = -1;
	while (++i < amount)
	{
		philos[i].id = i + 1;
		philos[i].death_time = reference_philo.death_time;
		philos[i].eat_time = reference_philo.eat_time;
		philos[i].sleep_time = reference_philo.sleep_time;
		philos[i].remaining_meals = reference_philo.remaining_meals;
		philos[i].finished_eating = reference_philo.finished_eating;
		philos[i].last_ate = reference_philo.last_ate;
	}
	*philos_ptr = philos;
	return (amount);
}

static int start_threads(t_philo *philos, int amount)
{
	int i;
	pthread_t th_id;
	pthread_mutex_t **forks;
	
	forks = (pthread_mutex_t**)malloc(sizeof(pthread_mutex_t*) * amount);
	if (!forks)
		return(error_exit(MALLOC_FAIL, -1));
	i = -1;
	while (++i < amount)
	{
		forks[i] = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
			return (error_exit(MALLOC_FAIL, -1));
		if (pthread_mutex_init(forks[i], NULL) != 0)
			return (error_exit(MUTEX_INIT_FAIL, -1));
	}
	i= -1;
	while (++i < amount)
	{
		philos[i].left_fork = forks[i];
		philos[i].right_fork = forks[(i + 1) % amount];
		if (pthread_create(&th_id, NULL, philosopher, (void*)&philos[i]) != 0)
			return (error_exit(THREAD_CREATE_FAIL, -1));
		pthread_detach(th_id);
	}
	return (0);
}

static void check_vitals_loop(t_philo *philos, int amount)
{
	int i;
	while (1)
	{
		i = -1;
		usleep(500);
		while (++i < amount)
		{	
			if (philos[i].finished_eating)
				return ;
			if (get_time() - philos[i].last_ate > philos[i].death_time)
				return print_status(philos[i], PHILO_DIED_MESSAGE);
		}
	}
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
	check_vitals_loop(philos, amount);
	return (0);
}