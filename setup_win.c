/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 17:32:26 by dhorvill          #+#    #+#             */
/*   Updated: 2019/11/16 17:38:06 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_win(void)
{
	g_win.mlx = mlx_init();
	g_win.win = mlx_new_window(g_win.mlx, 1000, 1000, "miniRT");
	g_win.img = mlx_new_image(g_win.mlx, 1000, 1000);
	g_win.buffer = (int*)mlx_get_data_addr(g_win.img, &g_win.bpp, &g_win.s_l, &g_win.endian);
}
