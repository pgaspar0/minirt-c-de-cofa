/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:46:31 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/04 20:01:25 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	rotx(t_minirt *rt, double val)
{
	if (rt->mini.type == 1)
		rt->plane[rt->mini.index].n_vector = rotate_x(rt->plane[rt->mini.index].n_vector,
				val);
	else if (rt->mini.type == 2)
		rt->cylinder[rt->mini.index].a_vector = rotate_x(rt->cylinder[rt->mini.index].a_vector,
				val);
	else if (rt->mini.type == 3)
		rt->light.coordinates = rotate_x(rt->light.coordinates, val);
	else if (rt->mini.type == 4)
		rt->camera.o_vector = rotate_x(rt->camera.o_vector, val);
}

void	roty(t_minirt *rt, double val)
{
	if (rt->mini.type == 1)
		rt->plane[rt->mini.index].n_vector = rotate_y(rt->plane[rt->mini.index].n_vector,
				val);
	else if (rt->mini.type == 2)
		rt->cylinder[rt->mini.index].a_vector = rotate_y(rt->cylinder[rt->mini.index].a_vector,
				val);
	else if (rt->mini.type == 3)
		rt->light.coordinates = rotate_y(rt->light.coordinates, val);
	else if (rt->mini.type == 4)
		rt->camera.o_vector = rotate_y(rt->camera.o_vector, val);
}

void	rotz(t_minirt *rt, double val)
{
	if (rt->mini.type == 1)
		rt->plane[rt->mini.index].n_vector = rotate_z(rt->plane[rt->mini.index].n_vector,
				val);
	else if (rt->mini.type == 2)
		rt->cylinder[rt->mini.index].a_vector = rotate_z(rt->cylinder[rt->mini.index].a_vector,
				val);
	else if (rt->mini.type == 3)
		rt->light.coordinates = rotate_z(rt->light.coordinates, val);
	else if (rt->mini.type == 4)
		rt->camera.o_vector = rotate_z(rt->camera.o_vector, val);
}
