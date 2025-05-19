/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:01:13 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/16 22:32:19 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	init_camera(t_minirt *rt)
{
	t_point updef;

	updef = (t_point){0, 1, 0};
	if (fabs(rt->camera.o_vector.y) == 1)
    	updef = (t_point){1, 0, 0};
	rt->right = vecprod(updef, rt->camera.o_vector);
	rt->up = vecprod(rt->camera.o_vector, rt->right);
    rt->viewport_height = 2 * tan((rt->camera.fov * (M_PI/180)) / 2);
    rt->viewport_width = rt->viewport_height * (((double)WIDTH/HEIGHT));
	rt->p_centro = vecsoma(rt->camera.coordinates, rt->camera.o_vector);
	rt->p_first = vecdif(rt->p_centro, vecprodesc(rt->right, rt->viewport_width / 2));
	rt->p_first = vecsoma(rt->p_first, vecprodesc(rt->up, rt->viewport_height / 2));
	rt->psizex = rt->viewport_width / WIDTH;
	rt->psizey = rt->viewport_height / HEIGHT;
	rt->mini.type = -1;
	rt->mini.index = -1;
	rt->in = -1;
}
