/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 20:40:57 by dhorvill          #+#    #+#             */
/*   Updated: 2019/12/08 00:23:36 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	int_to_rgb(int color_int)
{
	t_color rgb;

	rgb.red = color_int >> 16;
	rgb.green = (color_int & 0xff00) >> 8;
	rgb.blue = color_int & 0xff;

	return (rgb);
}

int		rgb_to_int(t_color color)
{
	color.red = color.red << 16;
	color.green = color.green << 8;

	return (color.red + color.green + color.blue);
}

t_color	rgb_color_intensity(t_color color, float intensity)
{
	color.red *= intensity;
	color.green *= intensity;
	color.blue *= intensity;

	return (color);
}

t_color	color_intensity(int color, float intensity)
{
	t_color	rgb;

	rgb = int_to_rgb(color);
	return (rgb_color_intensity(rgb, intensity));
}

int		weighted_average(t_color base, t_color reflected_color, float weight)
{
	float	r_diff;
	float	g_diff;
	float	b_diff;
	t_color	result;

	r_diff = reflected_color.red - base.red;
	g_diff = reflected_color.green - base.green;
	b_diff = reflected_color.blue - base.blue;

	result.red = (int)(r_diff * weight) + base.red;
	result.green = (int)(g_diff * weight) + base.green;
	result.blue = (int)(b_diff * weight) + base.blue;

	return (rgb_to_int(result));
}
