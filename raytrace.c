/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 19:15:30 by dhorvill          #+#    #+#             */
/*   Updated: 2019/12/07 23:27:46 by dhorvill         ###   ########.fr       */
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
	if (figure.is_reflective > 0)
	{
		reflective_rgb = int_to_rgb(reflective_color);
		return (weighted_average(base, reflective_rgb, figure.is_reflective));
	}
	return (rgb_to_int(base));
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

int		trace_ray(t_vect ray, t_figure *figures, t_point start, int	ignored_index)
{
	int		i;
	int		index;
	float	lum_intensity;
	float	closest_distance;
	float	distance;
	int		reflective_color;
	t_point	intersection;
	t_point	closest_intersection;
	t_point spotlight;

	spotlight.x = 0;
	spotlight.y = 0;
	spotlight.z = 0;
	closest_distance = RENDER_DISTANCE;
	i = -1;
	while (++i < 5)
	{
		if (i == ignored_index)
			continue;
		intersection = sphere_intersection(figures[i], ray, start);
		if ((distance = norm(intersection)) < closest_distance)
		{
			index = i;
			closest_distance = distance;
			closest_intersection = intersection;
		}
	}
	if (closest_distance < RENDER_DISTANCE)
	{
		if (figures[index].is_reflective > 0)
		{
			reflective_color = trace_ray(get_reflective_vector(figures[index], closest_intersection, ray),
						figures, closest_intersection, index);
		}
		lum_intensity = lum_intensity_sphere(figures[index], closest_intersection, spotlight);
		i = -1;
		while (++i < 5)
		{
			if (i == index)
				continue;
			if (sphere_eclipses_light(closest_intersection, figures[i], spotlight))
			{
				lum_intensity = AMBIENCE_LIGHTING;
				break;
			}
		}
		return (color_shade(lum_intensity, figures[index], reflective_color));
	}
	return (0);
}

void	render_frame(t_vect **ray_table, t_figure *figures, t_point start)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			g_win.buffer[j + i * WIN_HEIGHT] = trace_ray(ray_table[i][j], figures, start, -1);
	}
	mlx_put_image_to_window(g_win.mlx, g_win.win, g_win.img, 0, 0);
}

