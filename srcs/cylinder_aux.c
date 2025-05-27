/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:14:57 by jorcarva          #+#    #+#             */
/*   Updated: 2025/05/27 19:49:49 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	check_cylinder_body(t_cylinder_state *s, int i)
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

void	check_cap_top(t_cylinder_state *s, int i, t_point axis, t_point ro)
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

void	check_cap_bottom(t_cylinder_state *s, int i, t_point axis,
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

void	check_caps(t_cylinder_state *s, int i)
{
	t_point	axis;
	t_point	ro;

	axis = vecnorm(s->rt->cylinder[i].a_vector);
	ro = s->rt->camera.coordinates;
	check_cap_top(s, i, axis, ro);
	check_cap_bottom(s, i, axis, ro);
}

void	final_lighting(t_cylinder_state *s)
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
