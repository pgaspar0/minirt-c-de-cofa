/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shorteners1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:46:04 by pgaspar           #+#    #+#             */
/*   Updated: 2025/05/24 12:46:08 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void    clean_all(t_minirt *rt)
{
    if (rt->img)
        mlx_destroy_image(rt->con, rt->img);
    if (rt->window)
        mlx_destroy_window(rt->con, rt->window);
    if (rt->con)
    {
        mlx_destroy_display(rt->con);
        free(rt->con);
    }
}

int close_des(t_minirt *rt)
{
	clean_all(rt);
	exit(EXIT_SUCCESS);
	return (0);
}
