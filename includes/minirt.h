/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:01:56 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/23 08:08:50 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HEIGHT 1080
# define WIDTH 1920

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include "./vex.h"

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
	double	radius;
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
	double	radius;
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
	double		psizex;
	double		psizey;
	double		viewport_height;
	double		viewport_width;
	t_point		p_centro;
	t_point		p_first;
	t_point		right;
	t_point		up;
	t_color		background;
	void    	*con;
    void    	*img;
    void    	*window;
    int     	bpp;
    int     	endian;
    int     	size_line;
    char    	*data;
	int			sp;
	int			pl;
	int			cy;
	double		closest;
}	t_minirt;

int			color_to_int(t_color color);
int			intersect_sphere(t_sphere *sphere, t_point direction, t_minirt *rt, double *t);

char		**get_map(char *file);

void		parse_map(char **map, t_minirt *rt);
void		init_camera(t_minirt *rt);
void		put_scene(t_minirt *rt);
void		put_pixel(t_minirt *rt, int x, int y, int color);

t_color		add_dlight(t_minirt *rt, t_color color, t_color old_color, t_point bateu, t_point normal);
t_color		intersect_scene(t_point direction, t_minirt *rt);
t_color		add_alight(t_color color, t_minirt *rt);

#endif
