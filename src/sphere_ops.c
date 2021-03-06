/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2020/06/13 19:55:00 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_box		sphere_bounding_box(t_sphere sphere)
{
	t_point p;
	t_box box;

	p.x = sphere.x - sphere.radius;
	p.y = sphere.y + sphere.radius;
	p.z = sphere.z + sphere.radius;
	box.ulf = p;
	p.x = sphere.x + sphere.radius;
	box.urf = p;
	p.y = sphere.y - sphere.radius;
	box.drf = p;
	p.x = sphere.x - sphere.radius;
	box.dlf = p;
	p.z = sphere.z - sphere.radius;
	box.dlc = p;
	p.x = sphere.x + sphere.radius;
	box.drc = p;
	p.y = sphere.y + sphere.radius;
	box.urc = p;
	p.x = sphere.x - sphere.radius;
	box.ulc = p;
	return (box);
}

t_sphere	create_sphere(float x, float y, float z, float radius, int color, float is_reflective)
{
	t_sphere	sphere;

	sphere.x = x;
	sphere.y = y;
	sphere.z = z;
	sphere.center.x = x;
	sphere.center.y = y;
	sphere.center.z = z;
	sphere.radius = radius;
	sphere.color = color;
	sphere.is_reflective = is_reflective;
	return (sphere);
}

t_point		sphere_intersection(t_sphere sphere, t_vect ray, t_point start)
{
	t_polynome	equa;
	t_vect		result;
	t_vect		subbed;
	float		t;

	subbed = substract(sphere.center, start);
	equa.a = 1;
	equa.b = 2 * dot(ray, subbed);
	equa.c = subbed.x * subbed.x + subbed.y * subbed.y 
		+ subbed.z * subbed.z - sphere.radius * sphere.radius;
	//printf("x:%f     y:%f     z:%f \n", sphere.center.x, sphere.center.y, sphere.center.z);

	if ((equa.delta = equa.b * equa.b - 4 * equa.a * equa.c) > 0)
	{
		equa.sqrt_delta = sqrt(equa.delta);
		t = ((-equa.b + equa.sqrt_delta) / (2 * equa.a)) * -1;
		if (t > 0)
		{
			result.x = start.x + t * ray.x;
			result.y = start.y + t * ray.y;
			result.z = start.z + t * ray.z;
			return (result);
		}
		t = ((-equa.b - equa.sqrt_delta) / (2 * equa.a)) * -1;
		if (t > 0)
		{
			result.x = start.x + t * ray.x;
			result.y = start.y + t * ray.y;
			result.z = start.z + t * ray.z;
			return (result);
		}
	}
	result.x = RENDER_DISTANCE;
	result.y = RENDER_DISTANCE;
	result.z = RENDER_DISTANCE;
	return (result);
}

t_vect  get_sphere_normal_vector(t_vect inter, t_figure sphere)
{
    t_vect normal;

    normal = scale(true_vect(sphere.center, inter), 1.0 / sphere.radius);
    return (normal);
}
