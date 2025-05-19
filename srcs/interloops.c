/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interloops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:39:50 by pgaspar           #+#    #+#             */
/*   Updated: 2025/05/06 10:56:59 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
				// color = add_light(color, rt, bateu, normal);
				color = add_light(color, rt, bateu, normal, 0);
				if (rt->in == 0)
				{
					rt->mini.type = 0;
					rt->mini.index = i;
				}
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
				// color = add_light(color, rt, bateu, normal);
				color = add_light(color, rt, bateu, normal, 0);
				if (rt->in == 0)
				{
					rt->mini.type = 1;
					rt->mini.index = i;
				}
			}
		}
		i++;
	}
	return (color);
}

// t_color	cylinder_loop(t_minirt *rt, t_point direction, double *t, t_color color)
// {
// 	int		i;
// 	t_point	bateu;
// 	t_point	normal;
// 	t_point	v;
// 	t_point	tmp;

// 	i = 0;
// 	while (i < rt->cy)
// 	{
// 		if (intersect_cylinder(&rt->cylinder[i], direction, rt, t))
// 		{
// 			if (t[0] < 0)
// 				t[0] = t[1];
// 			if (t[0] > 0 && t[0] < rt->closest)
// 			{
// 				rt->closest = t[0];
// 				color = rt->cylinder[i].color;
// 				bateu = vecsoma(rt->camera.coordinates, vecprodesc(direction,
// 							t[0]));
// 				v = vecnorm(rt->cylinder[i].a_vector);
// 				tmp = vecprodesc(v, escprod(vecdif(bateu,
// 								rt->cylinder[i].coordinates), v));
// 				normal = vecnorm(vecdif(vecdif(bateu,
// 								rt->cylinder[i].coordinates), tmp));
// 				color = add_light(color, rt, bateu, normal);
// 			}
// 		}
// 		i++;
// 	}
// 	return (color);
// }

// t_point	get_cylinder_normal(t_cylinder *cy, t_point hit)
// {
// 	t_point	axis = vecnorm(cy->a_vector);
// 	t_point	top = vecsoma(cy->coordinates, vecscale(axis, cy->height / 2));
// 	t_point	bottom = vecsoma(cy->coordinates, vecscale(axis, -cy->height / 2));

// 	if (vecmod(vecdif(hit, top)) < 1e-6)
// 		return axis;
// 	if (vecmod(vecdif(hit, bottom)) < 1e-6)
// 		return vecscale(axis, -1);

// 	t_point	proj = vecscale(axis, escprod(vecdif(hit, cy->coordinates), axis));
// 	t_point	normal = vecdif(vecdif(hit, cy->coordinates), proj);
// 	return vecnorm(normal);
// }

t_point	get_cylinder_normal(t_cylinder *cy, t_point hit)
{
	t_point	axis;
	t_point	c_to_p;
	t_point	proj;
	t_point	top;
	t_point	bottom;
	double	dist_top;
	double	dist_bottom;

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

t_point get_cylinder_normal2(t_cylinder *cy, t_point hit, int aux)
{
	t_point axis = vecnorm(cy->a_vector);

	if (aux == 1) // Se for tampa
	{
		t_point top = vecsoma(cy->coordinates, vecprodesc(axis, cy->height / 2));
		t_point bottom = vecsoma(cy->coordinates, vecprodesc(axis, -cy->height / 2));

		if (vecmod(vecdif(hit, top)) < vecmod(vecdif(hit, bottom)))
			return axis; // Tampa superior
		else
			return vecprodesc(axis, -1); // Tampa inferior
	}
	else // Se for lateral
	{
		// Ponto base (centro da base inferior)
		t_point base = vecsoma(cy->coordinates, vecprodesc(axis, -cy->height / 2));
		// Vetor do ponto base até o hit point
		t_point to_hit = vecdif(hit, base);
		// Projeta to_hit sobre o eixo
		double proj_len = escprod(to_hit, axis);
		t_point proj = vecprodesc(axis, proj_len);
		t_point normal = vecdif(to_hit, proj);
		return vecnorm(normal);
	}
}




// t_color	cylinder_loop(t_minirt *rt, t_point dir, double *closest_t, t_color color)
// {
// 	double	t;
// 	int		i;
// 	int		closest_i = -1;

// 	i = 0;
// 	while (i < rt->cy)
// 	{
// 		if (intersect_cylinder(&rt->cylinder[i], dir, rt, &t))
// 		{
// 			if (t > 0.001 && t < *closest_t)
// 			{
// 				*closest_t = t;
// 				closest_i = i;
// 				color = rt->cylinder[i].color;
// 			}
// 		}
// 		i++;
// 	}
// 	if (closest_i != -1)
// 	{
// 		t_point ro = rt->camera.coordinates;
// 		t_point dir_scaled = vecprodesc(dir, *closest_t);
// 		t_point hit_point = vecsoma(ro, dir_scaled);
// 		t_point normal = get_cylinder_normal(&rt->cylinder[closest_i], hit_point);
// 		color = add_light(color, rt, hit_point, normal, 1);
// 	}
// 	return (color);
// }

// t_color	cylinder_loop(t_minirt *rt, t_point dir, double *closest_t, t_color color)
// {
// 	double	t;
// 	int		i;
// 	int		closest_i = -1;
// 	int		hit_part = -1; // 0 = lateral, 1 = tampa sup, 2 = tampa inf

// 	i = 0;
// 	while (i < rt->cy)
// 	{
// 		t_point axis = vecnorm(rt->cylinder[i].a_vector);
// 		t_point ro = rt->camera.coordinates;

// 		// ------ LATERAL ------
// 		t = -1;
// 		if (intersect_cylinder(&rt->cylinder[i], dir, rt, &t))
// 		{
// 			if (t > 0.001 && t < *closest_t)
// 			{
// 				*closest_t = t;
// 				rt->closest = t;
// 				closest_i = i;
// 				color = rt->cylinder[i].color;
// 				hit_part = 0;
// 			}
// 		}

// 		// ------ TAMPA SUPERIOR ------
// 		t_point cap_top = vecsoma(rt->cylinder[i].coordinates,
// 			vecprodesc(axis, rt->cylinder[i].height / 2));
// 		double t_top = -1;
// 		if (intersect_cap(ro, dir, cap_top, axis, rt->cylinder[i].radius, &t_top))
// 		{
// 			if (t_top > 0.001 && t_top < *closest_t)
// 			{
// 				t_point hit = vecsoma(ro, vecprodesc(dir, t_top));
// 				// Verifica se o ponto está dentro da altura do cilindro
// 				double proj = escprod(vecdif(hit, rt->cylinder[i].coordinates), axis);
// 				if (fabs(proj) <= rt->cylinder[i].height / 2)
// 				{
// 					*closest_t = t_top;
// 					rt->closest = t_top;
// 					closest_i = i;
// 					color = rt->cylinder[i].color;
// 					hit_part = 1;
// 				}
// 			}
// 		}

// 		// ------ TAMPA INFERIOR ------
// 		t_point cap_bottom = vecsoma(rt->cylinder[i].coordinates,
// 			vecprodesc(axis, -rt->cylinder[i].height / 2));
// 		double t_bot = -1;
// 		if (intersect_cap(ro, dir, cap_bottom, vecprodesc(axis, -1),
// 			rt->cylinder[i].radius, &t_bot))
// 		{
// 			if (t_bot > 0.001 && t_bot < *closest_t)
// 			{
// 				t_point hit = vecsoma(ro, vecprodesc(dir, t_bot));
// 				double proj = escprod(vecdif(hit, rt->cylinder[i].coordinates), axis);
// 				if (fabs(proj) <= rt->cylinder[i].height / 2)
// 				{
// 					*closest_t = t_bot;
// 					rt->closest = t_bot;
// 					closest_i = i;
// 					color = rt->cylinder[i].color;
// 					hit_part = 2;
// 				}
// 			}
// 		}
// 		i++;
// 	}

// 	// Se acertou alguma parte do cilindro
// 	if (closest_i != -1 && *closest_t > 0)
// 	{
// 		t_point ro = rt->camera.coordinates;
// 		t_point hit = vecsoma(ro, vecprodesc(dir, *closest_t));
// 		t_point normal;

// 		if (hit_part == 0)
// 			normal = get_cylinder_normal(&rt->cylinder[closest_i], hit);
// 		else
// 			normal = vecnorm(vecdif(hit, rt->cylinder[closest_i].coordinates));

// 		color = add_light(color, rt, hit, normal, hit_part);
// 	}
// 	return (color);
// }

// ultima função do cylinder_loop
t_color	cylinder_loop(t_minirt *rt, t_point dir, double *closest_t, t_color color)
{
	double	t = -1;
	int		i;
	int		closest_i = -1;
	int		aux = 0;
	int		entrou = 0;
	double t_global = 1e9;

	i = 0;
	while (i < rt->cy)
	{
		if (intersect_cylinder(&rt->cylinder[i], dir, rt, &t))
		{
			// if (t > 0.001 && t < rt->closest && (t < closest_t[0]))// || (entrou == 0))
			// if (t > 0.001 && t < rt->closest)// && (t < closest_t[0]))
			if (t > 0.001 && t < rt->closest&& t < t_global)
			{
				t_global = t;
				// entrou = 1;
				closest_t[0] = t;
				closest_i = i;
				color = rt->cylinder[i].color;
			}
		}
		// Parâmetros comuns
		t_point axis = vecnorm(rt->cylinder[i].a_vector);
		t_point ro = rt->camera.coordinates;
		// Tampa superior
		t_point cap_top = vecsoma(rt->cylinder[i].coordinates,
			vecprodesc(axis, rt->cylinder[i].height / 2));
		double t_cap_top;
		if (intersect_cap(ro, dir, cap_top, axis, rt->cylinder[i].radius, &t_cap_top))
		{
			if (t_cap_top > 0.001 && t_cap_top < rt->closest && t_cap_top < closest_t[1] && t < t_global)
			{
				t_global = t;
				closest_t[1] = t_cap_top;
				closest_i = i;
				color = rt->cylinder[i].color;
				aux = 1;
			}
		}
		// Tampa inferior
		t_point cap_bottom = vecsoma(rt->cylinder[i].coordinates,
			vecprodesc(axis, -rt->cylinder[i].height / 2));
		double t_cap_bottom;
		if (intersect_cap(ro, dir, cap_bottom, vecprodesc(axis, -1),
				rt->cylinder[i].radius, &t_cap_bottom))
		{
			if (t_cap_bottom > 0.001 && t_cap_bottom < rt->closest && t_cap_bottom < closest_t[1] && t < t_global)
			{
				t_global = t;
				closest_t[1] = t_cap_bottom;
				closest_i = i;
				color = rt->cylinder[i].color;
				aux = 1;
			}
		}
		entrou = 0;
		i++;
	}
	(void)entrou;
	// if (closest_i != -1 && *closest_t > 0)
	// if (rt->closest > closest_t[0] && closest_t[0] > 0)
	if (rt->closest > t_global && t_global > 0)
	{
		t_point ro = rt->camera.coordinates;
		t_point dir_scaled = vecprodesc(dir, t_global);
		t_point hit_point = vecsoma(ro, dir_scaled);
		t_point normal = get_cylinder_normal(&rt->cylinder[closest_i], hit_point);
		color = add_light(color, rt, hit_point, normal, aux);
	}
	return (color);
}


// t_color	cylinder_loop(t_minirt *rt, t_point dir, double *closest_t, t_color color)
// {
// 	double	t;
// 	int		i;
// 	int		closest_i = -1;
// 	int		final_aux = 0;

// 	i = 0;
// 	while (i < rt->cy)
// 	{
// 		t_point axis = vecnorm(rt->cylinder[i].a_vector);
// 		t_point ro = rt->camera.coordinates;

// 		// Lateral do cilindro
// 		if (intersect_cylinder(&rt->cylinder[i], dir, rt, &t))
// 		{
// 			if (t > 0.001 && t < *closest_t)
// 			{
// 				*closest_t = t;
// 				closest_i = i;
// 				color = rt->cylinder[i].color;
// 				final_aux = 0; // lateral
// 			}
// 		}

// 		// Tampa superior
// 		t_point cap_top = vecsoma(rt->cylinder[i].coordinates,
// 			vecprodesc(axis, rt->cylinder[i].height / 2));
// 		double t_cap_top;
// 		if (intersect_cap(ro, dir, cap_top, axis, rt->cylinder[i].radius, &t_cap_top))
// 		{
// 			if (t_cap_top > 0.001 && t_cap_top < *closest_t)
// 			{
// 				*closest_t = t_cap_top;
// 				closest_i = i;
// 				color = rt->cylinder[i].color;
// 				final_aux = 1; // tampa
// 			}
// 		}

// 		// Tampa inferior
// 		t_point cap_bottom = vecsoma(rt->cylinder[i].coordinates,
// 			vecprodesc(axis, -rt->cylinder[i].height / 2));
// 		double t_cap_bottom;
// 		if (intersect_cap(ro, dir, cap_bottom, vecprodesc(axis, -1),
// 				rt->cylinder[i].radius, &t_cap_bottom))
// 		{
// 			if (t_cap_bottom > 0.001 && t_cap_bottom < *closest_t)
// 			{
// 				*closest_t = t_cap_bottom;
// 				closest_i = i;
// 				color = rt->cylinder[i].color;
// 				final_aux = 1; // tampa
// 			}
// 		}
// 		i++;
// 	}
// 	if (closest_i != -1)
// 	{
// 		t_point ro = rt->camera.coordinates;
// 		t_point dir_scaled = vecprodesc(dir, *closest_t);
// 		t_point hit_point = vecsoma(ro, dir_scaled);
// 		t_point normal = get_cylinder_normal2(&rt->cylinder[closest_i], hit_point, final_aux);
// 		color = add_light(color, rt, hit_point, normal, final_aux, 1);
// 	}
// 	return (color);
// }


// t_color	cylinder_loop(t_minirt *rt, t_point dir, double *closest_t, t_color color)
// {
// 	double	t;
// 	int		i;
// 	int		closest_i = -1;
// 	int		aux; // indica se foi tampa

// 	i = 0;
// 	while (i < rt->cy)
// 	{
// 		aux = 0;
// 		if (intersect_cylinder(&rt->cylinder[i], dir, rt, &t))
// 		{
// 			if (t > 0.001 && t < *closest_t)
// 			{
// 				*closest_t = t;
// 				closest_i = i;
// 				color = rt->cylinder[i].color;
// 			}
// 		}
// 		i++;
// 	}
// 	if (closest_i != -1)
// 	{
// 		t_point ro = rt->camera.coordinates;
// 		t_point dir_scaled = vecprodesc(dir, *closest_t);
// 		t_point hit_point = vecsoma(ro, dir_scaled);

// 		t_point normal;
// 		if (aux == 1)
// 		{
// 			// Verifica se a interseção foi com a tampa superior ou inferior
// 			t_point top = vecsoma(rt->cylinder[closest_i].coordinates,
// 								vecprodesc(rt->cylinder[closest_i].a_vector,
// 										   rt->cylinder[closest_i].height / 2));
// 			double d_top = vecmod(vecdif(hit_point, top));

// 			if (d_top < rt->cylinder[closest_i].radius)
// 				normal = vecnorm(rt->cylinder[closest_i].a_vector); // tampa superior
// 			else
// 				normal = vecnorm(vecprodesc(rt->cylinder[closest_i].a_vector, -1)); // tampa inferior
// 		}
// 		else
// 		{
// 			normal = get_cylinder_normal(&rt->cylinder[closest_i], hit_point);
// 		}
// 		color = add_light(color, rt, hit_point, normal, 1);
// 	}
// 	return (color);
// }
