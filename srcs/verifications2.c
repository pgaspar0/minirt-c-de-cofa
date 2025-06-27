/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:54:32 by jorcarva          #+#    #+#             */
/*   Updated: 2025/06/26 12:45:45 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	check_camera(t_camera *camera)
{
	return ((camera->o_vector.x >= -1.0 && camera->o_vector.x <= 1.0)
		&& (camera->o_vector.y >= -1.0 && camera->o_vector.y <= 1.0)
		&& (camera->o_vector.z >= -1.0 && camera->o_vector.z <= 1.0)
		&& (camera->fov >= 0 && camera->fov <= 180));
}

int	check_light(t_light *light)
{
	return ((light->ratio >= 0.0 && light->ratio <= 1.0)
		&& check_colors(light->color));
}

int	check_plane(t_plane *plane)
{
	return ((plane->n_vector.x >= -1.0 && plane->n_vector.x <= 1.0)
		&& (plane->n_vector.y >= -1.0 && plane->n_vector.y <= 1.0)
		&& (plane->n_vector.z >= -1.0 && plane->n_vector.z <= 1.0)
		&& (check_colors(plane->color)));
}

int	check_cylinder(t_cylinder *cylinder)
{
	return ((cylinder->a_vector.x >= -1.0 && cylinder->a_vector.x <= 1.0)
		&& (cylinder->a_vector.y >= -1.0 && cylinder->a_vector.y <= 1.0)
		&& (cylinder->a_vector.z >= -1.0 && cylinder->a_vector.z <= 1.0)
		&& (check_colors(cylinder->color)));
}

int	check_sphere(t_sphere *sphere)
{
	if (!check_colors(sphere->color))
		return (0);
	return (1);
}
