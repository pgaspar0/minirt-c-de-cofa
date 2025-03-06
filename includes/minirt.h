/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <pgaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:01:56 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/05 12:48:31 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "vex.h"
# include "../libs/libft/libft.h"

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_alight
{
	double	ratio;
	t_color	color;
}			t_alight;

typedef struct s_camera
{
	t_point	coordinates;
	t_point	o_vector;
	int		fov;
}			t_camera;

typedef struct s_light
{
	t_point	coordinates;
	double	ratio;
	t_color	color;
}			t_light;

typedef struct s_sphere
{
	t_point	coordinates;
	double	diameter;
	t_color	color;
}			t_sphere;

typedef struct s_plane
{
	t_point	coordinates;
	t_point	n_vector;
	t_color	color;
}			t_plane;

typedef struct s_cylinder
{
	t_point	coordinates;
	t_point	a_vector;
	double	diameter;
	double	height;
	t_color	color;
}			t_cylinder;

typedef	struct s_minirt
{
	t_alight	alight;
	t_camera	camera;
	t_light		light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}	t_minirt;

char		**get_map(char *file);

void		parse_map(char **map, t_minirt *rt);

#endif
