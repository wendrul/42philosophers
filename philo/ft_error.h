/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:53:14 by wendrul           #+#    #+#             */
/*   Updated: 2021/07/08 03:23:58 by user42           ###   ########.fr       */
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
# define WRONG_NUMBER_OF_ARGS "Wrong number of arguments "
# define PARSING_ERROR "parsing failed"
# define THREAD_CREATE_FAIL "creating thread failed"

int	error_exit(char *msg, int exit_code);

#endif