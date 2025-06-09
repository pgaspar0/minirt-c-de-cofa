/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vexmanip2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:29:00 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/09 18:29:00 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vex.h"

t_point	vecsoma(t_point u, t_point v)
{
	t_point	w;

	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.z = u.z + v.z;
	return (w);
}

t_point	vecdif(t_point u, t_point v)
{
	t_point	w;

	w.x = u.x - v.x;
	w.y = u.y - v.y;
	w.z = u.z - v.z;
	return (w);
}

t_point	vecprodesc(t_point u, double escalar)
{
	t_point	v;

	v.x = u.x * escalar;
	v.y = u.y * escalar;
	v.z = u.z * escalar;
	return (v);
}

double	vecmod(t_point v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

t_point	vecnorm(t_point u)
{
	double	mod;
	t_point	v;

	mod = vecmod(u);
	v.x = u.x / mod;
	v.y = u.y / mod;
	v.z = u.z / mod;
	return (v);
}
