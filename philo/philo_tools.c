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

void	print_status(t_philo philo, char *msg, int death)
{
	static int has_died = 0;
		if (death)
			has_died = death;
		pthread_mutex_lock(philo.printer);
		if (death || !has_died)
			printf("%-7ld %-2d %s\n",
				get_time() - philo.born_time, philo.id, msg);
		pthread_mutex_unlock(philo.printer);
}
