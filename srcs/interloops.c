/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interloops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:39:50 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/24 19:39:52 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	sphere_loop(t_minirt *rt, t_point direction, double *t, t_color color)
{
	int	i;
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
				bateu = vecsoma(rt->camera.coordinates, vecprodesc(direction, rt->closest));
				normal = vecnorm(vecdif(bateu, rt->sphere[i].coordinates));
				color = add_light(color, rt, bateu, normal);
			}
		}
		i++;
	}
	return (color);
}

t_color	plane_loop(t_minirt *rt, t_point direction, double *t, t_color color)
{
	int	i;
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
				bateu = vecsoma(rt->camera.coordinates, vecprodesc(direction, rt->closest));
				normal = rt->plane[i].n_vector;
				color = add_light(color, rt, bateu, normal);
			}
		}
		i++;
	}
	return (color);
}