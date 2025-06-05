/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hfuncs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:26:43 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/05 16:39:08 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

t_color	colormult(t_color color, double mult)
{
	t_color	new;

	new.r = color.r * mult;
	new.g = color.g * mult;
	new.b = color.b * mult;
	return (new);
}
