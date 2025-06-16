/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:06:09 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/16 17:13:58 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	parse_color(char *color)
{
	t_color	colorini;
	char	**colors;

	colors = ft_split(color, ',');
	colorini.r = ft_atoi(colors[0]);
	colorini.g = ft_atoi(colors[1]);
	colorini.b = ft_atoi(colors[2]);
	free_matrix(colors);
	return (colorini);
}

t_point	parse_point(char *point)
{
	t_point	pointini;
	char	**points;

	points = ft_split(point, ',');
	pointini.x = ft_atod(points[0], 1, 0, 0);
	pointini.y = ft_atod(points[1], 1, 0, 0);
	pointini.z = ft_atod(points[2], 1, 0, 0);
	free_matrix(points);
	return (pointini);
}

void	parse_alight(char *line, t_minirt *rt)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	rt->alight.ratio = ft_atod(splitted_line[1], 1, 0, 0);
	rt->alight.color = parse_color(splitted_line[2]);
	free_matrix(splitted_line);
}

void	parse_camera(char *line, t_minirt *rt)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	rt->camera.coordinates = parse_point(splitted_line[1]);
	rt->camera.o_vector = parse_point(splitted_line[2]);
	rt->camera.fov = ft_atoi(splitted_line[3]);
	free_matrix(splitted_line);
}

void	parse_light(char *line, t_minirt *rt)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	rt->light.coordinates = parse_point(splitted_line[1]);
	rt->light.ratio = ft_atod(splitted_line[2], 1, 0, 0);
	if (splitted_line[3])
		rt->light.color = parse_color(splitted_line[3]);
	else
	{
		rt->light.color.r = 255;
		rt->light.color.g = 255;
		rt->light.color.b = 255;
	}
	free_matrix(splitted_line);
}
