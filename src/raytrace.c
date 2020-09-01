/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 19:15:30 by dhorvill          #+#    #+#             */
/*   Updated: 2020/06/16 17:12:38 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	**init_tracer()
{
	t_vect	**ray_table;
	t_point	start;
	t_point end;
	t_vect	step;
	int		i;
	int		j;

	if (!(ray_table = (t_vect**)malloc(sizeof(t_vect*) * WIN_HEIGHT)))
		exit(0);
	start.x = -sin(FOV_W);
	start.y = sin(FOV_H);	
	start.z = 1;
	end.x = sin(FOV_W);
	end.y = -sin(FOV_H);
	end.z = 1;
	step.x = ((end.x - start.x) / (float)WIN_WIDTH);
	step.y = ((end.y - start.y) / (float)WIN_HEIGHT);
	i = -1;
	while (++i < WIN_HEIGHT)
	{
		if (!(ray_table[i] = (t_vect*)malloc(sizeof(t_vect) * WIN_WIDTH)))
			exit(0);
		j = -1;
		while (++j < WIN_WIDTH)
		{
			ray_table[i][j].x = start.x + step.x * (float)j;
			ray_table[i][j].y = start.y + step.y * (float)i; //daniel doubts, Etienne owns
			ray_table[i][j].z = 1;
			ray_table[i][j] = normalize(ray_table[i][j]);
		}
	}
	return (ray_table);
}

int		color_shade(float intensity, t_figure figure, int reflective_color)
{
	t_color base;
	t_color	reflective_rgb;
	
	intensity = intensity < AMBIENCE_LIGHTING ? AMBIENCE_LIGHTING : intensity;
	base = color_intensity(figure.color, intensity);
	reflective_rgb = int_to_rgb(0);
	if (figure.is_reflective > 0)
		reflective_rgb = int_to_rgb(reflective_color);
	if (figure.is_reflective == 0)
		return (rgb_to_int(base));
	return (weighted_average(base, reflective_rgb, figure.is_reflective));

}

float	lum_intensity_sphere(t_sphere sphere, t_point ray, t_point spotlight)
{
	t_point	sphere_ray;
	t_point	ray_spot;
	float	result;

	sphere_ray = vector(sphere.center, ray);
	ray_spot = vector(ray, spotlight);
	if ((result = dot(sphere_ray, ray_spot)) > 0)
		return (result);
	return (0);
}

int		trace_ray(t_vect ray, t_scene scene, t_point start, int prev_index, int ignore, t_r_stack stack) //ignored index is to be changed (last_HIT_index)
{
	int			i;
	int			index;
	float		lum_intensity;
	float		closest_distance;
	float		distance;
	int			reflective_color;

	static int 	current_recursion_depth = 0;
	t_point		intersection;
	t_point		closest_intersection;
	t_vect		reflected_dir;
	t_vect		modified_start;

	if (++current_recursion_depth > MAX_RECURSION_DEPTH)
	{
		current_recursion_depth--;
		return (0);
	}
	closest_distance = RENDER_DISTANCE;
	i = -1;
	while (++i < scene.figure_count)
	{
		if (i == prev_index && ignore)
			continue;
		intersection = sphere_intersection(scene.figure_list[i], ray, start);
		if ((distance = norm(intersection)) < closest_distance)
		{
			index = i;
			closest_distance = distance;
			closest_intersection = intersection;
		}
	}
	if (closest_distance < RENDER_DISTANCE)
	{
		if (scene.figure_list[index].is_reflective > 0 && index != peek_index(stack))
		{
			reflected_dir = get_reflective_vector(scene.figure_list[index], closest_intersection, ray);
			modified_start = add(closest_intersection, scale(reflected_dir, EPSILON)); 
			reflective_color = trace_ray(reflected_dir, scene, modified_start, index, 0, stack);
		}
		lum_intensity = lum_intensity_sphere(scene.figure_list[index], closest_intersection, scene.spotlight);
		i = -1;
		while (++i < scene.figure_count)
		{
			if (i == index)
				continue;
			if (sphere_eclipses_light(closest_intersection, scene.figure_list[i], scene.spotlight))
			{
				lum_intensity = AMBIENCE_LIGHTING;
				break;
			}
		}
		current_recursion_depth--;
		return (color_shade(lum_intensity, scene.figure_list[index], reflective_color));
	}
	current_recursion_depth--;
	return (SKY_COLOR);
}
