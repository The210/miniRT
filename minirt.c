/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 22:07:25 by dhorvill          #+#    #+#             */
/*   Updated: 2019/11/30 22:06:56 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	t_figure	figures[1];

	if (!argc && argv[0])
		return (0);
	init_win();
	ray_table = init_tracer();
	render_frame(ray_table, figures);
	figures[0] = create_sphere(0, 0, 10, 5);
	mlx_key_hook(g_win.win, interact, NULL);
	mlx_loop(g_win.mlx);
	return (0);
}
