#include "minirt.h"

t_vect  get_refraction_vector(t_figure sphere, t_point inter, t_vect incident, float n_entry, float n_exit)
{
    t_vect  normal;
    float   i1;
    float   i2;
    float   r;
    float   g;

    //normal = figure.normal_vect(inter);
    normal = scale(true_vect(sphere.center, inter), 1.0 / sphere.radius);
    i1 = fmod(angle(normal, incident), (M_PI_2)) - M_PI_2;
    i2 = asin(n_entry / n_exit * sin(i1));
    r = 1 / cos(i1);
    g = sin(i2) / sin(i1);
    return (normalize(new_vect( g * normal.x + -r * incident.x, 
                                g * normal.y + -r * incident.y, 
                                -g * normal.z + r * incident.z)));
}