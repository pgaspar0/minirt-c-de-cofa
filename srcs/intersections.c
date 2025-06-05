/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:28:09 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/04 17:31:35 by jorcarva         ###   ########.fr       */
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

int	intersect_cap2(t_mini_intersect *inter, t_point center, double radius,
		double *t)
{
	double	denom;
	t_point	oc;
	double	t_hit;
	t_point	hit;
	t_point	dist;

	denom = escprod(inter->dir, inter->normal);
	if (fabs(denom) < 1e-6)
		return (0);
	oc = vecdif(center, inter->ro);
	t_hit = escprod(oc, inter->normal) / denom;
	if (t_hit < 0.001)
		return (0);
	hit = vecsoma(inter->ro, vecprodesc(inter->dir, t_hit));
	dist = vecdif(hit, center);
	if (vecmod(dist) > radius)
		return (0);
	*t = t_hit;
	return (1);
}

int	intersect_cylinder(t_cylinder *cy, t_point dir, t_minirt *rt, double *t)
{
	t_mini_intersect	t_inter;
	double				t0;
	double				t1;
	double				t_cap_top;
	t_point				cap_bottom;

	t0 = -1;
	t1 = -1;
	init_t_inter(&t_inter, cy, dir, rt);
	intersection_aux(&t_inter, &t0, &t1);
	caps_aux(&t_inter, &t_cap_top, &cap_bottom);
	ver_int(&t_inter, cap_bottom);
	if (t_inter.hit)
	{
		t[0] = t_inter.closest_t;
		return (1);
	}
	return (0);
}
