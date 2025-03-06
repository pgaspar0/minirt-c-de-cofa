/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:41:36 by pgaspar           #+#    #+#             */
/*   Updated: 2025/02/28 17:41:41 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* static int	file_lines(char *arg)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	fd = open(arg, O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	free(str);
	return (i);
} */

/* char	**get_map(char *file)
{
	char	**map;
	char	*str;
	int		fd;
	int		i;

	i = file_lines(file);
	map = malloc(sizeof(char *) * (i + 1));
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening scene!\n");
		return (NULL);
	}
	str = get_next_line(fd);
	map[i] = NULL;
	i = 0;
	while (str)
	{
		map[i++] = ft_strdup(str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (map);
} */