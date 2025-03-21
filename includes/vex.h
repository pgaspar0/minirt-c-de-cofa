/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:44:04 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/06 12:53:00 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEX_H
# define VEX_H

# include <math.h>

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}			t_point;


int			is_norm(t_point v);

double		escprod(t_point u, t_point v);
double		vecmod(t_point v);

t_point		vecnorm(t_point u);
t_point		vecmult(t_point u, t_point v);
t_point		vecdif(t_point u, t_point v);
t_point		vecprod(t_point u, t_point v);
t_point		vecsoma(t_point u, t_point v);
t_point		vecprodesc(t_point u, double escalar);

#endif
