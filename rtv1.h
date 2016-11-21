/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 20:07:08 by atoulous          #+#    #+#             */
/*   Updated: 2016/11/21 18:32:13 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "Libs/libft/libft.h"
# include "mlx.h"
# include "X.h"
# include <math.h>
# include <pthread.h>
# include <OpenCL/opencl.h>

# define NB_TH 10

# define BASE10 "0123456789"
# define BASE16 "0123456789ABCDEF"

/*
** raytracing defines
*/

# define HIT ray->hit
# define RAY ray->ray
# define CAM_DIR ray->var->cam_dir
# define CAM_UP ray->var->cam_up
# define CAM_RIGHT ray->var->cam_right
# define VIEW_PLANE_DIST ray->viewplanedist
# define VIEW_PLANE_UPLEFT ray->viewplaneupleft
# define VIEW_PLANE_WIDTH ray->viewplane_width
# define VIEW_PLANE_HEIGHT ray->viewplane_height
# define X_INDENT ray->x_indent
# define Y_INDENT ray->y_indent

/*
** object param
*/

#define OBJ_STR var->object[OBJ]->str
#define OBJ_NAME var->object[OBJ]->name
#define OBJ_TYPE var->object[OBJ]->type
#define OBJ_INTER var->object[OBJ]->inter
#define OBJ_STR_COLOR var->object[OBJ]->str_color
#define OBJ_COLOR var->object[OBJ]->obj_color
#define OBJ_SIZE var->object[OBJ]->obj_size
#define OBJ_SIZE_WIDTH var->object[OBJ]->size_width
#define OBJ_SIZE_HEIGHT var->object[OBJ]->size_height
#define OBJ_RGB var->object[OBJ]->obj_rgb
#define OBJ_ORIGIN var->object[OBJ]->obj_origin

/*
** global environnement defines
*/

# define MLX var->mlx
# define WIN var->win
# define IMG var->img
# define DATA var->data
# define DOC var->doc
# define SCENE_NAME var->scene_name
# define CAMERA var->camera
# define ORIGIN var->origin
# define RENDER var->render
# define TAB_OBJECT var->tab_object
# define BPP var->bpp
# define SIZELINE var->sizeline
# define ENDIAN var->endian
# define WIDTH_WIN var->width_win
# define HEIGHT_WIN var->height_win
# define COLOR var->color
# define TH var->th
# define OBJ var->obj
# define I var->i
# define NB_OBJ var->nb_obj
# define CAM_POS var->cam_pos

/*
** raytracing variables
*/

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_ray
{
	double			viewplanedist;
	double			viewplane_width;
	double			viewplane_height;
	double			x_indent;
	double			y_indent;
	int				hit;
	t_vector		viewplaneupleft;
	t_vector		ray;
	struct s_var	*var;

}					t_ray;

/*
** object param
*/

typedef struct		s_obj
{
	char			*str;
	char			*name;
	char			*type;
	char			*inter;
	char			*str_color;
	char			*obj_rgb;
	unsigned int	obj_color;
	double			obj_size;
	double			size_width;
	double			size_height;
	t_vector		obj_origin;
}					t_obj;

/*
** global environnement variables
*/

typedef struct		s_var
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	char			*doc;
	char			*scene_name;
	char			*camera;
	char			*origin;
	char			*render;
	double			width_win;
	double			height_win;
	int				bpp;
	int				sizeline;
	int				endian;
	int				color;
	int				th;
	int				obj;
	int				nb_obj;
	int				i;
	t_vector		cam_pos;
	t_vector		cam_dir;
	t_vector		cam_up;
	t_vector		cam_right;
	t_ray			*ray[NB_TH];
	t_obj			**object;
}					t_var;

void				fill_image(t_var *var, int x, int y, int color);
void				free_all(t_var *var);
void				parse_doc(int fd, t_var *var);
void				init_variables(t_var *var);
void				init_raytracing(t_ray *ray);
void				check_scene_param(t_var *var, char **tb, char *size);
void				check_object_param(t_var *var);
int					launch_rtv1(t_var *var);
int					ft_key(int keycode, t_var *var);
int					ft_release(int keycode, t_var *var);
int					ft_mouse(int button, int x, int y, t_var *var);
int					ft_motion_mouse(int x, int y, t_var *var);
int					ft_crossquit(t_var *var);

void				print_vector(t_vector v, char *str);
double				norm_vector(t_vector v);
t_vector			unit_vector(t_vector v);
t_vector			fill_vector(double x, double y, double z);
t_vector			*new_vector(double x, double y, double z);
t_vector			time_vector(t_vector v, double i);
t_vector			add_vectors(t_vector v1, t_vector v2);
t_vector			sub_vectors(t_vector v1, t_vector v2);
t_vector			perp_vectors(t_vector v1, t_vector v2);

#endif
