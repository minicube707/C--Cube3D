/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:51:40 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/02 14:19:02 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>

/*==================================*/
/*==============MACRO===============*/
/*==================================*/
# define PI	3.14159265358979323846

# define GAMENAME	"CUB3D"
# define W_WIDTH	1920
# define W_HEIGHT	1080

# define TILE_LEN	100

# define ESC	65307
# define W		119
# define A		97
# define S		115
# define D		100
# define LEFT	65361
# define RIGHT	65363
# define SPACE	32

/*==================================*/
/*==============STRUCUT=============*/
/*==================================*/
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_rectangle
{
	int		x;
	int		y;
	int		width;
	int		height;
}	t_rectangle;

typedef struct s_player
{
	t_vector	pos;
	double		direction;
	double		fov;
	double		plane_dist;

	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		key_turn_l;
	bool		key_turn_r;

	double		box_width;
	double		walk_spd;
	double		turn_spd;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bbp;
	int			line_len;
	int			endian;

	t_player	player;

	char		**map;
	int			map_width;
	int			map_height;
}	t_game;

/*==================================*/
/*============FONCTOIN==============*/
/*==================================*/

/*===================*/
/*=======MAP=========*/
/*===================*/

/*Setup_Map*/
bool	init_map(t_game *data);
void	wipeout_map(t_game *data);

/*===================*/
/*======PLAYER=======*/
/*===================*/

/*Player*/
void	init_player(t_player *player, double x, double y, double angle);
int		key_press(int key, t_player *player);
int		key_release(int key, t_player *player);
void	move_player(t_player *player);
void	turn_player(t_player *player);

/*===================*/
/*========DRAW=======*/
/*===================*/

/*Draw_Basic*/
void	draw_pixel(t_game *data, int x, int y, int color);
void	draw_rectangle(t_game *data, t_rectangle rect, int color);
void	draw_line(t_game *data, t_vector vct1, t_vector vct2, int color);

/*===================*/
/*===MATHEMATIQUES===*/
/*===================*/

/*Dtrig*/
double	deg2rad(double angle);
double	dsin(double angle);
double	dcos(double angle);
double	dtan(double angle);

/*Point_Math*/
double	point_angle(double x1, double y1, double x2, double y2);
double	point_dist(double x1, double y1, double x2, double y2);
double	vect_angle(t_vector vct1, t_vector vct2);
double	vect_dist(t_vector vct1, t_vector vct2);

/*Vect_Math*/
void	vect_add(t_vector *dest, t_vector src, double angle, double dist);

/*===================*/
/*=======EVENT=======*/
/*===================*/

/*Loop_Event*/
int		loop_event(t_game *data);

#endif