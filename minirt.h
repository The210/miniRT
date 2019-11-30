#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>

# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000
# define RENDER_DISTANCE 100000
# define FOV_H M_PI / 2
# define FOV_W M_PI / 2


typedef struct	s_point
{
	float		x;
	float		y;
	float		z;
}				t_point;

typedef t_point t_vect;



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

typedef struct	s_figure
{
	float		radius;
	float		x;
	float		y;
	float		z;
	t_point		center;
	t_box		box;
}				t_figure;

typedef t_figure	t_sphere;

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

typedef struct	s_polynome
{
	float		a;
	float		b;
	float		c;
	float		delta;
	float		sqrt_delta;
}				t_polynome;

t_window	g_win;

void		init_win(void);
t_sphere	create_sphere(float x, float y, float z, float radius);
t_point		sphere_intersection(t_sphere sphere, t_vect ray);
float		norm(t_point vector);
float		normsqrd(t_point vector);
t_point		normalize(t_point vector);
t_vect		square(t_vect v1);
t_point		vector(t_point v1, t_point v2);
t_vect		substract(t_vect v1, t_vect v2);
t_vect		add(t_vect v1, t_vect v2);
float		dot(t_point v1, t_point v2);
float		distance(t_point p1, t_point p2);
void		render_frame(t_vect **ray_table, t_figure *figures);
t_vect		**init_tracer();

#endif
