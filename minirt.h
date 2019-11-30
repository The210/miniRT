#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>

typedef struct	s_point
{
	float		x;
	float		y;
	float		z;
}				t_point;

typedef struct	s_box
{
	int			to_check;
	t_point		ulf;
	t_point		urf;
	t_point		ulc;
	t_point		urc;
	t_point		dlf;
	t_point		drf;
	t_point		dlc;
	t_point		drc;
}				t_box;

typedef struct	s_sphere
{
	float		radius;
	float		x;
	float		y;
	float		z;
	t_point		center;
	t_box		box;
}				t_sphere;

typedef struct	s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*buffer;
	int			bpp;
	int			endian;
	int			s_l;
}				t_window;

t_window	g_win;

void		init_win(void);
t_sphere	create_sphere(float x, float y, float z, float radius);

#endif
