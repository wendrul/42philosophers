/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:16:46 by wendrul           #+#    #+#             */
/*   Updated: 2021/10/18 13:06:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"
#include "ft_error.h"

static int	dishwash_forks(pthread_mutex_t ***forks_ptr, int amount)
{
	int				i;
	pthread_mutex_t	**forks;

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
	*forks_ptr = forks;
	return (0);
}

static int	start_threads(t_philo *philos, int amount)
{
	int				i;
	pthread_t		th_id;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*printer;
	pthread_mutex_t *get_time_lock;

	if (dishwash_forks(&forks, amount) == -1)
		return (-1);
	printer = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	get_time_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!printer || !get_time_lock)
		return (error_exit(MALLOC_FAIL, -1));
	if (pthread_mutex_init(printer, NULL) != 0)
		return (error_exit(MUTEX_INIT_FAIL, -1));
	if (pthread_mutex_init(get_time_lock, NULL) != 0)
		return (error_exit(MUTEX_INIT_FAIL, -1));
	i = -1;
	while (++i < amount)
	{
		philos[i].left_fork = forks[i];
		philos[i].right_fork = forks[(i + 1) % amount];
		philos[i].printer = printer;
		philos[i].get_time_lock = get_time_lock;
		if (pthread_create(&th_id, NULL, philosopher, (void *)&philos[i]) != 0)
			return (error_exit(THREAD_CREATE_FAIL, -1));
		pthread_detach(th_id);
	}
	free(forks);
	return (0);
}

static void	check_vitals_loop(t_philo *philos, int amount)
{
	int	i;
	int all_finished;

	while (1)
	{
		i = -1;
		all_finished = 1;
		usleep(500);
		while (++i < amount)
		{	
			if (!philos[i].finished_eating)
				all_finished = 0;
			pthread_mutex_lock(philos[i].get_time_lock);
			if (get_time() - philos[i].last_ate > philos[i].death_time)
			{
				pthread_mutex_unlock(philos[i].get_time_lock);
				return (print_status(philos[i], PHILO_DIED_MESSAGE, 1));
			}
			pthread_mutex_unlock(philos[i].get_time_lock);

		}
		if (all_finished)
			return ;
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	int		amount;
	int		i;

	amount = parse_args(argc, argv, &philos);
	if (amount == -1)
		return (1);
	if (start_threads(philos, amount) == -1)
		return (1);
	check_vitals_loop(philos, amount);
	end_sim(philos[0]);
	i = -1;
	ft_usleep((philos[0].eat_time + philos[0].eat_time) * amount * 1000);
	while (++i < amount)
		free(philos[i].right_fork);
	free(philos[0].simulation_end);
	free(philos[0].printer);
	free(philos[0].get_time_lock);
	free(philos);
	return (0);
}
