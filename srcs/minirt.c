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

void    clean_all(t_minirt *rt)
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
        printf("Type: %d, Index: %d\n", rt->mini.type, rt->mini.index);
        rt->in = -1;
    }
    else if (button == 2)
    {
        rt->mini.type = 4;
        printf("Type: %d, Index: %d\n", rt->mini.type, rt->mini.index);
    }
    else if (button == 3)
    {
        rt->mini.type = 3;
        printf("Type: %d, Index: %d\n", rt->mini.type, rt->mini.index);
    }
    return (0);
}

void    transy(t_minirt *rt, double val)
{
    if (rt->mini.type == 0)
        rt->sphere[rt->mini.index].coordinates.y += val;
    else if (rt->mini.type == 1)
        rt->plane[rt->mini.index].coordinates.y += val;
    else if (rt->mini.type == 2)
        rt->cylinder[rt->mini.index].coordinates.y += val;
    else if (rt->mini.type == 3)
        rt->light.coordinates.y += val;
    else if (rt->mini.type == 4)
        rt->camera.coordinates.y += val;
}

void    transx(t_minirt *rt, double val)
{
    if (rt->mini.type == 0)
        rt->sphere[rt->mini.index].coordinates.x += val;
    else if (rt->mini.type == 1)
        rt->plane[rt->mini.index].coordinates.x += val;
    else if (rt->mini.type == 2)
        rt->cylinder[rt->mini.index].coordinates.x += val;
    else if (rt->mini.type == 3)
        rt->light.coordinates.x += val;
    else if (rt->mini.type == 4)
        rt->camera.coordinates.x += val;
}
void    transz(t_minirt *rt, double val)
{
    if (rt->mini.type == 0)
        rt->sphere[rt->mini.index].coordinates.z += val;
    else if (rt->mini.type == 1)
        rt->plane[rt->mini.index].coordinates.z += val;
    else if (rt->mini.type == 2)
        rt->cylinder[rt->mini.index].coordinates.z += val;
    else if (rt->mini.type == 3)
        rt->light.coordinates.z += val;
    else if (rt->mini.type == 4)
        rt->camera.coordinates.z += val;
}

void    up_check(t_minirt *rt, int *i)
{
    transy(rt, 0.5);
    if (rt->mini.type != -1)
        *i = 0;
}
void    down_check(t_minirt *rt, int *i)
{
    transy(rt, -0.5);
    if (rt->mini.type != -1)
        *i = 0;
}
void    left_check(t_minirt *rt, int *i)
{
    transx(rt, -0.5);
    if (rt->mini.type != -1)
        *i = 0;
}
void    right_check(t_minirt *rt, int *i)
{
    transx(rt, 0.5);
    if (rt->mini.type != -1)
        *i = 0;
}
void    i_check(t_minirt *rt, int *i)
{
    transz(rt, 0.5);
    if (rt->mini.type != -1)
        *i = 0;
}
void    k_check(t_minirt *rt, int *i)
{
    transz(rt, -0.5);
    if (rt->mini.type != -1)
        *i = 0;
}
void    w_check(t_minirt *rt, int *i)
{
    if (rt->mini.type == 1)
    {
        rt->plane[rt->mini.index].n_vector = rotate_y(rt->plane[rt->mini.index].n_vector, 0.1);
        *i = 0;
    }
    else if (rt->mini.type == 2)
    {
        rt->cylinder[rt->mini.index].a_vector = rotate_y(rt->cylinder[rt->mini.index].a_vector, 0.1);
        *i = 0;
    }
    else if (rt->mini.type == 3)
    {
        rt->light.coordinates = rotate_y(rt->light.coordinates, 0.1);
        *i = 0;
    }
    else if (rt->mini.type == 4)
    {
        rt->camera.o_vector = rotate_y(rt->camera.o_vector, 0.5);
        *i = 0;
    }
}
void    s_check(t_minirt *rt, int *i)
{
    if (rt->mini.type == 1)
    {
        rt->plane[rt->mini.index].n_vector = rotate_y(rt->plane[rt->mini.index].n_vector, -0.1);
        *i = 0;
    }
    else if (rt->mini.type == 2)
    {
        rt->cylinder[rt->mini.index].a_vector = rotate_y(rt->cylinder[rt->mini.index].a_vector, -0.1);
        *i = 0;
    }
    else if (rt->mini.type == 3)
    {
        rt->light.coordinates = rotate_y(rt->light.coordinates, -0.1);
        *i = 0;
    }
    else if (rt->mini.type == 4)
    {
        rt->camera.o_vector = rotate_y(rt->camera.o_vector, -0.5);
        *i = 0;
    }
}
void    a_check(t_minirt *rt, int *i)
{
    if (rt->mini.type == 1)
    {
        rt->plane[rt->mini.index].n_vector = rotate_x(rt->plane[rt->mini.index].n_vector, 0.1);
        *i = 0;
    }
    else if (rt->mini.type == 2)
    {
        rt->cylinder[rt->mini.index].a_vector = rotate_x(rt->cylinder[rt->mini.index].a_vector, 0.1);
        *i = 0;
    }
    else if (rt->mini.type == 3)
    {
        rt->light.coordinates = rotate_x(rt->light.coordinates, 0.1);
        *i = 0;
    }
    else if (rt->mini.type == 4)
    {
        rt->camera.o_vector = rotate_x(rt->camera.o_vector, 0.5);
        *i = 0;
    }
}
void    d_check(t_minirt *rt, int *i)
{
    if (rt->mini.type == 1)
    {
        rt->plane[rt->mini.index].n_vector = rotate_x(rt->plane[rt->mini.index].n_vector, -0.1);
        *i = 0;
    }
    else if (rt->mini.type == 2)
    {
        rt->cylinder[rt->mini.index].a_vector = rotate_x(rt->cylinder[rt->mini.index].a_vector, -0.1);
        *i = 0;
    }
    else if (rt->mini.type == 3)
    {
        rt->light.coordinates = rotate_x(rt->light.coordinates, -0.1);
        *i = 0;
    }
    else if (rt->mini.type == 4)
    {
        rt->camera.o_vector = rotate_x(rt->camera.o_vector, -0.5);
        *i = 0;
    }
}
void    q_check(t_minirt *rt, int *i)
{
    if (rt->mini.type == 1)
    {
        rt->plane[rt->mini.index].n_vector = rotate_z(rt->plane[rt->mini.index].n_vector, 0.1);
        *i = 0;
    }
    else if (rt->mini.type == 2)
    {
        rt->cylinder[rt->mini.index].a_vector = rotate_z(rt->cylinder[rt->mini.index].a_vector, 0.1);
        *i = 0;
    }
    else if (rt->mini.type == 3)
    {
        rt->light.coordinates = rotate_z(rt->light.coordinates, 0.1);
        *i = 0;
    }
    else if (rt->mini.type == 4)
    {
        rt->camera.o_vector = rotate_z(rt->camera.o_vector, 0.5);
        *i = 0;
    }
}
void    e_check(t_minirt *rt, int *i)
{
    if (rt->mini.type == 1)
    {
        rt->plane[rt->mini.index].n_vector = rotate_z(rt->plane[rt->mini.index].n_vector, -0.1);
        *i = 0;
    }
    else if (rt->mini.type == 2)
    {
        rt->cylinder[rt->mini.index].a_vector = rotate_z(rt->cylinder[rt->mini.index].a_vector, -0.1);
        *i = 0;
    }
    else if (rt->mini.type == 3)
    {
        rt->light.coordinates = rotate_z(rt->light.coordinates, -0.1);
        *i = 0;
    }
    else if (rt->mini.type == 4)
    {
        rt->camera.o_vector = rotate_z(rt->camera.o_vector, -0.5);
        *i = 0;
    }
}

int keys(int keycode, void *param)
{
    t_minirt    *rt;
    int         i;

    i = -1;
    rt = (t_minirt *) param;
    if (keycode == XK_Escape)
    {
        clean_all(rt);
        exit(EXIT_SUCCESS);
    }
    if (keycode == XK_Up)
        up_check(rt, &i);
    if (keycode == XK_Down)
        down_check(rt, &i);
    if (keycode == XK_Right)
        right_check(rt, &i);
    if (keycode == XK_Left)
        left_check(rt, &i);
    if (keycode == XK_i || keycode == XK_I)
        i_check(rt, &i);
    if (keycode == XK_k || keycode == XK_K)
        k_check(rt, &i);
    if (keycode == XK_w || keycode == XK_W)
        w_check(rt, &i);
    if (keycode == XK_s || keycode == XK_S)
        s_check(rt, &i);
    if (keycode == XK_a || keycode == XK_A)
        a_check(rt, &i);
    if (keycode == XK_d || keycode == XK_D)
        d_check(rt, &i);
    if (keycode == XK_q || keycode == XK_Q)
        q_check(rt, &i);
    if (keycode == XK_e || keycode == XK_E)
        e_check(rt, &i);
    if (i != -1)
    {
        put_scene(rt);
        mlx_put_image_to_window(rt->con, rt->window, rt->img, 0, 0);
    }
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
    mlx_key_hook(rt.window, keys, &rt);
    mlx_mouse_hook(rt.window, mouses, &rt);
    mlx_loop(rt.con);
    return (0);    
}
