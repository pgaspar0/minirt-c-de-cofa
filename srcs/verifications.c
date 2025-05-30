/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:53:51 by jorcarva          #+#    #+#             */
/*   Updated: 2025/03/28 12:16:06 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// check colors, RGB (0 - 255)
int	check_colors(t_color color)
{
	return ((color.r >= 0 && color.r <= 255) && (color.g >= 0 && color.g <= 255)
		&& (color.b >= 0 && color.b <= 255));
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

int	check_sphere(t_sphere *sphere)
{
	if (!check_colors(sphere->color))
		return (0);
	return (1);
}

static int	check_scene2(t_minirt *scene)
{
	int	i;

	i = 0;
	while (i < scene->pl)
	{
		if (!check_plane(&scene->plane[i]))
		{
			printf("Error: plane %d is invalid\n", i + 1);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < scene->cy)
	{
		if (!check_cylinder(&scene->cylinder[i]))
		{
			printf("Error: cylinder %d is invalid\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_scene(t_minirt *scene)
{
	int	i;

	i = 0;
	if (!(check_alight(&scene->alight) && check_camera(&scene->camera)
			&& check_light(&scene->light)))
	{
		printf("Error: Invalid scene values\n");
		return (1);
	}
	while (i < scene->sp)
	{
		if (!check_sphere(&scene->sphere[i]))
		{
			printf("Error: Sphere %d is invalid\n", i + 1);
			return (1);
		}
		i++;
	}
	if (check_scene2(scene))
		return (1);
	return (0);
}
