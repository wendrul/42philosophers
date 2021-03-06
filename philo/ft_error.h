/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:53:14 by wendrul           #+#    #+#             */
/*   Updated: 2021/09/07 13:34:35 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include <unistd.h>
# include <stdlib.h>

# define DEFAULT_ERROR 0
# define FATAL_ERROR 1

# define ITOA_MALLOC_FAIL "malloc failed on ft_itoa"
# define MALLOC_FAIL "malloc failed"
# define WRONG_NUMBER_OF_ARGS "Wrong number of arguments"
# define INVALID_AMOUNT_OF_PHILOS "Invalid number of philosophers"
# define INVALID_TIME_SPEC "Invalid time specification"
# define PARSING_ERROR "parsing failed"
# define THREAD_CREATE_FAIL "creating thread failed"
# define MUTEX_INIT_FAIL "failed to init mutex"
# define INVALID_AMOUNT_TO_EAT "Invalid amount of times to eat"

int	error_exit(char *msg, int exit_code);

#endif