/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 17:32:26 by dhorvill          #+#    #+#             */
/*   Updated: 2019/12/01 17:24:33 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_win(void)
{
	g_win.mlx = mlx_init();
	g_win.win = mlx_new_window(g_win.mlx, WIN_HEIGHT, WIN_WIDTH, "miniRT");
	g_win.img = mlx_new_image(g_win.mlx, WIN_HEIGHT, WIN_WIDTH);
	g_win.buffer = (int*)mlx_get_data_addr(g_win.img, &g_win.bpp, &g_win.s_l, &g_win.endian);
}
