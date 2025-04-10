/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:28:09 by pgaspar           #+#    #+#             */
/*   Updated: 2025/04/08 17:54:04 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	intersect_sphere(t_sphere *sphere, t_point direction, t_minirt *rt,
		double *t)
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
	double	t[2];
	t_color	color;

	rt->closest = 1e9;
	color = colormult(rt->alight.color, rt->alight.ratio);
	color = sphere_loop(rt, direction, t, color);
	color = plane_loop(rt, direction, t, color);
	color = cylinder_loop(rt, direction, t, color);
	return (color);
}

int	intersect_cylinder(t_cylinder *cy, t_point direction, t_minirt *rt,
		double *t)
{
	t_point	oc;
	t_point	d;
	t_point	v;
	double	a;
	double	b;
	double	c;
	double	delta;

	v = vecnorm(cy->a_vector);
	oc = vecdif(rt->camera.coordinates, cy->coordinates);
	d = direction;
	a = escprod(vecdif(d, vecprodesc(v, escprod(d, v))), vecdif(d, vecprodesc(v,
					escprod(d, v))));
	b = 2 * escprod(vecdif(d, vecprodesc(v, escprod(d, v))), vecdif(oc,
				vecprodesc(v, escprod(oc, v))));
	c = escprod(vecdif(oc, vecprodesc(v, escprod(oc, v))), vecdif(oc,
				vecprodesc(v, escprod(oc, v)))) - (cy->radius * cy->radius);
	delta = (b * b) - (4 * a * c);
	if (delta < 0)
		return (0);
	t[0] = (-b - sqrt(delta)) / (2 * a);
	t[1] = (-b + sqrt(delta)) / (2 * a);
	return (1);
}
