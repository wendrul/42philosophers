#include "philo.h"

time_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (time_t)1000) + (tv.tv_usec / 1000));
}

static int	base_is_valid(const char *base)
{
	int	i;
	int	j;

	if (ft_strlen(base) < 2)
		return (0);
	i = 0;
	while (base[i + 1])
	{
		j = 1;
		while (base[i + j])
		{
			if (base[i + j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_atoi_base(const char *nptr, const char *base)
{
	int				sgn;
	unsigned int	nb;

	if (!base_is_valid(base))
		return (0);
	sgn = 1;
	while (ft_iswhitespace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sgn = -1;
		nptr++;
	}
	nb = 0;
	while (ft_indexof(*nptr, base) != -1)
	{
		nb = nb * ft_strlen(base) + ft_indexof(*nptr, base);
		nptr++;
	}
	return (sgn * nb);
}

int ft_atoi(char *str)
{
	return (ft_atoi_base(str, "0123456789"));
}