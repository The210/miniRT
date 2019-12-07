/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 20:03:19 by dhorvill          #+#    #+#             */
/*   Updated: 2019/12/07 19:46:20 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		sphere_eclipses_light(t_point intersection, t_sphere sphere, t_point spot)
{
	t_vect	intersection_to_spot;

	if (sphere.is_reflective)
		return (0);
	intersection_to_spot = normalize(vector(intersection, spot));
	intersection_to_spot = scale(intersection_to_spot, distance(intersection, sphere.center));
	intersection_to_spot = add(intersection, intersection_to_spot);
	if (distance(intersection_to_spot, sphere.center) < sphere.radius)
	{
		if (distance(intersection, spot) > distance(intersection, sphere.center))
			return (1);
	}
	return (0);
}
