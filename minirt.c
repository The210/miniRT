/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 22:07:25 by dhorvill          #+#    #+#             */
/*   Updated: 2019/12/01 19:39:39 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

int	interact(int keycode, void *thing)
{
	thing = 0;
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 53)
		exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_vect		**ray_table;
	t_figure	figures[2];

	if (!argc && argv[0])
		return (0);
	ray_table = init_tracer();
	init_win();
	figures[0] = create_sphere(-50, 0, 100, 50, 0x00aaaa);
	figures[1] = create_sphere(0, 0, 100, 50, 0x00ffff);
	clock_t begin = clock();

	render_frame(ray_table, figures);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time Elapsed: %lf\n", time_spent);
	mlx_key_hook(g_win.win, interact, NULL);
	mlx_loop(g_win.mlx);
	return (0);
}
