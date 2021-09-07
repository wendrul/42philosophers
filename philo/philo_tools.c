/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:32:22 by ede-thom          #+#    #+#             */
/*   Updated: 2021/09/07 15:33:26 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo philo, char *msg)
{
	static time_t	start_time = 0;

	if (start_time == 0)
		start_time = get_time();
	printf("%-7ld %-2d %s\n", get_time() - start_time, philo.id, msg);
}
