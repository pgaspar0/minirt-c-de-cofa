/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:11:18 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/27 16:21:42 by jorcarva         ###   ########.fr       */
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

int print_sphere_count(const t_minirt *rt)
{
    if (!rt)
    {
        fprintf(stderr, "Erro: Estrutura t_minirt nula.\n");
        return;
    }
    return(rt->sp);
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
    print_sphere_count(&rt);
    printf("Não teve erro aparentemente\n");
    free_matrix(map);
    rt.con = mlx_init();
    rt.window = mlx_new_window(rt.con, WIDTH, HEIGHT, "Ray fn Tracer");
    rt.img = mlx_new_image(rt.con, WIDTH, HEIGHT);
    rt.data = mlx_get_data_addr(rt.img, &rt.bpp, &rt.size_line, &rt.endian);
    init_camera(&rt);
    put_scene(&rt);
    mlx_put_image_to_window(rt.con, rt.window, rt.img, 0, 0);
    mlx_loop(rt.con);
    return (0);    
}