/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:03:36 by ede-thom          #+#    #+#             */
/*   Updated: 2019/12/01 23:01:00 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"

char	*ft_strjoin_charset(const char *s1, const char *s2, const char *sep)
{
	char *ret;
	char *start;

	if (s1 == NULL || s2 == NULL)
		return ((char*)NULL);
	if (!(ret = (char*)malloc((ft_strlen(s1)
		+ ft_strlen(s2) + ft_strlen(sep) + 1) * sizeof(*ret))))
		return (NULL);
	start = ret;
	while (*s1)
		*ret++ = *s1++;
    while (*sep)
        *ret++ = *sep++;
	while (*s2)
		*ret++ = *s2++;
	*ret = '\0';
	return (start);
}

char        **read_lines(int fd)
{
    char    **lines;
    char    *buf;
    char    *line;
    char    *aux;
    int     ret;

    while (ret)
    {
        if ((ret = get_next_line(fd, &line)) == -1)
            clean_exit(1, "Failed when reading file");
        if (line[0] && line[0] != '#')
        {
            if (!(aux = ft_strjoin_charset(line, buf, "\n")))
            {
                free(buf);
                free(line);
                return (NULL);
            }       
            free(line);
            line = aux;
        }
        free(buf);
    }
    if(!(lines = ft_split(line, '\n')))
        return (NULL);
    free(line);
    return (lines);
}

t_scene     count_figures(char **lines)
{
    t_scene scene;

    scene.figure_count = 0;
    while(*lines)
    {
        
    }
}

t_scene     parse_scene(char *scene_path)
{
    int     fd;
    char    **lines;
    t_scene scene;

    if((fd = open(scene_path, O_RDONLY) == -1))
        clean_exit(1, "Failed to open file");
    lines = read_lines(fd);
    
}