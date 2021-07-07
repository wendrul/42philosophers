/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:41:33 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/29 12:35:25 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

int error_exit(char *msg, int exit_code)
{
    ft_putstr_fd("Error: ", STDERR_FILENO);
    ft_putendl_fd(msg, STDERR_FILENO);
    exit(exit_code);
    return (-69);
}
