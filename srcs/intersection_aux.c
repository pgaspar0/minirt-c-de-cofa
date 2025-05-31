/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:09:39 by jorcarva          #+#    #+#             */
/*   Updated: 2025/05/31 13:24:54 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*

typedef struct s_intersection
{
	t_point	ro;
	t_point	axis;
	t_point	dir;
	t_point	hit_point;
	double	closest_t;
	int		hit;
}			t_mini_intersect;

*/

/*

if (delta >= 0)
	{
		t0 = (-b - sqrt(delta)) / (2 * escprod(d_perp, d_perp));
		t1 = (-b + sqrt(delta)) / (2 * escprod(d_perp, d_perp));
		// float epha[2];
		// *epha = get_delta(cy, d_perp, oc_perp, dir);
		// printf("Já aqui dentro: %f - %f, Agora os de fora: %f - %f\n", t0, t1, epha[0], epha[1]);
		if (t0 > t1) { tmp = t0; t0 = t1; t1 = tmp; }

		hit_point = vecsoma(ro, vecprodesc(d, t0));
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

*/

void	delta()
{
	double	t0;
	double	t1;

	t0 = (-b - sqrt(delta)) / (2 * escprod(d_perp, d_perp));
	t1 = (-b + sqrt(delta)) / (2 * escprod(d_perp, d_perp));
}

// float	*get_delta(t_cylinder *cy, t_point d_perp, t_point oc_perp, t_point d)
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	delta;
// 	double	t[2];

// 	a = escprod(vecdif(d, d_proj), vecdif(d, d_proj));
// 	b = 2 * escprod(vecdif(d, d_proj), vecdif(oc, oc_proj));
// 	c = escprod(vecdif(oc, oc_proj), vecdif(oc, oc_proj)) - cy->radius
// 		* cy->radius;
// 	delta = b * b - 4 * a * c;
// 	// t[0] = -1;
// 	// t[1] = -1;
// 	t[0] = (-b - sqrt(delta)) / (2 * escprod(vecdif(d, d_proj), vecdif(d,
// 					d_proj)));
// 	t[1] = (-b + sqrt(delta)) / (2 * escprod(vecdif(d, d_proj), vecdif(d,
// 					d_proj)));
// 	return (t);
// }

int	intersect_cylinder(t_cylinder *cy, t_point dir, t_minirt *rt, double *t)
{
}
