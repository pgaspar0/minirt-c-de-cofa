/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vexmanip3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:29:03 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/09 18:29:04 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vex.h"

int	is_norm(t_point v)
{
	return (fabs(vecmod(v) - 1) < 0.00001);
}

t_point	vecmult(t_point u, t_point v)
{
	t_point	w;

	w.x = u.x * v.x;
	w.y = u.y * v.y;
	w.z = u.z * v.z;
	return (w);
}

t_point	rotate_x(t_point u, double angle)
{
	t_point	v;

	v.x = u.x;
	v.y = u.y * cos(angle) - u.z * sin(angle);
	v.z = u.y * sin(angle) + u.z * cos(angle);
	return (v);
}

t_point	rotate_y(t_point u, double angle)
{
	t_point	v;

	v.x = u.x * cos(angle) + u.z * sin(angle);
	v.y = u.y;
	v.z = -u.x * sin(angle) + u.z * cos(angle);
	return (v);
}

t_point	rotate_z(t_point u, double angle)
{
	t_point	v;

	v.x = u.x * cos(angle) - u.y * sin(angle);
	v.y = u.x * sin(angle) + u.y * cos(angle);
	v.z = u.z;
	return (v);
}
