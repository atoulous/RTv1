/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 20:07:08 by atoulous          #+#    #+#             */
/*   Updated: 2016/10/19 19:50:04 by atoulous         ###   ########.fr       */
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

/*
** raytracing defines
*/

# define POS_X var->ray[TH]->pos_x
# define POS_Y var->ray[TH]->pos_y
# define POS_Z var->ray[TH]->pos_z
# define ROT_X var->ray[TH]->rot_x
# define ROT_Y var->ray[TH]->rot_y
# define ROT_Z var->ray[TH]->rot_z
# define FOC var->ray[TH]->foc

/*
** object param
*/

#define OBJ_STR var->object[OBJ]->str
#define OBJ_NAME var->object[OBJ]->name
#define OBJ_INTER var->object[OBJ]->inter
#define OBJ_STR_COLOR var->object[OBJ]->str_color
#define OBJ_COLOR var->object[OBJ]->color

/*
** global environnement defines
*/

# define MLX var->mlx
# define WIN var->win
# define IMG var->img
# define DATA var->data
# define DOC var->doc
# define CPY var->cpy
# define SCENE_NAME var->scene_name
# define CAMERA var->camera
# define RENDER var->render
# define TAB_OBJECT var->tab_object
# define BPP var->bpp
# define SIZELINE var->sizeline
# define ENDIAN var->endian
# define WIDTH_WIN var->width_win
# define HEIGHT_WIN var->height_win
# define COLOR var->color
# define TH var->th
# define NB_OBJ var->nb_obj
# define OBJ var->obj

/*
** raytracing variables
*/

typedef struct		s_ray
{
	double			pos_x;
	double			pos_y;
	double			pos_z;
	double			rot_x;
	double			rot_y;
	double			rot_z;
	double			foc;
}					t_ray;

/*
** object param
*/

typedef struct		s_obj
{
	char			*str;
	char			*name;
	char			*inter;
	char			*str_color;
	char			*red;
	char			*green;
	char			*blue;
	int				color;
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
	char			*cpy;
	char			*scene_name;
	char			*camera;
	char			*render;
	char			**tab_object;
	int				bpp;
	int				sizeline;
	int				endian;
	int				width_win;
	int				height_win;
	int				color;
	int				th;
	int				obj;
	int				nb_obj;
	struct s_ray	*ray[NB_TH];
	struct s_obj	**object;
}					t_var;

void				fill_image(t_var *var, int x, int y, int color);
void				free_all(t_var *var);
void				parse_doc(int fd, t_var *var);
int					launch_rtv1(t_var *var);
int					ft_key(int keycode, t_var *var);
int					ft_release(int keycode, t_var *var);
int					ft_mouse(int button, int x, int y, t_var *var);
int					ft_motion_mouse(int x, int y, t_var *var);
int					ft_crossquit(t_var *var);

#endif
