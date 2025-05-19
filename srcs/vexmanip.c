/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vexmanip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:41:14 by pgaspar           #+#    #+#             */
/*   Updated: 2025/05/20 00:08:15 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vex.h"

double	escprod(t_point u, t_point v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

t_point	vecprod(t_point u, t_point v)
{
	t_point	w;

	w.x = (u.y * v.z) - (u.z * v.y);
	w.y = (u.z * v.x) - (u.x * v.z);
	w.z = (u.x * v.y) - (u.y * v.x);
	return (w);
}

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
