/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:11:18 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/27 08:29:24 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	put_pixel(t_minirt *rt, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * rt->size_line + x * (rt->bpp / 8);
	dst = rt->data + offset;
	if (x < WIDTH && x >= 0 && y >= 0 && y < HEIGHT)
		*(unsigned int *)dst = color;
}

void	init_mlx(t_minirt *rt)
{
	rt->con = mlx_init();
	rt->window = mlx_new_window(rt->con, WIDTH, HEIGHT, "Ray fn Tracer");
	rt->img = mlx_new_image(rt->con, WIDTH, HEIGHT);
	rt->data = mlx_get_data_addr(rt->img, &rt->bpp, &rt->size_line,
			&rt->endian);
}

int	main(int ac, char *av[])
{
	char		**map;
	t_minirt	rt;

	if (!initial_checks(ac, av, &rt))
		return (0);
	map = get_map(av[1]);
	if (!map)
		return (0);
	rt.complete = 1;
	count_elements(map, &rt);
	if (rt.al != 1 || rt.l != 1 || rt.c != 1 || rt.complete != 1)
		return (printf("Error\nMisconfiguration\n"), free_matrix(map), 0);
	parse_map(map, &rt);
	free_matrix(map);
	if (rt.error == 0)
	{
		printf("Error\nMisconfiguration\n");
		free(rt.sphere);
		free(rt.plane);
		free(rt.cylinder);
		return (1);
	}
	if (check_scene(&rt))
	{
		printf("Error\nMisconfiguration\n");
		free(rt.sphere);
		free(rt.plane);
		free(rt.cylinder);
		return (1);
	}
	init_mlx(&rt);
	init_camera(&rt);
	put_scene(&rt);
	mlx_put_image_to_window(rt.con, rt.window, rt.img, 0, 0);
	mlx_hook(rt.window, 17, 0, close_des, &rt);
	mlx_key_hook(rt.window, keys, &rt);
	mlx_mouse_hook(rt.window, mouses, &rt);
	mlx_loop(rt.con);
	return (0);
}
