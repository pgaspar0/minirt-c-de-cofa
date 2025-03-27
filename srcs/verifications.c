/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:53:51 by jorcarva          #+#    #+#             */
/*   Updated: 2025/03/27 16:28:47 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// check colors, RGB (0 - 255)
int	check_colors(t_color color)
{
	return ((color.r >= 0 && color.r <= 255) && (color.g >= 0
			&& color.g <= 255) && (color.b >= 0 && color.b <= 255));
}

// check ambient's light ratio range (0.0 -> 1.0), and colors
int	check_alight(t_alight *ambiente)
{
	return ((ambiente->ratio >= 0.0 && ambiente->ratio <= 1.0)
		&& check_colors(ambiente->color));
}

// check camera 3d normalized orientation (-1.0;1.0) and FOV (0-180)
int	check_camera(t_camera *camera)
{
	return ((camera->o_vector.x >= -1.0 && camera->o_vector.x <= 1.0)
		&& (camera->o_vector.y >= -1.0 && camera->o_vector.y <= 1.0)
		&& (camera->o_vector.z >= -1.0 && camera->o_vector.z <= 1.0)
		&& (camera->fov >= 0 && camera->fov <= 180));
}

// check light brightness ratio (0.0 - 1.0) and colors
int	check_light(t_light *light)
{
	return ((light->ratio >= 0.0 && light->ratio <= 1.0)
		&& check_colors(light->color));
}

// check sphere colors
int	check_sphere(t_sphere *sphere)
{
	return (check_colors(sphere->color));
}

// check plane 3d normalized vector (-1.0;1.0) and colors
int	check_plane(t_plane *plane)
{
	return ((plane->n_vector.x >= -1.0 && plane->n_vector.x <= 1.0)
		&& (plane->n_vector.y >= -1.0 && plane->n_vector.y <= 1.0)
		&& (plane->n_vector.z >= -1.0 && plane->n_vector.z <= 1.0)
		&& (check_colors(plane->color)));
}

// check cylinder 3d normalized vector (-1.0;1.0) and colors
int	check_cylinder(t_cylinder *cylinder)
{
	return ((cylinder->a_vector.x >= -1.0 && cylinder->a_vector.x <= 1.0)
		&& (cylinder->a_vector.y >= -1.0 && cylinder->a_vector.y <= 1.0)
		&& (cylinder->a_vector.z >= -1.0 && cylinder->a_vector.z <= 1.0)
		&& (check_colors(cylinder->color)));
}

// função para efetuar todas as verificações nos campos do mapa
int	check_scene(t_minirt *scene)
{
	int i;
	if (!(check_alight(&scene->alight) && check_camera(&scene->camera)
			&& check_light(&scene->light)))
	{
		printf("Error: invalid scenes values");
		return (1);
	}
	i = 0;
	// é suposto fazer aqui uma estrutura para verificar cada esfera and so on
	// while (print_sphere_count(scene) != i)
	// {
	// 	if ()

	// 	i++;
	// }
	// if ()
	return (0);
}
