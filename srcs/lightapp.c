/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightapp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:43:14 by pgaspar           #+#    #+#             */
/*   Updated: 2025/04/10 09:43:58 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	add_light(t_color color, t_minirt *rt, t_point bateu, t_point normal)
{
	t_color	final;
	t_point	light_dir;

	final = add_alight(color, rt);
	light_dir = vecnorm(vecdif(rt->light.coordinates, bateu));
	if (in_shadow(rt, bateu, light_dir))
		return (colormult(color, rt->alight.ratio)); // ← corrigido aqui
	final = add_dlight(rt, final, color, bateu, normal);
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

t_color	add_dlight(t_minirt *rt, t_color color, t_color old_color,
		t_point bateu, t_point normal)
{
	t_point	lightdir;
	t_color	dif_color;
	t_color	last_color;
	double	esc;

	lightdir = vecnorm(vecdif(rt->light.coordinates, bateu));
	esc = escprod(normal, lightdir);
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

int	in_shadow(t_minirt *rt, t_point point, t_point light_dir)
{
	double		t[2];
	t_point		shadow_origin;
	int			i;

	shadow_origin = vecsoma(point, vecprodesc(light_dir, 0.001));
	i = 0;
	while (i < rt->sp)
	{
		if (intersect_sphere(&rt->sphere[i], light_dir, &(t_minirt){
			.camera.coordinates = shadow_origin }, t))
			if (t[0] > 0.001 && t[0] < 1.0)
				return (1);
		i++;
	}

	i = 0;
	while (i < rt->pl)
	{
		if (intersect_plane(&(t_minirt){
			.camera.coordinates = shadow_origin }, &rt->plane[i], light_dir, t))
			if (t[0] > 0.001 && t[0] < 1.0)
				return (1);
		i++;
	}
	i = 0;
	while (i < rt->cy)
	{
		if (intersect_cylinder(&rt->cylinder[i], light_dir, &(t_minirt){
			.camera.coordinates = shadow_origin }, t))
			if (t[0] > 0.001 && t[0] < 1.0)
				return (1);
		i++;
	}
	return (0);
}
