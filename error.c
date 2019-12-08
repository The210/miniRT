/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:29:35 by ede-thom          #+#    #+#             */
/*   Updated: 2019/12/08 01:46:14 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    clean_exit(int status, char *str)
{
    ft_putstr_fd("Error\nExiting program...\nstatus = ", 1);
    ft_putnbr_fd(status, 1);
    ft_putstr_fd(": ", 1); 
    if  (str)
        ft_putstr_fd(str, 1);
    else
        ft_putstr_fd("(null)", 1);
    ft_putchar_fd('\n', 1);
    exit(status);
}