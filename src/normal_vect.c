#include "minirt.h"

t_vect  get_sphere_normal_vector(t_vect inter, t_figure sphere)
{
    t_vect normal;

    normal = scale(true_vect(sphere.center, inter), 1.0 / sphere.radius);
    return (normal);
}