/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 12:54:07 by ede-thom          #+#    #+#             */
/*   Updated: 2019/12/11 22:09:01 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float   ft_atof(char *nb)
{
    int     q;
    double  ret;
    double  exp;

    q = ft_atoi(nb);
    while (*nb && *nb != '.')
        nb++;
    nb++;
    if ((*nb > '9' || *nb < '0'))
        return (q);
    ret = 0.;
    exp = .1;
    while (*nb)
    {
        ret += (float)(*nb - '0') * exp;
        exp /= 10.;
        nb++;
    }
    if (q >= 0)
        return ((float)q + ret);
    return ((float)q - ret);
}
/*ft_atof("9aaaaaaa.11111") => 9.11111*/