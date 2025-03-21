/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:30:20 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/21 11:30:22 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_point	get_pixel(int i, int j, t_minirt *rt)
{
	t_point	pixel;
	t_point right_part;
	t_point	up_part;

	right_part = vecprodesc(rt->right, i * rt->psizex);
	up_part = vecprodesc(rt->up, j * rt->psizey);
	pixel = vecsoma(rt->p_first, vecdif(right_part, up_part));
	return (pixel);
}

void	put_scene(t_minirt *rt)
{
	int		x;
	int		y;
	t_color	color;
	t_point	direction;
	t_point	pixel;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel = get_pixel(x, y, rt);
			direction = vecdif(pixel, rt->camera.coordinates);
			direction = vecnorm(direction);
			color = intersect_scene(direction, rt);
			color = add_alight(color, rt);
			put_pixel(rt, x, y, color_to_int(color));
			x++;
		}
		y++;
	}
}