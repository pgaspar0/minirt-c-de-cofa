/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:07:14 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/27 20:22:54 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	parse_sphere(char *line, t_minirt *rt, int index)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	if (!splitted_line || !splitted_line[0] || !splitted_line[1]
		|| !splitted_line[2] || !splitted_line[3]
		|| (int)ft_matlen(splitted_line) != 4 || ft_strcmp(splitted_line[0],
			"sp"))
	{
		free_matrix(splitted_line);
		rt->error = 0;
		return ;
	}
	rt->sphere[index].coordinates = parse_point(splitted_line[1], rt);
	rt->sphere[index].diameter = ft_atod(splitted_line[2], (t_fdi){1, 0, 0},
			&rt->error);
	rt->sphere[index].radius = rt->sphere[index].diameter / 2;
	rt->sphere[index].color = parse_color(splitted_line[3], rt);
	free_matrix(splitted_line);
}

void	parse_plane(char *line, t_minirt *rt, int index)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	if (!splitted_line || !splitted_line[0] || !splitted_line[1]
		|| !splitted_line[2] || !splitted_line[3]
		|| (int)ft_matlen(splitted_line) != 4 || ft_strcmp(splitted_line[0],
			"pl"))
	{
		free_matrix(splitted_line);
		rt->error = 0;
		return ;
	}
	rt->plane[index].coordinates = parse_point(splitted_line[1], rt);
	rt->plane[index].n_vector = parse_point(splitted_line[2], rt);
	rt->plane[index].color = parse_color(splitted_line[3], rt);
	free_matrix(splitted_line);
}

void	parse_cylinder(char *line, t_minirt *rt, int index)
{
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	if (!splitted_line || !splitted_line[0] || !splitted_line[1]
		|| !splitted_line[2] || !splitted_line[3] || !splitted_line[4]
		|| !splitted_line[5] || (int)ft_matlen(splitted_line) != 6
		|| ft_strcmp(splitted_line[0], "cy"))
	{
		free_matrix(splitted_line);
		rt->error = 0;
		return ;
	}
	rt->cylinder[index].coordinates = parse_point(splitted_line[1], rt);
	rt->cylinder[index].a_vector = parse_point(splitted_line[2], rt);
	rt->cylinder[index].diameter = ft_atod(splitted_line[3], (t_fdi){1, 0, 0},
			&rt->error);
	rt->cylinder[index].radius = rt->cylinder[index].diameter / 2;
	rt->cylinder[index].height = ft_atod(splitted_line[4], (t_fdi){1, 0, 0},
			&rt->error);
	rt->cylinder[index].color = parse_color(splitted_line[5], rt);
	free_matrix(splitted_line);
}

void	parse_map2(char **map, t_minirt *rt, int i, int qtd[3])
{
	if (map[i][0] == 's')
		parse_sphere(map[i], rt, qtd[0]++);
	else if (map[i][0] == 'p')
		parse_plane(map[i], rt, qtd[1]++);
	else if (map[i][0] == 'c')
		parse_cylinder(map[i], rt, qtd[2]++);
	return ;
}
