/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:28:09 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/23 08:10:48 by gamekiller2      ###   ########.fr       */
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

int	intersect_plane(t_minirt *rt, t_plane *plane, t_point direction, double *t)
{
	double	npmo;
	double	nd;
	t_point	pmo;
	
	pmo = vecdif(plane->coordinates, rt->camera.coordinates);
	npmo = escprod(plane->n_vector, pmo);
	nd = escprod(plane->n_vector, direction);
	if (nd == 0)
		return (0);
	t[0] = npmo / nd;
	if (t[0] < 0)
		return (0);
	return (1);
}

t_color	intersect_scene(t_point direction, t_minirt *rt)
{
	double		t[2];
	t_point		bateu;
	t_point		normal;
	t_color		color;
	t_color		old_color;
	int			i;

	i = 0;
	rt->closest = 1e9;
	color = rt->alight.color;
	while (i < rt->sp)
	{
		if (intersect_sphere(&rt->sphere[i], direction, rt, t))
		{
			if (t[0] < 0)
				t[0] = t[1];
			if (t[0] > 0 && t[0] < rt->closest)
			{
				rt->closest = t[0];
				color = rt->sphere[i].color;
				old_color = color;
				bateu = vecsoma(rt->camera.coordinates, vecprodesc(direction, rt->closest));
				normal = vecdif(bateu, rt->sphere[i].coordinates);
				normal = vecnorm(normal);
				color = add_alight(color, rt);
				color = add_dlight(rt, color, old_color, bateu, normal);
			}
		}
		i++;
	}
	i = 0;
	while (i < rt->pl)
	{
		if (intersect_plane(rt, &rt->plane[i], direction, t))
		{
			if (t[0] > 0 && t[0] < rt->closest)
			{
				rt->closest = t[0];
				color = rt->plane[i].color;
				old_color = color;
				bateu = vecsoma(rt->camera.coordinates, vecprodesc(direction, rt->closest));
				normal = rt->plane[i].n_vector;
				color = add_alight(color, rt);
				color = add_dlight(rt, color, old_color, bateu, normal);
			}
		}
		i++;
	}
	return (color);
}
