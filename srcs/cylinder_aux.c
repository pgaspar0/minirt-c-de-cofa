/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:14:57 by jorcarva          #+#    #+#             */
/*   Updated: 2025/05/26 20:10:27 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_point	get_cylinder_normal(t_cylinder *cy, t_point hit, double dist_top,
		double dist_bottom)
{
	t_point	axis;
	t_point	c_to_p;
	t_point	proj;
	t_point	top;
	t_point	bottom;

	axis = vecnorm(cy->a_vector);
	top = vecsoma(cy->coordinates, vecprodesc(axis, cy->height / 2));
	bottom = vecsoma(cy->coordinates, vecprodesc(axis, -cy->height / 2));
	dist_top = vecmod(vecdif(hit, top));
	dist_bottom = vecmod(vecdif(hit, bottom));
	if (dist_top <= cy->radius + 0.0001)
		return (axis);
	if (dist_bottom <= cy->radius + 0.0001)
		return (vecprodesc(axis, -1));
	c_to_p = vecdif(hit, cy->coordinates);
	proj = vecprodesc(axis, escprod(c_to_p, axis));
	return (vecnorm(vecdif(c_to_p, proj)));
}

// t_point	axis;
// t_point	to_hit;
// vecnorm(cy->a_vector) = vecnorm(cy->a_vector);
// vecdif(hit, base) = vecdif(hit, base);

// t_point	get_cylinder_normal2(t_cylinder *cy, t_point hit, int aux,
// double proj_len)
// {
// 	t_point	top;
// 	t_point	bottom;
// 	t_point	base;
// 	t_point	proj;
// 	t_point	normal;

// 	if (aux == 1)
// 	{
// 		top = vecsoma(cy->coordinates, vecprodesc(vecnorm(cy->a_vector),
// 					cy->height / 2));
// 		bottom = vecsoma(cy->coordinates, vecprodesc(vecnorm(cy->a_vector),
// 					-cy->height / 2));
// 		if (vecmod(vecdif(hit, top)) < vecmod(vecdif(hit, bottom)))
// 			return (vecnorm(cy->a_vector));
// 		else
// 			return (vecprodesc(vecnorm(cy->a_vector), -1));
// 	}
// 	base = vecsoma(cy->coordinates, vecprodesc(vecnorm(cy->a_vector),
// 				-cy->height / 2));
// 	proj_len = escprod(vecdif(hit, base), vecnorm(cy->a_vector));
// 	proj = vecprodesc(vecnorm(cy->a_vector), proj_len);
// 	normal = vecdif(vecdif(hit, base), proj);
// 	return (vecnorm(normal));
// }

// void	cylinder_loop_aux1(double t, double *t_global, double **closest_t)
// {
// 	*t_global = t;
// 	*closest_t[0] = t;
// }

// t_color	cylinder_loop_aux2(int i, t_minirt *rt, int *closest_i)
// {
// 	*closest_i = i;
// 	return (rt->cylinder[i].color);
// }

// cap_top = vecsoma(rt->cylinder[i].coordinates,
// 			vecprodesc(axis, rt->cylinder[i].height / 2));
// 		double t_cap_top;
// 		if (intersect_cap(ro, dir, cap_top, axis, rt->cylinder[i].radius,
//				&t_cap_top))
// 		{
// 			if (t_cap_top > 0.001 && t_cap_top < rt->closest
//				&& t_cap_top < closest_t[1] && t < t_global)
// 			{
// 				t_global = t;
// 				closest_t[1] = t_cap_top;
// 				closest_i = i;
// 				color = rt->cylinder[i].color;
// 				aux = 1;
// 			}
// 		}

/*
rt

dir
*/

// int	cap_top_aux(t_minirt *rt, t_point dir, double *closest_t,
// 		double t_cap_top)
// {
// 	t_point cap_top;
// 	t_point axis;

// 	axis = vecnorm(rt->cylinder[i].a_vector);
// 	cap_top = vecsoma(rt->cylinder[i].coordinates,
// 			vecprodesc(axis, rt->cylinder[i].height / 2));
// 	if (intersect_cap(ro, dir, cap_top, axis,
// 			rt->cylinder[i].radius, &t_cap_top))
// 	{
// 		if (t_cap_top > 0.001 && t_cap_top < rt->closest
// 			&& t_cap_top < closest_t[1])
// 		{
// 			closest_t[1] = t_cap_top;
// 			closest_i = i;
// 			color = rt->cylinder[i].color;
// 			aux = 1;
// 			return (1);
// 		}
// 	}
// }

static void	check_cylinder_body(t_cylinder_state *s, int i)
{
	if (s->t > 0.001 && s->t < s->rt->closest && s->t < s->t_global)
	{
		s->t_global = s->t;
		s->closest_t[0] = s->t;
		s->closest_i = i;
		s->color = s->rt->cylinder[i].color;
		if (s->rt->in == 0)
		{
			s->rt->mini.type = 2;
			s->rt->mini.index = i;
		}
	}
}

static void	check_cap_top(t_cylinder_state *s, int i, t_point axis, t_point ro)
{
	t_point	cap_top;
	double	t_cap_top;

	cap_top = vecsoma(s->rt->cylinder[i].coordinates, vecprodesc(axis,
				s->rt->cylinder[i].height / 2));
	if (intersect_cap(ro, s->dir, cap_top, axis, s->rt->cylinder[i].radius,
			&t_cap_top))
	{
		if (t_cap_top > 0.001 && t_cap_top < s->rt->closest
			&& t_cap_top < s->closest_t[1] && s->t < s->t_global)
		{
			s->t_global = s->t;
			s->closest_t[1] = t_cap_top;
			s->closest_i = i;
			s->color = s->rt->cylinder[i].color;
			s->aux = 1;
		}
	}
}

static void	check_cap_bottom(t_cylinder_state *s, int i, t_point axis,
		t_point ro)
{
	t_point	cap_bottom;
	double	t_cap_bottom;

	cap_bottom = vecsoma(s->rt->cylinder[i].coordinates, vecprodesc(axis,
				-s->rt->cylinder[i].height / 2));
	if (intersect_cap(ro, s->dir, cap_bottom, vecprodesc(axis, -1),
			s->rt->cylinder[i].radius, &t_cap_bottom))
	{
		if (t_cap_bottom > 0.001 && t_cap_bottom < s->rt->closest
			&& t_cap_bottom < s->closest_t[1] && s->t < s->t_global)
		{
			s->t_global = s->t;
			s->closest_t[1] = t_cap_bottom;
			s->closest_i = i;
			s->color = s->rt->cylinder[i].color;
			s->aux = 1;
		}
	}
}

static void	check_caps(t_cylinder_state *s, int i)
{
	t_point	axis;
	t_point	ro;

	axis = vecnorm(s->rt->cylinder[i].a_vector);
	ro = s->rt->camera.coordinates;
	check_cap_top(s, i, axis, ro);
	check_cap_bottom(s, i, axis, ro);
}

static void	final_lighting(t_cylinder_state *s)
{
	t_point	ro;
	t_point	dir_scaled;
	t_point	hit_point;
	t_point	normal;

	if (s->rt->closest > s->t_global && s->t_global > 0)
	{
		ro = s->rt->camera.coordinates;
		dir_scaled = vecprodesc(s->dir, s->t_global);
		hit_point = vecsoma(ro, dir_scaled);
		normal = get_cylinder_normal(&s->rt->cylinder[s->closest_i], hit_point,
				0.0, 0.0);
		s->color = add_light(s->color, s->rt, hit_point, normal, s->aux);
	}
}

t_color	cylinder_loop(t_minirt *rt, t_point dir, double *closest_t,
		t_color color)
{
	t_cylinder_state	s;
	int					i;

	s.rt = rt;
	s.dir = dir;
	s.color = color;
	s.closest_t = closest_t;
	s.closest_i = -1;
	s.t_global = 1e9;
	s.aux = 0;
	i = 0;
	while (i < rt->cy)
	{
		s.t = -1;
		if (intersect_cylinder(&rt->cylinder[i], dir, rt, &s.t))
		{
			check_cylinder_body(&s, i);
		}
		check_caps(&s, i);
		i++;
	}
	final_lighting(&s);
	return (s.color);
}
