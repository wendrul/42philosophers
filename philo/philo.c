/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:16:46 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/29 12:49:33 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"
#include "ft_error.h"

t_philo parse_args(int argc, char **argv)
{
    if (argc != 4 && argc != 5)
        error_exit(WRONG_NUMBER_OF_ARGS, DEFAULT_ERROR);
}

int main(int argc, char **argv)
{
    t_philo philo;

    philo = parse_args(argc, argv);
    return (0);
}