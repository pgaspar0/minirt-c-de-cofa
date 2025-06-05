/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shorteners.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:46:04 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/04 17:13:56 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	initial_checks(int ac, char *av[])
{
	if (ac != 2)
	{
		printf("Invalid number of arguments!\n");
		return (0);
	}
	if (is_directory(av[1]) || is_bad_file_name(av[1]))
	{
		printf("Wrong file name\n");
		return (0);
	}
	return (1);
}

int	is_bad_file_name(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (!ft_strcmp(file + len - 3, ".rt"))
		return (0);
	return (1);
}

int	is_directory(const char *file)
{
	int		fd;
	char	buffer[1];

	errno = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	if (read(fd, buffer, 0) < 0 && errno == EISDIR)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

void	clean_all(t_minirt *rt)
{
	if (rt->img)
		mlx_destroy_image(rt->con, rt->img);
	if (rt->window)
		mlx_destroy_window(rt->con, rt->window);
	if (rt->con)
	{
		mlx_destroy_display(rt->con);
		free(rt->con);
	}
	if (rt->sphere)
		free(rt->sphere);
	if (rt->plane)
		free(rt->plane);
	if (rt->cylinder)
		free(rt->cylinder);
}

int	close_des(t_minirt *rt)
{
	clean_all(rt);
	exit(EXIT_SUCCESS);
	return (0);
}
