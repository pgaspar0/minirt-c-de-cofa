/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:53:51 by jorcarva          #+#    #+#             */
/*   Updated: 2025/06/26 08:51:41 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	check_colors(t_color color)
{
	return ((color.r >= 0 && color.r <= 255) && (color.g >= 0 && color.g <= 255)
		&& (color.b >= 0 && color.b <= 255));
}

int	check_alight(t_alight *ambiente)
{
	return ((ambiente->ratio >= 0.0 && ambiente->ratio <= 1.0)
		&& check_colors(ambiente->color));
}

static int	check_scene2(t_minirt *scene)
{
	int	i;

	i = 0;
	while (i < scene->pl)
	{
		if (!check_plane(&scene->plane[i]))
		{
			printf("Error\nplane %d is invalid\n", i + 1);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < scene->cy)
	{
		if (!check_cylinder(&scene->cylinder[i]))
		{
			printf("Error\ncylinder %d is invalid\n", i + 1);
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
		printf("Error\nInvalid scene values\n");
		return (1);
	}
	while (i < scene->sp)
	{
		if (!check_sphere(&scene->sphere[i]))
		{
			printf("Error\nSphere %d is invalid\n", i + 1);
			return (1);
		}
		i++;
	}
	if (check_scene2(scene))
		return (1);
	return (0);
}
