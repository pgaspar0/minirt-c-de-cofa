/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:33:00 by pgaspar           #+#    #+#             */
/*   Updated: 2025/05/24 12:33:02 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void    q_check(t_minirt *rt, int *i)
{
    rotz(rt, -0.1);
    if (rt->mini.type != -1)
        *i = 0;
    if (rt->mini.type == 4)
        init_camera(rt);
}
void    e_check(t_minirt *rt, int *i)
{
    rotz(rt, 0.1);
    if (rt->mini.type != -1)
        *i = 0;
    if (rt->mini.type == 4)
        init_camera(rt);
}
