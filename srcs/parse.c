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
	{
		printf("fd: %d\n", fd);
		return (printf("Error opening scene!\n"), NULL);
	}
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
	int	qtd[3];

	i = 0;
	init_elements(map, rt);
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
		i++;
	}
}
