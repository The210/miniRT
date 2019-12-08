#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_HEIGHT 800
# define WIN_WIDTH 800
# define RENDER_DISTANCE 100000000
# define FOV_H M_PI / 2
# define FOV_W M_PI / 2
# define CREATE_ARGS float x, float y, float z, float radius, int color


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
	int			color;
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

typedef struct	s_scene
{
	t_point		spotlight;
	t_figure	*figure_list;
	int			figure_count;
}	            t_scene;

typedef struct	s_drawable
{
	char				*name;
	t_figure			(*create)(CREATE_ARGS);
	//create always has the max number of arguments, even if irrelevant
	struct s_drawable	*next;
}				t_drawable;

t_window	g_win;

void		init_win(void);
t_sphere	create_sphere(float x, float y, float z, float radius, int color);
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
void		clean_exit(int status, char *msg);
t_scene		parse_scene(char *scene_file_path, t_drawable *drawable_list);
float		ft_atof(char *nb);
void		add_drawable(t_drawable **drawables, char *name, t_figure (*create_func)(CREATE_ARGS));

#endif
