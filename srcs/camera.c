/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:01:13 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/16 22:32:19 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	init_camera(t_minirt *rt)
{
	t_point updef;

	updef.x = 0;
	updef.y = 1;
	updef.z = 0;
	rt->right = vecprod(updef, rt->camera.o_vector);
	rt->up = vecprod(rt->camera.o_vector, rt->right);
    rt->viewport_height = 2 * tan(rt->camera.fov / 2);
    rt->viewport_width = rt->viewport_height * ((double)(WIDTH/HEIGHT));
	rt->p_centro = vecsoma(rt->camera.coordinates, rt->camera.o_vector);
	rt->p_first = vecdif(rt->p_centro, vecprodesc(rt->right, rt->viewport_width / 2));
	rt->p_first = vecsoma(rt->p_first, vecprodesc(rt->up, rt->viewport_height / 2));
	rt->psizex = rt->viewport_width / WIDTH;
	rt->psizey = rt->viewport_height / HEIGHT;
}

t_point	get_pixel(int i, int j, t_minirt *rt)
{
	t_point	pixel;
	t_point right_part;
	t_point	up_part;

	right_part = vecprodesc(rt->right, i * rt->psizex);
	up_part = vecprodesc(rt->up, j * rt->psizey);
	pixel = vecsoma(rt->p_first, vecdif(right_part, up_part));
	return (pixel);
}

t_color	intersect(t_point direction, t_minirt *rt)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t[2];
	double	raio;
	t_point	oc;
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	raio = rt->sphere->diameter / 2;
	oc = vecdif(rt->camera.coordinates, rt->sphere->coordinates);
	a = escprod(direction, direction);
	b = 2 * (escprod(direction, oc));
	c = escprod(oc, oc) - (raio * raio);
	delta = (b * b) - (4 * a * c);
	if (delta < 0)
		return (color);
	t[0] = (-b - sqrt(delta)) / (2 * a);
	t[1] = (-b + sqrt(delta)) / (2 * a);
	if (t[0] > 0 || t[1] > 0)
		return (rt->sphere->color);
	return (color);
}

void	put_scene(t_minirt *rt)
{
	int		i;
	int		j;
	t_color	color;
	t_point	direction;
	t_point	pixel;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			pixel = get_pixel(i, j, rt);
			direction = vecnorm(vecdif(pixel, rt->camera.coordinates));
			color = intersect(direction, rt);
		}
	}
}