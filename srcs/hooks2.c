/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:32:55 by pgaspar           #+#    #+#             */
/*   Updated: 2025/05/24 12:32:56 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void    k_check(t_minirt *rt, int *i)
{
    transz(rt, -0.5);
    if (rt->mini.type != -1)
        *i = 0;
}

void    w_check(t_minirt *rt, int *i)
{
    roty(rt, 0.1);
    if (rt->mini.type != -1)
        *i = 0;
}

void    s_check(t_minirt *rt, int *i)
{
    roty(rt, -0.1);
    if (rt->mini.type != -1)
        *i = 0;
}

void    a_check(t_minirt *rt, int *i)
{
    rotx(rt, -0.1);
    if (rt->mini.type != -1)
        *i = 0;
}

void    d_check(t_minirt *rt, int *i)
{
    rotx(rt, 0.1);
    if (rt->mini.type != -1)
        *i = 0;
}
