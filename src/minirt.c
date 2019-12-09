/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 22:07:25 by dhorvill          #+#    #+#             */
/*   Updated: 2019/12/08 17:44:50 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

int	interact(int keycode, void *thing)
{
	thing = 0;
	ft_putnbr_fd(keycode, 1);
	ft_putchar_fd('\n', 1);
	if (keycode == 53)
		exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_vect		**ray_table;
	t_point		start;
	t_scene		scene;
	t_drawable	*drawables;

	if (argc != 2)
	{
		ft_putendl_fd("pls file", 1);
		return (0);
	}
	ray_table = init_tracer();
	init_win();
	drawables = NULL;
	add_drawable(&drawables, "Sphere", create_sphere);
	scene = parse_scene(argv[1], drawables);
	start.x = 0;
	start.y = 0;
	start.z = 0;
	/*figures[0] = create_sphere(0, 0, 10, 5, 0x852e28, 0.75);
	figures[1] = create_sphere(3, 0, -15, 8, 0x0000FF, 0.2);
	figures[2] = create_sphere(90, 0, -20, 80, 0xFFFFFF, 0.5);
	figures[3] = create_sphere(-10, 0, 0, 1, 0x00ff00, 0);
	figures[4] = create_sphere(-4, 2, 20, 10, 0x00881e, 0);*/

	clock_t begin = clock();

	render_frame(ray_table, scene, start);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time Elapsed: %lf\n", time_spent);
	mlx_key_hook(g_win.win, interact, NULL);
	mlx_loop(g_win.mlx);
	return (0);
}