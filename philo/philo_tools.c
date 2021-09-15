/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:32:22 by ede-thom          #+#    #+#             */
/*   Updated: 2021/09/08 16:07:47 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_error.h"

void	print_status(t_philo philo, char *msg, int death)
{
	static int	has_died = 0;

	if (death)
		has_died = death;
	pthread_mutex_lock(philo.printer);
	if (death || !has_died)
		printf("%-7ld %-2d %s\n",
			get_time() - philo.born_time, philo.id, msg);
	pthread_mutex_unlock(philo.printer);
}

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
	t_philo	ref;

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
		return (-1);
	philos = (t_philo *)malloc(sizeof(t_philo) * (amount + 1));
	if (!philos)
		return (error_exit(MALLOC_FAIL, -1));
	i = -1;
	while (++i < amount)
		copy_philo(&(philos[i]), ref, i);
	*philos_ptr = philos;
	return (amount);
}
