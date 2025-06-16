/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:57:19 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/16 17:38:27 by jorcarva         ###   ########.fr       */
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
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>

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

typedef struct s_minielem
{
	int			type;
	int			index;
}				t_minielem;

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
	int			al;
	int			l;
	int			c;
	int			sp;
	int			pl;
	int			cy;
	double		closest;
	int			in;
	int			complete;
}				t_minirt;

typedef struct s_cylinder_state
{
	t_minirt	*rt;
	t_point		dir;
	t_point		normal;
	t_color		color;
	double		t;
	double		*closest_t;
	double		t_global;
	double		radius;
	int			closest_i;
	int			i;
	int			aux;
}				t_cylinder_state;

typedef struct s_vecs
{
	double		light_len;
	t_point		vec1;
	t_point		vec2;
}				t_vecs;

typedef struct s_intersection
{
	t_point		ro;
	t_point		axis;
	t_point		dir;
	t_point		hit_point;
	t_point		normal;
	double		closest_t;
	t_point		d_perp;
	t_point		oc_perp;
	int			hit;
	t_minirt	*rt;
	t_cylinder	*cy;
}				t_mini_intersect;

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
int				initial_checks(int ac, char *av[]);
int				is_bad_file_name(char *file);
int				is_directory(const char *file);
int				mouses(int button, int x, int y, void *param);
int				keys(int keycode, void *param);
int				close_des(t_minirt *rt);
int				in_shadow(t_minirt *rt, t_point point, t_point light_dir);
float			*get_delta(t_cylinder *cy, t_point d_perp, t_point oc_perp,
					t_point d);

t_color			cylinder_loop(t_minirt *rt, t_point dir, double *closest_t,
					t_color color);
t_color			parse_color(char *color);

int				intersect_cylinder(t_cylinder *cy, t_point dir, t_minirt *rt,
					double *t);

char			**get_map(char *file);

void			count_elements(char **map, t_minirt *rt);
void			rotx(t_minirt *rt, double val);
void			roty(t_minirt *rt, double val);
void			rotz(t_minirt *rt, double val);
void			transx(t_minirt *rt, double val);
void			transy(t_minirt *rt, double val);
void			transz(t_minirt *rt, double val);
void			clean_all(t_minirt *rt);
void			parse_map(char **map, t_minirt *rt);
void			init_camera(t_minirt *rt);
void			put_scene(t_minirt *rt);
void			put_pixel(t_minirt *rt, int x, int y, int color);
void			up_check(t_minirt *rt, int *i);
void			down_check(t_minirt *rt, int *i);
void			left_check(t_minirt *rt, int *i);
void			right_check(t_minirt *rt, int *i);
void			i_check(t_minirt *rt, int *i);
void			k_check(t_minirt *rt, int *i);
void			w_check(t_minirt *rt, int *i);
void			s_check(t_minirt *rt, int *i);
void			a_check(t_minirt *rt, int *i);
void			d_check(t_minirt *rt, int *i);
void			q_check(t_minirt *rt, int *i);
void			e_check(t_minirt *rt, int *i);
void			check_cylinder_body(t_cylinder_state *s, int i);
void			check_cap_top(t_cylinder_state *s, int i, t_point axis,
					t_point ro);
void			check_cap_bottom(t_cylinder_state *s, int i, t_point axis,
					t_point ro);
void			check_caps(t_cylinder_state *s, int i);
void			final_lighting(t_cylinder_state *s);
void			parse_sphere(char *line, t_minirt *rt, int index);
void			parse_plane(char *line, t_minirt *rt, int index);
void			parse_cylinder(char *line, t_minirt *rt, int index);
void			parse_alight(char *line, t_minirt *rt);
void			parse_camera(char *line, t_minirt *rt);
void			parse_light(char *line, t_minirt *rt);
void			init_camera_late(t_minirt *rt);

t_color			add_dlight(t_minirt *rt, t_color color, t_color old_color,
					t_vecs *vec);
t_color			sphere_loop(t_minirt *rt, t_point direction, double *t,
					t_color color);
t_color			plane_loop(t_minirt *rt, t_point direction, double *t,
					t_color color);
t_color			add_light(t_color color, t_minirt *rt, t_vecs *vec, int i);
t_color			intersect_scene(t_point direction, t_minirt *rt);
t_color			colormult(t_color color, double mult);
t_color			add_alight(t_color color, t_minirt *rt);
t_point			get_pixel(int i, int j, t_minirt *rt);
t_point			get_cylinder_normal(t_cylinder *cy, t_point hit,
					double dist_top, double dist_bottom);
t_point			parse_point(char *point);

int				intersect_cap(t_point ro, t_cylinder_state *s, t_point center,
					double *t);
int				intersect_cap2(t_mini_intersect *inter, t_point center,
					double radius, double *t);

int				in_shadow_sp(int i, t_minirt *rt, double t[2], t_vecs *vec);

void			init_t_inter(t_mini_intersect *t_inter, t_cylinder *cy,
					t_point dir, t_minirt *rt);
void			intersection_aux(t_mini_intersect *t_inter, double *t0,
					double *t1);
void			caps_aux(t_mini_intersect *t_inter, double *t_cap_top,
					t_point *cap_bottom);
void			ver_int(t_mini_intersect *inter, t_point cap_bottom);

#endif
