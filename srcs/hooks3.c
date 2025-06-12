/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:33:00 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/05 16:35:23 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	q_check(t_minirt *rt, int *i)
{
	rotz(rt, -0.1);
	if (rt->mini.type != -1)
		*i = 0;
	if (rt->mini.type == 4)
		init_camera_late(rt);
}

void	e_check(t_minirt *rt, int *i)
{
	rotz(rt, 0.1);
	if (rt->mini.type != -1)
		*i = 0;
	if (rt->mini.type == 4)
		init_camera_late(rt);
}
