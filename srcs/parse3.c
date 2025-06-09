/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:07:14 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/09 18:07:17 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	parse_sphere(char *line, t_minirt *rt, int index)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	rt->sphere[index].coordinates = parse_point(splitted_line[1]);
	rt->sphere[index].diameter = ft_atod(splitted_line[2], 1, 0, 0);
	rt->sphere[index].radius = rt->sphere[index].diameter / 2;
	rt->sphere[index].color = parse_color(splitted_line[3]);
	free_matrix(splitted_line);
}

void	parse_plane(char *line, t_minirt *rt, int index)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	rt->plane[index].coordinates = parse_point(splitted_line[1]);
	rt->plane[index].n_vector = parse_point(splitted_line[2]);
	rt->plane[index].color = parse_color(splitted_line[3]);
	free_matrix(splitted_line);
}

void	parse_cylinder(char *line, t_minirt *rt, int index)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	rt->cylinder[index].coordinates = parse_point(splitted_line[1]);
	rt->cylinder[index].a_vector = parse_point(splitted_line[2]);
	rt->cylinder[index].diameter = ft_atod(splitted_line[3], 1, 0, 0);
	rt->cylinder[index].radius = rt->cylinder[index].diameter / 2;
	rt->cylinder[index].height = ft_atod(splitted_line[4], 1, 0, 0);
	rt->cylinder[index].color = parse_color(splitted_line[5]);
	free_matrix(splitted_line);
}
