/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interloops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:39:50 by pgaspar           #+#    #+#             */
/*   Updated: 2025/05/27 19:51:23 by jorcarva         ###   ########.fr       */
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
	t_point	bateu;
	t_point	normal;

	i = 0;
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
				bateu = vecsoma(rt->camera.coordinates, vecprodesc(direction,
							rt->closest));
				normal = vecnorm(vecdif(bateu, rt->sphere[i].coordinates));
				color = add_light(color, rt, bateu, normal, 0);
				mini_autofill(rt, 0, i);
			}
		}
		i++;
	}
	return (color);
}

t_color	plane_loop(t_minirt *rt, t_point direction, double *t, t_color color)
{
	int		i;
	t_point	bateu;
	t_point	normal;

	i = 0;
	while (i < rt->pl)
	{
		if (intersect_plane(rt, &rt->plane[i], direction, t))
		{
			if (t[0] > 0 && t[0] < rt->closest)
			{
				rt->closest = t[0];
				color = rt->plane[i].color;
				bateu = vecsoma(rt->camera.coordinates, vecprodesc(direction,
							rt->closest));
				normal = rt->plane[i].n_vector;
				color = add_light(color, rt, bateu, normal, 0);
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

// t_color	cylinder_loop(t_minirt *rt, t_point dir, double *closest_t,
//		t_color color)
// {
// 	double	t;
// 	int		i;
// 	int		closest_i;
// 	int		aux;
// 	double t_global;
// 	t_point	axis;
// 	t_point ro;
// 	// t_point cap_top;

// 	i = 0;
// 	t = -1;
// 	closest_i = -1;
// 	aux = 0;
// 	t_global = 1e9;
// 	while (i < rt->cy)
// 	{
// 		if (intersect_cylinder(&rt->cylinder[i], dir, rt, &t))
// 		{
// 			if (t > 0.001 && t < rt->closest && t < t_global)
// 			{
// 				cylinder_loop_aux1(t, &t_global, &closest_t);
// 				color = cylinder_loop_aux2(i, rt, &closest_i);
// 				mini_autofill(rt, 2, i);
// 			}
// 		}
// 		// Parâmetros comuns
// 		// if(t < t_global && cap_top_aux(rt, dir, closest_t, t_cap_top))
// 		// {
// 		// 	t_global = t;
// 		// 	// cap_top_aux(rt, dir, closest_t, t_cap_top);
// 		// }

// 		/*axis = vecnorm(rt->cylinder[i].a_vector);
// 		ro = rt->camera.coordinates;

// 		// Tampa superior
// 		cap_top = vecsoma(rt->cylinder[i].coordinates,
// 			vecprodesc(axis, rt->cylinder[i].height / 2));
// 		double t_cap_top;
// 		if (intersect_cap(ro, dir, cap_top, axis, rt->cylinder[i].radius,
//&t_cap_top))
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
// 		}*/

// 		// Tampa inferior
// 		t_point cap_bottom = vecsoma(rt->cylinder[i].coordinates,
// 			vecprodesc(axis, -rt->cylinder[i].height / 2));
// 		double t_cap_bottom;
// 		if (intersect_cap(ro, dir, cap_bottom, vecprodesc(axis, -1),
// 				rt->cylinder[i].radius, &t_cap_bottom))
// 		{
// 			if (t_cap_bottom > 0.001 && t_cap_bottom < rt->closest
//				&& t_cap_bottom < closest_t[1] && t < t_global)
// 			{
// 				t_global = t;
// 				closest_t[1] = t_cap_bottom;
// 				closest_i = i;
// 				color = rt->cylinder[i].color;
// 				aux = 1;
// 			}
// 		}
// 		i++;
// 	}
// 	if (rt->closest > t_global && t_global > 0)
// 	{
// 		t_point hit_point = vecsoma(rt->camera.coordinates, vecprodesc(dir,
//					t_global));
// 		t_point normal = get_cylinder_normal(&rt->cylinder[closest_i],
//				hit_point, 0.0, 0.0);
// 		color = add_light(color, rt, hit_point, normal, aux);
// 	}
// 	return (color);
// }

// a função do cylinder_loop que funciona
// t_color	cylinder_loop(t_minirt *rt, t_point dir, double *closest_t,
//		t_color color)
// {
// 	double	t = -1;
// 	int		i;
// 	int		closest_i = -1;
// 	int		aux = 0;
// 	int		entrou = 0;
// 	double t_global = 1e9;

// 	i = 0;
// 	while (i < rt->cy)
// 	{
// 		if (intersect_cylinder(&rt->cylinder[i], dir, rt, &t))
// 		{
//         	// closest_t[0] = cylinder_loop_aux1(t, rt, t_global, i);
// 			// closest_i = i;
// 			  // color = rt->cylinder[i].color;
// 			if (t > 0.001 && t < rt->closest && t < t_global)
// 			{
// 				t_global = t;
// 				closest_t[0] = t;
// 				closest_i = i;
// 				color = rt->cylinder[i].color;
// 				if (rt->in == 0)
// 				{
// 					rt->mini.type = 2;
// 					rt->mini.index = i;
// 				}
// 			}
// 		}
// 		// Parâmetros comuns
// 		t_point axis = vecnorm(rt->cylinder[i].a_vector);
// 		t_point ro = rt->camera.coordinates;
// 		// Tampa superior
// 		t_point cap_top = vecsoma(rt->cylinder[i].coordinates,
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
// 		// Tampa inferior
// 		t_point cap_bottom = vecsoma(rt->cylinder[i].coordinates,
// 			vecprodesc(axis, -rt->cylinder[i].height / 2));
// 		double t_cap_bottom;
// 		if (intersect_cap(ro, dir, cap_bottom, vecprodesc(axis, -1),
// 				rt->cylinder[i].radius, &t_cap_bottom))
// 		{
// 			if (t_cap_bottom > 0.001 && t_cap_bottom < rt->closest
//				&& t_cap_bottom < closest_t[1] && t < t_global)
// 			{
// 				t_global = t;
// 				closest_t[1] = t_cap_bottom;
// 				closest_i = i;
// 				color = rt->cylinder[i].color;
// 				aux = 1;
// 			}
// 		}
// 		entrou = 0;
// 		i++;
// 	}
// 	(void)entrou;
// 	if (rt->closest > t_global && t_global > 0)
// 	{
// 		t_point ro = rt->camera.coordinates;
// 		t_point dir_scaled = vecprodesc(dir, t_global);
// 		t_point hit_point = vecsoma(ro, dir_scaled);
// 		t_point normal = get_cylinder_normal(&rt->cylinder[closest_i],
//				hit_point);
// 		color = add_light(color, rt, hit_point, normal, aux);
// 	}
// 	return (color);
// }
