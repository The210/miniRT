/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2019/11/24 19:14:34 by dhorvill         ###   ########.fr       */
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

t_sphere	create_sphere(float x, float y, float z, float radius)
{
	t_sphere	sphere;

	sphere.x = x;
	sphere.y = y;
	sphere.z = z;
	sphere.center.x = x;
	sphere.center.y = y;
	sphere.center.z = z;
	sphere.radius = radius;
	//sphere.box = sphere_bounding_box(sphere);
	//sphere.box.to_check = 1;
	return (sphere);
}
