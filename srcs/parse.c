/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:06:53 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/16 18:05:56 by jorcarva         ###   ########.fr       */
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
		return (printf("Error\nError opening scene!\n"), NULL);
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
	return (free(map_str), close(fd), map);
}

void	check_argv(char **s, t_minirt *rt, int i)
{
	char	**splitted;

	splitted = ft_split(s[i], ' ');
	if (s[i][0] == 's' && splitted[3])
		rt->sp++;
	else if (s[i][0] == 'p' && splitted[3])
		rt->pl++;
	else if (s[i][0] == 'c' && splitted[5])
		rt->cy++;
	else if (s[i][0] == 'C' && splitted[3])
		rt->c++;
	else if (s[i][0] == 'A' && splitted[2])
		rt->al++;
	else if (s[i][0] == 'L' && splitted[2])
		rt->l++;
	else
	{
		rt->complete = 0;
		printf("Error: bad scene format\n");
	}
	free_matrix(splitted);
}

void	count_elements(char **map, t_minirt *rt)
{
	int	i;

	i = 0;
	rt->sp = 0;
	rt->pl = 0;
	rt->cy = 0;
	rt->c = 0;
	rt->al = 0;
	rt->l = 0;
	while (map[i])
	{
		if (map[i][0] == 's')
			check_argv(map, rt, i);
		else if (map[i][0] == 'p')
			check_argv(map, rt, i);
		else if (map[i][0] == 'c')
			check_argv(map, rt, i);
		else if (map[i][0] == 'C')
			check_argv(map, rt, i);
		else if (map[i][0] == 'A')
			check_argv(map, rt, i);
		else if (map[i][0] == 'L')
			check_argv(map, rt, i);
		i++;
	}
}

void	init_elements(t_minirt *rt)
{
	rt->sphere = malloc(sizeof(t_sphere) * rt->sp);
	rt->plane = malloc(sizeof(t_plane) * rt->pl);
	rt->cylinder = malloc(sizeof(t_cylinder) * rt->cy);
}

void	parse_map(char **map, t_minirt *rt)
{
	int	i;
	int	qtd[3];

	i = 0;
	init_elements(rt);
	qtd[0] = 0;
	qtd[1] = 0;
	qtd[2] = 0;
	while (map[i])
	{
		if (map[i][0] == 'A')
			parse_alight(map[i], rt);
		else if (map[i][0] == 'C')
			parse_camera(map[i], rt);
		else if (map[i][0] == 'L')
			parse_light(map[i], rt);
		else if (map[i][0] == 's')
			parse_sphere(map[i], rt, qtd[0]++);
		else if (map[i][0] == 'p')
			parse_plane(map[i], rt, qtd[1]++);
		else if (map[i][0] == 'c')
			parse_cylinder(map[i], rt, qtd[2]++);
		if (rt->error == 0)
			return ;
		i++;
	}
}
