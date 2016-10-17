/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 20:07:08 by atoulous          #+#    #+#             */
/*   Updated: 2016/09/30 15:47:32 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "Libs/libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include <OpenCL/opencl.h>
# include </System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h>

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
** global environnement defines
*/

# define MLX var->mlx
# define WIN var->win
# define IMG var->img
# define DATA var->data
# define BPP var->bpp
# define SIZELINE var->sizeline
# define ENDIAN var->endian
# define WIDTH_WIN var->width_win
# define HEIGHT_WIN var->height_win
# define COLOR var->color
# define TH var->th

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
** global environnement variables
*/

typedef struct		s_var
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				sizeline;
	int				endian;
	int				width_win;
	int				height_win;
	int				color;
	int				th;
	struct s_ray	*ray[NB_TH];
}					t_var;

void				fill_image(t_var *var, int x, int y, int color);
void				free_all(t_var *var);
int					launch_rtv1(t_var *var);
int					ft_key(int keycode, t_var *var);
int					ft_release(int keycode, t_var *var);
int					ft_mouse(int button, int x, int y, t_var *var);
int					ft_motion_mouse(int x, int y, t_var *var);
int					ft_crossquit(t_var *var);

#endif
