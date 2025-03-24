/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:06:53 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/05 12:51:45 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char	**get_map(char *file)
{
	int		fd;
	char	**map;
	char	*temp;
	char	*map_str;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error opening scene!\n"), NULL);
	map_str = ft_strdup("");
	str = get_next_line(fd);
	while (str)
	{
		temp = ft_strjoin(map_str, str);
		free(map_str);
		free(str);
		map_str = temp;
		str = get_next_line(fd);
	}
	map = ft_split(map_str, '\n');
	free(map_str);
	close(fd);
	return (map);
}

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

void	init_elements(char **map, t_minirt *rt)
{
	int	i;

	i = 0;
	rt->sp = 0;
	rt->pl = 0;
	rt->cy = 0;
	while (map[i])
	{
		if (map[i][0] == 's')
			rt->sp++;
		else if (map[i][0] == 'p')
			rt->pl++;
		else if (map[i][0] == 'c')
			rt->cy++;
		i++;
	}
	rt->sphere = malloc(sizeof(t_sphere) * rt->sp);
	rt->plane = malloc(sizeof(t_plane) * rt->pl);
	rt->cylinder = malloc(sizeof(t_cylinder) * rt->cy);
}

void	parse_map(char **map, t_minirt *rt)
{
	int	i;
	int	sp;
	int	pl;
	int	cy;

	i = 0;
	init_elements(map, rt);
	sp = pl = cy = 0;
	while (map[i])
	{
		if (map[i][0] == 'A')
			parse_alight(map[i], rt);
		else if (map[i][0] == 'C')
			parse_camera(map[i], rt);
		else if (map[i][0] == 'L')
			parse_light(map[i], rt);
		else if (map[i][0] == 's')
			parse_sphere(map[i], rt, sp++);
		else if (map[i][0] == 'p')
			parse_plane(map[i], rt, pl++);
		else if (map[i][0] == 'c')
			parse_cylinder(map[i], rt, cy++);
		i++;
	}
}
