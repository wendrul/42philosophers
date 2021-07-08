#include "philo.h"

time_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (time_t)1000) + (tv.tv_usec / 1000));
}

int	ft_strlen(char const *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char const *str)
{
	int	i;
	int	start;
	int	is_neg;
	int	res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	is_neg = (str[i] == '-') ? -1 : 1;
	if (is_neg == -1 || str[i] == '+')
		i++;
	start = i;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res * is_neg);
}

void ft_putstr_fd(char *str, int fd)
{
	int i;
	i = -1;
	while (str[i])
		i++;
	write(fd, str, i);
}