/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightapp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:43:14 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/05 17:54:48 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// t_point bateu, t_point normal,

t_color	add_light(t_color color, t_minirt *rt, t_vecs *vec, int i)
{
	t_color	final;
	t_point	light_dir;

	(void)i;
	final = add_alight(color, rt);
	light_dir = vecnorm(vecdif(rt->light.coordinates, vec->vec1));
	if (in_shadow(rt, vec->vec1, light_dir))
		return (colormult(color, rt->alight.ratio));
	final = add_dlight(rt, final, color, vec);
	return (final);
}

t_color	add_alight(t_color color, t_minirt *rt)
{
	t_color	new;

	new.r = (color.r * rt->alight.color.r / 255.0) * rt->alight.ratio;
	new.g = (color.g * rt->alight.color.g / 255.0) * rt->alight.ratio;
	new.b = (color.b * rt->alight.color.b / 255.0) * rt->alight.ratio;
	return (new);
}

t_color	add_dlight(t_minirt *rt, t_color color, t_color old_color, t_vecs *vec)
{
	t_point	lightdir;
	t_color	dif_color;
	t_color	last_color;
	double	esc;

	lightdir = vecnorm(vecdif(rt->light.coordinates, vec->vec1));
	esc = escprod(vec->vec2, lightdir);
	if (esc < 0)
		return (color);
	dif_color.r = (old_color.r * rt->light.color.r / 255.0) * rt->light.ratio
		* esc;
	dif_color.g = (old_color.g * rt->light.color.g / 255.0) * rt->light.ratio
		* esc;
	dif_color.b = (old_color.b * rt->light.color.b / 255.0) * rt->light.ratio
		* esc;
	last_color.r = fmin(255, color.r + dif_color.r);
	last_color.g = fmin(255, color.g + dif_color.g);
	last_color.b = fmin(255, color.b + dif_color.b);
	return (last_color);
}

static double	veclen(t_point v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

int	in_shadow(t_minirt *rt, t_point point, t_point light_dir)
{
	double		t[2];
	t_minirt	*rt_aux;
	t_vecs		vec;
	int			i;

	i = 0;
	rt_aux = (t_minirt *)malloc(sizeof(t_minirt));
	vec.vec1 = vecsoma(point, vecprodesc(light_dir, 0.001));
	vec.light_len = veclen(vecdif(rt->light.coordinates, point));
	vec.vec2 = light_dir;
	if (in_shadow_sp(i, rt, t, &vec) == 1)
		return (1);
	while (i < rt->cy)
	{
		rt_aux->camera.coordinates = vec.vec1;
		if (intersect_cylinder(&rt->cylinder[i], vec.vec2, rt_aux, t))
			if (t[0] > 0.001 && t[0] < vec.light_len)
				return (1);
		i++;
	}
	return (0);
}
