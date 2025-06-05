/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_aux2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:09:40 by jorcarva          #+#    #+#             */
/*   Updated: 2025/06/05 16:33:39 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ver_int(t_mini_intersect *inter, t_point cap_bottom)
{
	double	t_cap_bottom;

	if (intersect_cap2(inter, cap_bottom, inter->cy->radius, &t_cap_bottom))
	{
		if (t_cap_bottom > 0.001 && (!inter->hit
				|| t_cap_bottom < inter->closest_t))
		{
			inter->closest_t = t_cap_bottom;
			inter->hit_point = vecsoma(inter->ro, vecprodesc(inter->dir,
						t_cap_bottom));
			inter->hit = 1;
		}
	}
}

void	init_t_inter(t_mini_intersect *t_inter, t_cylinder *cy, t_point dir,
		t_minirt *rt)
{
	t_inter->ro = rt->camera.coordinates;
	t_inter->cy = cy;
	t_inter->rt = rt;
	t_inter->dir = dir;
	t_inter->axis = vecnorm(cy->a_vector);
	t_inter->d_perp = vecdif(dir, vecprodesc(t_inter->axis, escprod(dir,
					t_inter->axis)));
	t_inter->oc_perp = vecdif(vecdif(t_inter->ro, cy->coordinates),
			vecprodesc(t_inter->axis, escprod(vecdif(t_inter->ro,
						cy->coordinates), t_inter->axis)));
	t_inter->closest_t = -1;
	t_inter->hit = 0;
	t_inter->normal = vecnorm(t_inter->cy->a_vector);
}

void	caps_aux(t_mini_intersect *t_inter, double *t_cap_top,
		t_point *cap_bottom)
{
	t_point	cap_top;

	cap_top = vecsoma(t_inter->cy->coordinates, vecprodesc(t_inter->axis,
				t_inter->cy->height / 2));
	*cap_bottom = vecsoma(t_inter->cy->coordinates, vecprodesc(t_inter->axis,
				-t_inter->cy->height / 2));
	t_inter->normal = vecnorm(t_inter->cy->a_vector);
	if (intersect_cap2(t_inter, cap_top, t_inter->cy->radius, t_cap_top))
	{
		if (*t_cap_top > 0.001 && (!t_inter->hit
				|| *t_cap_top < t_inter->closest_t))
		{
			t_inter->closest_t = *t_cap_top;
			t_inter->hit_point = vecsoma(t_inter->ro, vecprodesc(t_inter->dir,
						*t_cap_top));
			t_inter->hit = 1;
		}
	}
}

int	intersect_cap(t_point ro, t_cylinder_state *s, t_point center, double *t)
{
	double	denom;
	t_point	oc;
	double	t_hit;
	t_point	hit;
	t_point	dist;

	denom = escprod(s->dir, s->normal);
	if (fabs(denom) < 1e-6)
		return (0);
	oc = vecdif(center, ro);
	t_hit = escprod(oc, s->normal) / denom;
	if (t_hit < 0.001)
		return (0);
	hit = vecsoma(ro, vecprodesc(s->dir, t_hit));
	dist = vecdif(hit, center);
	if (vecmod(dist) > s->radius)
		return (0);
	*t = t_hit;
	return (1);
}
