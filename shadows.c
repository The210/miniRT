/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 20:03:19 by dhorvill          #+#    #+#             */
/*   Updated: 2019/12/01 21:10:24 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		sphere_eclipses_light(t_point intersection, t_sphere sphere, t_point spot)
{
	t_vect	intersection_to_spot;

	intersection_to_spot = normalize(vector(intersection, spot));
	intersection_to_spot = scale(intersection_to_spot, distance(intersection, sphere.center));
	intersection_to_spot = add(intersection, intersection_to_spot);
	return (distance(intersection_to_spot, sphere.center) < sphere.radius ? 1 : 0);
}
