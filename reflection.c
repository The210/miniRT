/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 21:54:26 by dhorvill          #+#    #+#             */
/*   Updated: 2019/12/07 20:14:31 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	get_reflective_vector(t_sphere sphere, t_point inter, t_vect incident)
{
	t_vect normal;
	t_vect reflected;

	normal = scale(true_vect(sphere.center, inter), 1.0 / sphere.radius);
	reflected = scale(normal, 2.0 * dot(incident, normal));
	reflected = substract(incident, reflected);
	return (reflected);
}
