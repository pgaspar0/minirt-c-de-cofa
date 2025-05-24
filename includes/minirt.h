/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/01 11:41:06 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HEIGHT 500
# define WIDTH 500

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include "./vex.h"
# include <X11/keysym.h>

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_alight
{
	double		ratio;
	t_color		color;
}				t_alight;

typedef struct s_camera
{
	t_point		coordinates;
	t_point		o_vector;
	int			fov;
}				t_camera;

typedef struct s_light
{
	t_point		coordinates;
	double		ratio;
	t_color		color;
}				t_light;

typedef struct s_sphere
{
	t_point		coordinates;
	double		diameter;
	double		radius;
	t_color		color;
}				t_sphere;

typedef struct s_plane
{
	t_point		coordinates;
	t_point		n_vector;
	t_color		color;
}				t_plane;

typedef struct s_cylinder
{
	t_point		coordinates;
	t_point		a_vector;
	double		diameter;
	double		radius;
	double		height;
	t_color		color;
}				t_cylinder;

typedef struct	s_minielem
{
	int	type;
	int	index;
}	t_minielem;

typedef struct s_minirt
{
	t_alight	alight;
	t_camera	camera;
	t_light		light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_minielem	mini;
	double		psizex;
	double		psizey;
	double		viewport_height;
	double		viewport_width;
	t_point		p_centro;
	t_point		p_first;
	t_point		right;
	t_point		up;
	t_color		background;
	void		*con;
	void		*img;
	void		*window;
	int			bpp;
	int			endian;
	int			size_line;
	char		*data;
	int			sp;
	int			pl;
	int			cy;
	double		closest;
	int			in;
}				t_minirt;

int				color_to_int(t_color color);
int				intersect_sphere(t_sphere *sphere, t_point direction,
					t_minirt *rt, double *t);
int				intersect_plane(t_minirt *rt, t_plane *plane, t_point direction,
					double *t);
int				check_colors(t_color color);
int				check_alight(t_alight *ambiente);
int				check_camera(t_camera *camera);
int				check_light(t_light *light);
int				check_sphere(t_sphere *sphere);
int				check_plane(t_plane *plane);
int				check_cylinder(t_cylinder *cylinder);
int				check_scene(t_minirt *scene);
int				keys(int keycode, void *param);
int				close_des(t_minirt *rt);
// int				intersect_cylinder(t_cylinder *cy, t_point direction,
// 					t_minirt *rt, double *t);
int				in_shadow(t_minirt *rt, t_point point, t_point light_dir);

//test functions
t_color	cylinder_loop(t_minirt *rt, t_point dir, double *closest_t, t_color color);
int	intersect_cylinder(t_cylinder *cy, t_point dir, t_minirt *rt, double *t);


char			**get_map(char *file);

void			rotx(t_minirt *rt, double val);
void			roty(t_minirt *rt, double val);
void			rotz(t_minirt *rt, double val);
void			transx(t_minirt *rt, double val);
void			transy(t_minirt *rt, double val);
void			transz(t_minirt *rt, double val);
void    		clean_all(t_minirt *rt);
void			parse_map(char **map, t_minirt *rt);
void			init_camera(t_minirt *rt);
void			put_scene(t_minirt *rt);
void			put_pixel(t_minirt *rt, int x, int y, int color);
void    		up_check(t_minirt *rt, int *i);
void    		down_check(t_minirt *rt, int *i);
void    		left_check(t_minirt *rt, int *i);
void    		right_check(t_minirt *rt, int *i);
void    		i_check(t_minirt *rt, int *i);
void    		k_check(t_minirt *rt, int *i);
void    		w_check(t_minirt *rt, int *i);
void    		s_check(t_minirt *rt, int *i);
void    		a_check(t_minirt *rt, int *i);
void    		d_check(t_minirt *rt, int *i);
void    		q_check(t_minirt *rt, int *i);
void    		e_check(t_minirt *rt, int *i);


t_color			add_dlight(t_minirt *rt, t_color color, t_color old_color,
					t_point bateu, t_point normal);
t_color			sphere_loop(t_minirt *rt, t_point direction, double *t,
					t_color color);
t_color			plane_loop(t_minirt *rt, t_point direction, double *t,
					t_color color);
t_color			add_light(t_color color, t_minirt *rt, t_point bateu,
					t_point normal, int i);
t_color			intersect_scene(t_point direction, t_minirt *rt);
t_color			colormult(t_color color, double mult);
t_color			add_alight(t_color color, t_minirt *rt);
// t_color			cylinder_loop(t_minirt *rt, t_point direction, double *t,
// 					t_color color);
t_point	get_pixel(int i, int j, t_minirt *rt);
t_point	get_cylinder_normal2(t_cylinder *cy, t_point hit, int aux);
t_point	get_cylinder_normal(t_cylinder *cy, t_point hit);
int	intersect_cap(t_point ro, t_point d, t_point center, t_point normal, double radius, double *t);


#endif
