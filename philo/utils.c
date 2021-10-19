/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:34:44 by ede-thom          #+#    #+#             */
/*   Updated: 2021/10/18 13:16:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (time_t)1000) + (tv.tv_usec / 1000));
}

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	tern(int condition, int yes, int no)
{
	if (condition)
		return (yes);
	else
		return (no);
}

int	ft_atoi(char const *str)
{
	int	i;
	int	is_neg;
	int	res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	is_neg = tern((str[i] == '-'), -1, 1);
	if (is_neg == -1 || str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res * is_neg);
}

void	ft_usleep(useconds_t time_val, t_philo philo)
{
	time_t		start_time;
	useconds_t	to_wait;
	useconds_t	sleep_val;

	start_time = get_time();
	to_wait = (start_time * 1000 + time_val) - start_time * 1000;
	sleep_val = tern(to_wait > USLEEP_INCREMENT, USLEEP_INCREMENT, to_wait);
	while (to_wait > 0 && !is_sim_end(philo))
	{
		usleep(sleep_val);
		to_wait = (start_time * 1000 + time_val) - get_time() * 1000;
		sleep_val = tern(to_wait > USLEEP_INCREMENT, USLEEP_INCREMENT, to_wait);
	}
}
