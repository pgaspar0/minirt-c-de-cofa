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
