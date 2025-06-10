/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interloops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:39:50 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/10 20:03:21 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	mini_autofill(t_minirt *rt, int type, int index)
{
	if (rt->in == 0)
	{
		rt->mini.type = type;
		rt->mini.index = index;
	}
	return ;
}

t_color	sphere_loop(t_minirt *rt, t_point direction, double *t, t_color color)
{
	int		i;
	t_vecs	vec;

	i = -1;
	while (++i < rt->sp)
	{
		if (intersect_sphere(&rt->sphere[i], direction, rt, t))
		{
			if (t[0] < 0)
				t[0] = t[1];
			if (t[0] > 0 && t[0] < rt->closest)
			{
				rt->closest = t[0];
				color = rt->sphere[i].color;
				vec.vec1 = vecsoma(rt->camera.coordinates,
						vecprodesc(direction, rt->closest));
				vec.vec2 = vecnorm(vecdif(vec.vec1,
							rt->sphere[i].coordinates));
				color = add_light(color, rt, &vec, 0);
				mini_autofill(rt, 0, i);
			}
		}
	}
	return (color);
}

t_color	plane_loop(t_minirt *rt, t_point direction, double *t, t_color color)
{
	int		i;
	t_vecs	vec;

	i = 0;
	while (i < rt->pl)
	{
		if (intersect_plane(rt, &rt->plane[i], direction, t))
		{
			if (t[0] > 0 && t[0] < rt->closest)
			{
				rt->closest = t[0];
				color = rt->plane[i].color;
				vec.vec1 = vecsoma(rt->camera.coordinates,
						vecprodesc(direction, rt->closest));
				vec.vec2 = rt->plane[i].n_vector;
				color = add_light(color, rt, &vec, 0);
				mini_autofill(rt, 1, i);
			}
		}
		i++;
	}
	return (color);
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
