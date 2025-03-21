/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightapp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:43:14 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/21 19:43:15 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color add_alight(t_color color, t_minirt *rt)
{
    t_color new;

    new.r = (color.r * rt->alight.color.r / 255.0) * rt->alight.ratio;
    new.g = (color.g * rt->alight.color.g / 255.0) * rt->alight.ratio;
    new.b = (color.b * rt->alight.color.b / 255.0) * rt->alight.ratio;
    return (new);
}