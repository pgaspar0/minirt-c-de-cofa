/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:06:09 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/27 20:20:47 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	parse_color(char *color, t_minirt *rt)
{
	t_color	colorini;
	char	**colors;

	colors = ft_split(color, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2]
		|| (int)ft_matlen(colors) != 3)
	{
		free_matrix(colors);
		rt->error = 0;
		return ((t_color){0, 0, 0});
	}
	colorini.r = ft_atoi(colors[0], &rt->error);
	colorini.g = ft_atoi(colors[1], &rt->error);
	colorini.b = ft_atoi(colors[2], &rt->error);
	free_matrix(colors);
	return (colorini);
}

t_point	parse_point(char *point, t_minirt *rt)
{
	t_point	pointini;
	char	**points;

	points = ft_split(point, ',');
	if (!points || !points[0] || !points[1] || !points[2]
		|| (int)ft_matlen(points) != 3)
	{
		free_matrix(points);
		rt->error = 0;
		return ((t_point){0, 0, 0});
	}
	pointini.x = ft_atod(points[0], (t_fdi){1, 0, 0}, &rt->error);
	pointini.y = ft_atod(points[1], (t_fdi){1, 0, 0}, &rt->error);
	pointini.z = ft_atod(points[2], (t_fdi){1, 0, 0}, &rt->error);
	free_matrix(points);
	return (pointini);
}

void	parse_alight(char *line, t_minirt *rt)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	if (!splitted_line || !splitted_line[0] || !splitted_line[1]
		|| !splitted_line[2] || (int)ft_matlen(splitted_line) != 3
		|| ft_strcmp(splitted_line[0], "A"))
	{
		free_matrix(splitted_line);
		rt->error = 0;
		return ;
	}
	rt->alight.ratio = ft_atod(splitted_line[1], (t_fdi){1, 0, 0}, &rt->error);
	rt->alight.color = parse_color(splitted_line[2], rt);
	free_matrix(splitted_line);
}

void	parse_camera(char *line, t_minirt *rt)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	if (!splitted_line || !splitted_line[0] || !splitted_line[1]
		|| !splitted_line[2] || !splitted_line[3]
		|| (int)ft_matlen(splitted_line) != 4 || ft_strcmp(splitted_line[0],
			"C"))
	{
		free_matrix(splitted_line);
		rt->error = 0;
		return ;
	}
	rt->camera.coordinates = parse_point(splitted_line[1], rt);
	rt->camera.o_vector = parse_point(splitted_line[2], rt);
	rt->camera.fov = ft_atoi(splitted_line[3], &rt->error);
	free_matrix(splitted_line);
}

void	parse_light(char *line, t_minirt *rt)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	if (!splitted_line || !splitted_line[0] || !splitted_line[1]
		|| !splitted_line[2] || (int)ft_matlen(splitted_line) != 4
		|| ft_strcmp(splitted_line[0], "L"))
	{
		free_matrix(splitted_line);
		rt->error = 0;
		return ;
	}
	rt->light.coordinates = parse_point(splitted_line[1], rt);
	rt->light.ratio = ft_atod(splitted_line[2], (t_fdi){1, 0, 0}, &rt->error);
	if (splitted_line[3])
		rt->light.color = parse_color(splitted_line[3], rt);
	else
	{
		rt->light.color.r = 255;
		rt->light.color.g = 255;
		rt->light.color.b = 255;
	}
	free_matrix(splitted_line);
}
