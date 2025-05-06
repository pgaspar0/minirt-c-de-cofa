/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:28:09 by pgaspar           #+#    #+#             */
/*   Updated: 2025/05/02 11:55:07 by jorcarva         ###   ########.fr       */
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

	// t_point	hit_point;
	rt->closest = 1e9;
	color = colormult(rt->alight.color, rt->alight.ratio);
	color = sphere_loop(rt, direction, t, color);
	color = plane_loop(rt, direction, t, color);
	color = cylinder_loop(rt, direction, t, color);
	// color
	// color = cylinder_loop(rt, direction, t);
	return (color);
}

// int	intersect_cylinder(t_cylinder *cy, t_point direction, t_minirt *rt,
// 		double *t)
// {
// 	t_point	oc;
// 	t_point	d;
// 	t_point	v;
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	delta;

// 	v = vecnorm(cy->a_vector);
// 	oc = vecdif(rt->camera.coordinates, cy->coordinates);
// 	d = direction;
// 	a = escprod(vecdif(d, vecprodesc(v, escprod(d, v))), vecdif(d, vecprodesc(v,
// 					escprod(d, v))));
// 	b = 2 * escprod(vecdif(d, vecprodesc(v, escprod(d, v))), vecdif(oc,
// 				vecprodesc(v, escprod(oc, v))));
// 	c = escprod(vecdif(oc, vecprodesc(v, escprod(oc, v))), vecdif(oc,
// 				vecprodesc(v, escprod(oc, v)))) - (cy->radius * cy->radius);
// 	delta = (b * b) - (4 * a * c);
// 	if (delta < 0)
// 		return (0);
// 	t[0] = (-b - sqrt(delta)) / (2 * a);
// 	t[1] = (-b + sqrt(delta)) / (2 * a);
// 	return (1);
// }

int	intersect_cap(t_point ro, t_point d, t_point center, t_point normal, double radius, double *t)
{
	double denom = escprod(d, normal);
	if (fabs(denom) < 1e-6)
		return (0); // Raio paralelo ao plano

	t_point oc = vecdif(center, ro);
	double t_hit = escprod(oc, normal) / denom;
	if (t_hit < 0.001)
		return (0); // Atrás da câmera

	t_point hit = vecsoma(ro, vecprodesc(d, t_hit));
	t_point dist = vecdif(hit, center);
	if (vecmod(dist) > radius)
		return (0); // Fora do círculo

	*t = t_hit;
	return (1);
}

int	intersect_cylinder(t_cylinder *cy, t_point dir, t_minirt *rt, double *t)
{
	t_point ro = rt->camera.coordinates;
	t_point axis = vecnorm(cy->a_vector);
	t_point oc = vecdif(ro, cy->coordinates);
	t_point d = dir;

	t_point d_proj = vecprodesc(axis, escprod(d, axis));
	t_point oc_proj = vecprodesc(axis, escprod(oc, axis));
	t_point d_perp = vecdif(d, d_proj);
	t_point oc_perp = vecdif(oc, oc_proj);

	double a = escprod(d_perp, d_perp);
	double b = 2 * escprod(d_perp, oc_perp);
	double c = escprod(oc_perp, oc_perp) - cy->radius * cy->radius;
	double delta = b * b - 4 * a * c;
	double t0 = -1, t1 = -1, tmp;
	double closest_t = -1;
	int hit = 0;
	t_point hit_point;

	if (delta >= 0)
	{
		t0 = (-b - sqrt(delta)) / (2 * a);
		t1 = (-b + sqrt(delta)) / (2 * a);
		if (t0 > t1) { tmp = t0; t0 = t1; t1 = tmp; }

		t_point hit_point = vecsoma(ro, vecprodesc(d, t0));
		double proj_len = escprod(vecdif(hit_point, cy->coordinates), axis);
		if (proj_len >= -cy->height / 2 && proj_len <= cy->height / 2 && t0 > 0.001)
		{
			closest_t = t0;
			hit = 1;
		}
		hit_point = vecsoma(ro, vecprodesc(d, t1));
		proj_len = escprod(vecdif(hit_point, cy->coordinates), axis);
		if (proj_len >= -cy->height / 2 && proj_len <= cy->height / 2 && t1 > 0.001)
		{
			if (!hit || t1 < closest_t)
			{
				closest_t = t1;
				hit = 1;
			}
		}
	}
	// Testa tampas (cap superior e inferior)
	double t_cap_top, t_cap_bottom;
	t_point cap_top = vecsoma(cy->coordinates, vecprodesc(axis, cy->height / 2));
	t_point cap_bottom = vecsoma(cy->coordinates, vecprodesc(axis, -cy->height / 2));
	t_point normal = vecnorm(cy->a_vector);
	if (intersect_cap(ro, d, cap_top, normal, cy->radius, &t_cap_top))
	{
		if (t_cap_top > 0.001 && (!hit || t_cap_top < closest_t))
		{
			closest_t = t_cap_top;
			hit_point = vecsoma(ro, vecprodesc(d, t_cap_top));
			normal = get_cylinder_normal(cy, hit_point);
			hit = 1;
		}
	}
	// normal = vecnorm(vecprodesc(cy->a_vector, -1));
	normal = vecprodesc(vecnorm(cy->a_vector), -1);
	if (intersect_cap(ro, d, cap_bottom, normal, cy->radius, &t_cap_bottom))
	{
		if (t_cap_bottom > 0.001 && (!hit || t_cap_bottom < closest_t))
		{
			closest_t = t_cap_bottom;
			hit_point = vecsoma(ro, vecprodesc(d, t_cap_bottom));
			hit = 1;
		}
	}
	if (hit)
	{
		t[0] = closest_t;
		return (1);
	}
	return (0);
}


// Interseção com a lateral de um cilindro finito
// int	intersect_cylinder(t_cylinder *cy, t_point dir, t_minirt *rt, double *t)
// {
// 	t_point	ro;
// 	t_point	axis;
// 	t_point	d;
// 	t_point	d_proj;
// 	t_point	oc_proj;
// 	t_point	d_perp;
// 	t_point	oc_perp;
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	delta;
// 	t_point	hit_point;
// 	double	proj_len;

// 	ro = rt->camera.coordinates;
// 	t_point oc = vecdif(ro, cy->coordinates); // ro - centro do cilindro
// 	axis = vecnorm(cy->a_vector);
// 	d = dir;
// 	d_proj = vecprodesc(axis, escprod(d, axis));
// 	oc_proj = vecprodesc(axis, escprod(oc, axis));
// 	d_perp = vecdif(d, d_proj);
// 	oc_perp = vecdif(oc, oc_proj);
// 	a = escprod(d_perp, d_perp);
// 	b = 2 * escprod(d_perp, oc_perp);
// 	c = escprod(oc_perp, oc_perp) - cy->radius * cy->radius;
// 	delta = b * b - 4 * a * c;
// 	double t0, t1, tmp;
// 	if (delta < 0)
// 		return (0);
// 	t0 = (-b - sqrt(delta)) / (2 * a);
// 	t1 = (-b + sqrt(delta)) / (2 * a);
// 	if (t0 > t1)
// 	{
// 		tmp = t0;
// 		t0 = t1;
// 		t1 = tmp;
// 	}
// 	// Testa t0
// 	hit_point = vecsoma(ro, vecprodesc(d, t0));
// 	// proj_len = escprod(vecdif(hit_point, cy->coordinates), axis);
// 	// if (proj_len >= 0 && proj_len <= cy->height)
// 	proj_len = escprod(vecdif(hit_point, cy->coordinates), axis);
// 	if (proj_len >= -cy->height / 2 && proj_len <= cy->height / 2)
// 	{
// 		t[0] = t0;
// 		return (1);
// 	}
// 	// Testa t1 se t0 estiver fora do cilindro
// 	hit_point = vecsoma(ro, vecprodesc(d, t1));
// 	// proj_len = escprod(vecdif(hit_point, cy->coordinates), axis);
// 	// if (proj_len >= 0 && proj_len <= cy->height)
// 	proj_len = escprod(vecdif(hit_point, cy->coordinates), axis);
// 	if (proj_len >= -cy->height / 2 && proj_len <= cy->height / 2)
// 	{
// 		t[0] = t1;
// 		return (1);
// 	}
// 	return (0);
// }
