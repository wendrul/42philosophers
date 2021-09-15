/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:16:46 by wendrul           #+#    #+#             */
/*   Updated: 2021/09/08 16:00:08 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"
#include "ft_error.h"

static void	copy_philo(t_philo *dest, t_philo src, int i)
{
	dest->id = i + 1;
	dest->death_time = src.death_time;
	dest->eat_time = src.eat_time;
	dest->sleep_time = src.sleep_time;
	dest->remaining_meals = src.remaining_meals;
	dest->finished_eating = src.finished_eating;
	dest->last_ate = src.last_ate;
	dest->born_time = src.born_time;
}

int	get_ref(int argc, char **argv, t_philo *ref_philo)
{
	t_philo ref;

	ref.death_time = ft_atoi(argv[2]);
	ref.eat_time = ft_atoi(argv[3]);
	ref.sleep_time = ft_atoi(argv[4]);
	if (ref.death_time <= 0 || ref.eat_time <= 0 || ref.sleep_time <= 0)
		return (error_exit(INVALID_TIME_SPEC, -1));
	ref.remaining_meals = -1;
	ref.finished_eating = 0;
	ref.last_ate = get_time();
	ref.born_time = ref.last_ate;
	if (argc == 6)
	{
		ref.remaining_meals = ft_atoi(argv[5]);
		if (ref.remaining_meals < 0)
			ref.remaining_meals = 0;
	}
	*ref_philo = ref;
	return (0);
}

int	parse_args(int argc, char **argv, t_philo **philos_ptr)
{
	t_philo	ref;
	t_philo	*philos;
	int		amount;
	int		i;

	if (argc != 5 && argc != 6)
		return (error_exit(WRONG_NUMBER_OF_ARGS, -1));
	amount = ft_atoi(argv[1]);
	if (amount <= 0)
		return (error_exit(INVALID_AMOUNT_OF_PHILOS, -1));
	if (get_ref(argc, argv, &ref) == -1)
		return(-1);
	philos = (t_philo *)malloc(sizeof(t_philo) * (amount + 1));
	if (!philos)
		return (error_exit(MALLOC_FAIL, -1));
	i = -1;
	while (++i < amount)
		copy_philo(&(philos[i]), ref, i);
	*philos_ptr = philos;
	return (amount);
}

static int	start_threads(t_philo *philos, int amount)
{
	int				i;
	pthread_t		th_id;
	pthread_mutex_t	**forks;
	pthread_mutex_t *printer;

	forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * amount);
	if (!forks)
		return (error_exit(MALLOC_FAIL, -1));
	i = -1;
	while (++i < amount)
	{
		forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
			return (error_exit(MALLOC_FAIL, -1));
		if (pthread_mutex_init(forks[i], NULL) != 0)
			return (error_exit(MUTEX_INIT_FAIL, -1));
	}
	printer = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!printer)
		return (error_exit(MALLOC_FAIL, -1));
	if (pthread_mutex_init(printer, NULL) != 0)
			return (error_exit(MUTEX_INIT_FAIL, -1));
	i = -1;
	while (++i < amount)
	{
		philos[i].left_fork = forks[i];
		philos[i].right_fork = forks[(i + 1) % amount];
		philos[i].printer = printer;
		if (pthread_create(&th_id, NULL, philosopher, (void *)&philos[i]) != 0)
			return (error_exit(THREAD_CREATE_FAIL, -1));
		pthread_detach(th_id);
	}
	return (0);
}

static void	check_vitals_loop(t_philo *philos, int amount)
{
	int	i;

	while (1)
	{
		i = -1;
		usleep(500);
		while (++i < amount)
		{	
			if (philos[i].finished_eating)
				return ;
			if (get_time() - philos[i].last_ate > philos[i].death_time)
				return (print_status(philos[i], PHILO_DIED_MESSAGE, 1));
		}
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	int		amount;

	amount = parse_args(argc, argv, &philos);
	if (amount == -1)
		return (1);
	if (start_threads(philos, amount) == -1)
		return (1);
	check_vitals_loop(philos, amount);
	return (0);
}
