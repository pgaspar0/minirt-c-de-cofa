/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:28:09 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/21 11:28:10 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	intersect_sphere(t_sphere *sphere, t_point direction, t_minirt *rt, double *t)
{
	t_point	oc;
	double	a;
	double	b;
	double	c;
	double	delta;

	oc = vecdif(rt->camera.coordinates, sphere->coordinates);
	a = escprod(direction, direction);
	b = 2 * (escprod(direction, oc));
	c = escprod(oc, oc) - (sphere->radius * sphere->radius);
	delta = (b * b) - (4 * a * c);
	if (delta < 0)
		return (0);
	t[0] = (-b - sqrt(delta)) / (2 * a);
	t[1] = (-b + sqrt(delta)) / (2 * a);
	return (1);
}

t_color	intersect_scene(t_point direction, t_minirt *rt)
{
	double		closest;
	double		t[2];
	t_color		color;
	int			i;

	i = 0;
	closest = 1e9;
	color = rt->alight.color;
	while (i < rt->sp)
	{
		if (intersect_sphere(&rt->sphere[i], direction, rt, t))
		{
			if (t[0] < 0)
				t[0] = t[1];
			if (t[0] > 0 && t[0] < closest)
			{
				closest = t[0];
				color = rt->sphere[i].color;
			}
		}
		i++;
	}
	return (color);
}
