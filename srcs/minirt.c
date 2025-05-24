/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:11:18 by pgaspar           #+#    #+#             */
/*   Updated: 2025/05/21 20:10:23 by jorcarva         ###   ########.fr       */
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

int mouses(int button, int x, int y, void *param)
{
    t_minirt *rt;
    t_point	pixel;
	t_point	direction;

    rt = (t_minirt *) param;
    if (button == 1)
    {
        rt->in = 0;
		pixel = get_pixel(x, y, rt);
        direction = vecdif(pixel, rt->camera.coordinates);
		direction = vecnorm(direction);
		intersect_scene(direction, rt);
        rt->in = -1;
    }
    else if (button == 2)
        rt->mini.type = 4;
    else if (button == 3)
        rt->mini.type = 3;
    return (0);
}

void    init_mlx(t_minirt *rt)
{
    rt->con = mlx_init();
    rt->window = mlx_new_window(rt->con, WIDTH, HEIGHT, "Ray fn Tracer");
    rt->img = mlx_new_image(rt->con, WIDTH, HEIGHT);
    rt->data = mlx_get_data_addr(rt->img, &rt->bpp, &rt->size_line, &rt->endian);
}

int main(int ac, char *av[])
{
    char    **map;
    t_minirt    rt;

    if (ac != 2)
    {
        printf("Invalid number of arguments!\n");
        return (0);
    }
    map = get_map(av[1]);
    if (!map)
        return (0);
    parse_map(map, &rt);
    if(check_scene(&rt))
         return (1);
    free_matrix(map);
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
