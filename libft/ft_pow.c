/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 00:29:44 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/11 00:57:42 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long int	ft_pow(int nb, int pow)
{
	if (pow < 0)
		return (0);
	if (pow == 0)
		return (1);
	if (pow % 2 == 0)
		return (ft_pow(nb * nb, pow / 2));
	else
		return (nb * ft_pow(nb, pow - 1));
}
