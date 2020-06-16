#include "minirt.h"

t_vect  get_refraction_vector(t_figure sphere, t_point inter, t_vect incident, float n_entry, float n_exit)
{
    t_vect  normal;
    double   i1;
    double   i2;
    double   r;
    double   g;

    //normal = figure.normal_vect(inter);
    normal = scale(true_vect(sphere.center, inter), 1.0 / sphere.radius);
    i1 = fmod(angle(normal, incident) - M_PI_2, M_PI_2);
    if (fabs(i1) < ZERO_FLOAT_PRECISION)
        return (normalize(incident));
    i2 = asin(n_entry / n_exit * sin(i1));
    r =  1 / cos(i1);
    g = 1 - tan(i1)/tan(i2);
    //if (dot(incident, normal) > 0)
    //    g = -g;
    return (normalize(new_vect( g * normal.x + r * incident.x, 
                                g * normal.y + r * incident.y, 
                                g * normal.z + r * incident.z)));
}