/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2020/06/13 19:55:00 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	create_plane(float x, float y, float z, float normal_x, float normal_y, float normal_z, int color, float is_reflective)
{
	t_plane	plane;

	plane.x = x;
	plane.y = y;
	plane.z = z;
	plane.center.x = x;
	plane.center.y = y;
	plane.center.z = z;
    plane.normal.x = normal_x;
	plane.normal.y = normal_y;
	plane.normal.z = normal_z;
    plane.normal = normalize(plane.normal);
	plane.color = color;
	plane.is_reflective = is_reflective;
	return (plane);
}

t_point		plane_intersection(t_plane plane, t_vect ray, t_point start)
{
	t_vect		result;
    double      r1;

	result.x = RENDER_DISTANCE;
	result.y = RENDER_DISTANCE;
	result.z = RENDER_DISTANCE;
	if (dot(plane.normal, ray) == 0)
        return (result);
    r1 = (- dot(plane.center, plane.normal) - dot(plane.normal, start)) / dot(plane.normal, ray);
    if (r1 >= 0)
        return (result);
    result.x = r1 * ray.x + start.x;
    result.y = r1 * ray.y + start.y;
    result.z = r1 * ray.z + start.z;
    return (result);
    

t_vect      get_plane_normal_vector(t_vect inter, t_figure plane)
{
    return (plane.normal);
}
