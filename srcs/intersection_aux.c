/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:09:39 by jorcarva          #+#    #+#             */
/*   Updated: 2025/06/04 17:11:12 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static double	delta_aux(t_point d_perp, t_point oc_perp, t_cylinder *cy,
		double *b)
{
	double	a;
	double	c;

	a = escprod(d_perp, d_perp);
	*b = 2 * escprod(d_perp, oc_perp);
	c = escprod(oc_perp, oc_perp) - cy->radius * cy->radius;
	return (*b * *b - 4 * a * c);
}

static double	ft_delta(t_mini_intersect *t_inter, double *t0, double *t1)
{
	double	b;
	double	delta;
	int		tmp;

	delta = delta_aux(t_inter->d_perp, t_inter->oc_perp, t_inter->cy, &b);
	if (delta >= 0)
	{
		*t0 = (-b - sqrt(delta)) / (2 * escprod(t_inter->d_perp,
					t_inter->d_perp));
		*t1 = (-b + sqrt(delta)) / (2 * escprod(t_inter->d_perp,
					t_inter->d_perp));
		if (t0 > t1)
		{
			tmp = *t0;
			*t0 = *t1;
			*t1 = tmp;
		}
		return (delta);
	}
	return (0);
}

static void	verify_border(t_mini_intersect *t_inter, double *t, int flag)
{
	double	proj_len;

	t_inter->hit_point = vecsoma(t_inter->ro, vecprodesc(t_inter->dir, *t));
	proj_len = escprod(vecdif(t_inter->hit_point, t_inter->cy->coordinates),
			t_inter->axis);
	if (proj_len >= -t_inter->cy->height / 2 && proj_len <= t_inter->cy->height
		/ 2 && *t > 0.001)
	{
		if (flag == 0)
		{
			t_inter->closest_t = *t;
			t_inter->hit = 1;
		}
		else if ((!t_inter->hit || *t < t_inter->closest_t) && flag == 1)
		{
			t_inter->closest_t = *t;
			t_inter->hit = 1;
		}
	}
}

void	intersection_aux(t_mini_intersect *t_inter, double *t0, double *t1)
{
	double	delta;

	delta = ft_delta(t_inter, t0, t1);
	if (delta >= 0)
	{
		verify_border(t_inter, t0, 0);
		verify_border(t_inter, t1, 1);
	}
}
