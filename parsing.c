/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:03:36 by ede-thom          #+#    #+#             */
/*   Updated: 2019/12/08 02:28:40 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char        **read_lines(int fd)
{
    char    buf[4096];
    char    *lines;
    char    *aux;
    char    **tab_lines;
    int     bytes;

    if ((lines = ft_strdup("")) == NULL)
        return (NULL);
    while (bytes = read(fd, buf, 4096))
    {
        buf[bytes] = 0;
        aux = lines;
        if (!(lines = ft_strjoin(lines, buf)))
        {
            free(aux);
            return (NULL);

        }
        free(aux);
    }
    tab_lines = ft_split(lines, '\n');
    free(lines);
    return (tab_lines);
    
}

static int    is_drawable(char *line, t_drawable *drawables)
{
    if(!(line = ft_split_charset(line, "\f\t\n\r\v ")))
        clean_exit(1, "Malloc failed");
    while(drawables)
    {
        if (ft_strncmp(drawables->name, line[0], ft_strlen(line[0])) == 0)
        {
            while (*line)
                free(line++);
            free(line);
            return (1);
        }
        drawables = drawables->next;
    }
    while (*line)
            free(line++);
    free(line);
    return (0);
}

static t_scene     count_figures(char **lines, t_drawable *drawables)
{
    t_scene scene;

    scene.spotlight.x = 0;
    scene.spotlight.y = 0;
    scene.spotlight.z = 0;
    scene.figure_count = 0;
    scene.figure_list = NULL;
    while(*lines)
    {
        if (is_drawable(*lines, drawables))
            scene.figure_count++;
        lines++;
    }
    return (scene);
}

static void    create_figure(t_figure **figures, char *line, t_drawable *drawables, t_point *light)
{
    t_figure figure;
    
    if(!(line = ft_split_charset(line, "\f\t\n\r\v ")))
        clean_exit(1, "Failed to create figure (malloc wtf)");
    while(drawables)
    {
        if (ft_strncmp(drawables->name, line[0], ft_strlen(line[0])) == 0)
        {
            figure = (drawables->create)(ft_atof(line[1]),
                                         ft_atof(line[2]),
                                         ft_atof(line[3]),
                                         ft_atof(line[4]),
                                         ft_atoi(line[5]));
            **figures = figure;
            (*figures)++;
        }
        if (ft_strncmp("Spotlight", line[0], ft_strlen(line[0])) == 0)
        {
            light->x = ft_atof(line[1]);
            light->y = ft_atof(line[2]);
            light->z = ft_atof(line[3]);
        }
        drawables = drawables->next;
    }
    while (*line)
            free(line++);
    free(line);
}

static void build_scene(t_scene *scene, char **lines, t_drawable *drawables)
{
    int i;
    t_scene s;

    s = *scene;
    if (!(s.figure_list = (t_figure*)malloc(sizeof(t_figure) * s.figure_count)))
        clean_exit(1, "Failed to build scene (malloc wtf)");
    i = 1;
    while (*lines)
    {
        if ((*lines)[0] != '#')
            create_figure(&s.figure_list, *lines, &s.spotlight, drawables);
        free(lines++);
    }
}

t_scene     parse_scene(char *scene_path, t_drawable *drawables)
{
    int     fd;
    char    **lines;
    t_scene scene;

    if((fd = open(scene_path, O_RDONLY) == -1))
        clean_exit(1, "Failed to open file");
    lines = read_lines(fd);
    scene = count_figures(lines, drawables);
    build_scene(&scene, lines, drawables);
    free(lines);
    return (scene);
}