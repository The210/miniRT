/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 20:40:57 by dhorvill          #+#    #+#             */
/*   Updated: 2020/06/15 21:51:46 by ede-thom         ###   ########.fr       */
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

t_fcolor	int_to_fcolor(int color_int)
{
	t_color		rgb;
	t_fcolor	f_rgb;

	rgb = int_to_rgb(color_int);

	f_rgb.red = (float)rgb.red / 255.0;
	f_rgb.green = (float)rgb.green / 255.0;
	f_rgb.blue = (float)rgb.blue / 255.0;

	return (f_rgb);
}

int		rgb_to_int(t_color color)
{
	color.red = color.red << 16;
	color.green = color.green << 8;

	return (color.red + color.green + color.blue);
}

int		fcolor_to_int(t_fcolor color)
{
	t_color rgb;

	rgb.red = color.red * 255.0;
	rgb.green = color.green * 255.0;
	rgb.blue = color.blue * 255.0;
	return (rgb_to_int(rgb));
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

int		weighted_average(t_color base, t_color reflected, float weight1, t_color refracted, float weight2) 
{
	t_color	result;

	result.red = (int)(reflected.red * weight1) 
				+ (int)(refracted.red * weight2) 
				+ (int)(base.red * (1 - weight1 - weight2));
	result.green = (int)(reflected.green * weight1) 
				+ (int)(refracted.green * weight2) 
				+ (int)(base.green * (1 - weight1 - weight2));
	result.blue = (int)(reflected.blue * weight1) 
				+ (int)(refracted.blue * weight2) 
				+ (int)(base.blue * (1 - weight1 - weight2));
	return (rgb_to_int(result));
}
