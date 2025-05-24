/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:46:36 by pgaspar           #+#    #+#             */
/*   Updated: 2025/05/24 12:46:37 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void    transy(t_minirt *rt, double val)
{
    if (rt->mini.type == 0)
        rt->sphere[rt->mini.index].coordinates.y += val;
    else if (rt->mini.type == 1)
        rt->plane[rt->mini.index].coordinates.y += val;
    else if (rt->mini.type == 2)
        rt->cylinder[rt->mini.index].coordinates.y += val;
    else if (rt->mini.type == 3)
        rt->light.coordinates.y += val;
    else if (rt->mini.type == 4)
        rt->camera.coordinates.y += val;
}

void    transx(t_minirt *rt, double val)
{
    if (rt->mini.type == 0)
        rt->sphere[rt->mini.index].coordinates.x += val;
    else if (rt->mini.type == 1)
        rt->plane[rt->mini.index].coordinates.x += val;
    else if (rt->mini.type == 2)
        rt->cylinder[rt->mini.index].coordinates.x += val;
    else if (rt->mini.type == 3)
        rt->light.coordinates.x += val;
    else if (rt->mini.type == 4)
        rt->camera.coordinates.x += val;
}
void    transz(t_minirt *rt, double val)
{
    if (rt->mini.type == 0)
        rt->sphere[rt->mini.index].coordinates.z += val;
    else if (rt->mini.type == 1)
        rt->plane[rt->mini.index].coordinates.z += val;
    else if (rt->mini.type == 2)
        rt->cylinder[rt->mini.index].coordinates.z += val;
    else if (rt->mini.type == 3)
        rt->light.coordinates.z += val;
    else if (rt->mini.type == 4)
        rt->camera.coordinates.z += val;
}
