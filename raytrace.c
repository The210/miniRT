/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 19:15:30 by dhorvill          #+#    #+#             */
/*   Updated: 2019/12/01 17:21:16 by dhorvill         ###   ########.fr       */
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
			ray_table[i][j].y = start.y + step.y * (float)i; //daniel doubts
			ray_table[i][j].z = 1;
			ray_table[i][j] = normalize(ray_table[i][j]);
		}
	}
	return (ray_table);
}

int	lum_intensity_sphere(t_sphere sphere, t_point ray, t_point spotlight)
{
	t_point	sphere_ray;
	t_point	ray_spot;
	float	result;

	sphere_ray = vector(sphere.center, ray);
	ray_spot = vector(ray, spotlight);
	if ((result = dot(sphere_ray, ray_spot)) > 0)
		return (round(255 * result) * pow(16, 4));
	else
		return (0);
}

int		trace_ray(t_vect ray, t_figure *figures)
{
	int		i;
	int		index;
	float	closest_distance;
	float	distance;
	t_point	intersection;
	t_point	closest_intersection;
	t_point spotlight;

	i = -1;
	spotlight.x = 0;
	spotlight.y = 0;
	spotlight.z = 0;
	closest_distance = RENDER_DISTANCE;
	while (++i < 2)
	{
		//if ((intersection = sphere_intersection(figures[i], ray)))
		intersection = sphere_intersection(figures[i], ray);
		if ((distance = norm(intersection)) < closest_distance)
		{
			index = i;
			closest_distance = distance;
			closest_intersection = intersection;
		}
	}
	if (closest_distance < RENDER_DISTANCE)
	{
		//printf("CI.x: %f,  CI.y: %f,  CI.z: %f\n", closest_intersection.x, closest_intersection.y, closest_intersection.z);
		return (lum_intensity_sphere(figures[index], closest_intersection, spotlight));
	}
	return (0);
}

void	render_frame(t_vect **ray_table, t_figure *figures)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			g_win.buffer[j + i * WIN_HEIGHT] = trace_ray(ray_table[i][j], figures);
	}
	mlx_put_image_to_window(g_win.mlx, g_win.win, g_win.img, 0, 0);
}

