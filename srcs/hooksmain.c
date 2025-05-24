/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooksmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:36:59 by pgaspar           #+#    #+#             */
/*   Updated: 2025/05/24 12:37:00 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void    key_pressed(t_minirt *rt, int keycode, int *i)
{
    if (keycode == XK_Up)
        up_check(rt, i);
    if (keycode == XK_Down)
        down_check(rt, i);
    if (keycode == XK_Right)
        right_check(rt, i);
    if (keycode == XK_Left)
        left_check(rt, i);
    if (keycode == XK_i || keycode == XK_I)
        i_check(rt, i);
    if (keycode == XK_k || keycode == XK_K)
        k_check(rt, i);
    if (keycode == XK_w || keycode == XK_W)
        w_check(rt, i);
    if (keycode == XK_s || keycode == XK_S)
        s_check(rt, i);
    if (keycode == XK_a || keycode == XK_A)
        a_check(rt, i);
    if (keycode == XK_d || keycode == XK_D)
        d_check(rt, i);
    if (keycode == XK_q || keycode == XK_Q)
        q_check(rt, i);
    if (keycode == XK_e || keycode == XK_E)
        e_check(rt, i);
}

int keys(int keycode, void *param)
{
    t_minirt    *rt;
    int         i;

    i = -1;
    rt = (t_minirt *) param;
    if (keycode == XK_Escape)
    {
        clean_all(rt);
        exit(EXIT_SUCCESS);
    }
    key_pressed(rt, keycode, &i);
    if (i != -1)
    {
        put_scene(rt);
        mlx_put_image_to_window(rt->con, rt->window, rt->img, 0, 0);
    }
    return (0);
}
