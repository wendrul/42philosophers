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

	if (dishwash_forks(&forks, amount) == -1)
		return (-1);
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
