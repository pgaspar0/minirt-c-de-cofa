/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightapp_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:40:06 by jorcarva          #+#    #+#             */
/*   Updated: 2025/06/10 19:55:16 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	in_shadow_sp(int i, t_minirt *rt, double t[2], t_vecs *vec)
{
	t_minirt	rt_aux;

	i = 0;
	while (i < rt->sp)
	{
		rt_aux.camera.coordinates = vec->vec1;
		if (intersect_sphere(&rt->sphere[i], vec->vec2, &rt_aux, t))
			if (t[0] > 0.001 && t[0] < vec->light_len)
				return (1);
		i++;
	}
	i = 0;
	while (i < rt->pl)
	{
		rt_aux.camera.coordinates = vec->vec1;
		if (intersect_plane(&rt_aux, &rt->plane[i], vec->vec2, t))
			if (t[0] > 0.001 && t[0] < vec->light_len)
				return (1);
		i++;
	}
	return (0);
}
