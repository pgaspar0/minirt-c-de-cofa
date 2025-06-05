/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:32:49 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/05 16:35:54 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	up_check(t_minirt *rt, int *i)
{
	transy(rt, 0.5);
	if (rt->mini.type != -1)
		*i = 0;
}

void	down_check(t_minirt *rt, int *i)
{
	transy(rt, -0.5);
	if (rt->mini.type != -1)
		*i = 0;
}

void	left_check(t_minirt *rt, int *i)
{
	transx(rt, -0.5);
	if (rt->mini.type != -1)
		*i = 0;
}

void	right_check(t_minirt *rt, int *i)
{
	transx(rt, 0.5);
	if (rt->mini.type != -1)
		*i = 0;
}

void	i_check(t_minirt *rt, int *i)
{
	transz(rt, 0.5);
	if (rt->mini.type != -1)
		*i = 0;
}
