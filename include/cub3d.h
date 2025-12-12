/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:51:40 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/12 16:57:43 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

/*==================================*/
/*==============MACRO===============*/
/*==================================*/
# define PI 3.14159265358979323846

# define GAMENAME "CUB3D"
# define W_WIDTH 1024
# define W_HEIGHT 768

# define TILE_LEN 64

# define FPS 60
# define ANIM_MS 1000

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define SPACE 32
# define LSHIFT 65505
# define M 109

/*==================================*/
/*==============STRUCTS=============*/
/*==================================*/
typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_rectangle
{
	int				x;
	int				y;
	int				width;
	int				height;
}					t_rectangle;

typedef struct s_arrow
{
	t_vector		pos;
	double			width;
	double			height;
	double			angle;
}					t_arrow;

typedef struct s_img
{
	int				img_width;
	int				img_height;
	void			*sprite;
	char			*addr;
	int				bbp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_imgtextures
{
	int				frames_north;
	t_img			*wall_north;
	int				frames_south;
	t_img			*wall_south;
	int				frames_east;
	t_img			*wall_east;
	int				frames_west;
	t_img			*wall_west;
	int				frames_door;
	t_img			*wall_door;
}					t_imgtextures;

typedef struct s_player
{
	t_vector		pos;
	double			direction;
	double			fov;

	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			key_turn_l;
	bool			key_turn_r;
	bool			key_sprint;
	bool			key_space_pressed;

	double			box_width;
	double			walk_spd;
	double			turn_spd;
}					t_player;

typedef struct s_texture
{
	char			**texture_north;
	char			**texture_south;
	char			**texture_east;
	char			**texture_west;
}				t_texture;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bbp;
	int				line_len;
	int				endian;

	t_player		player;
	t_texture		texture;
	t_imgtextures	wall_imgs;

	char			**map;
	int				map_width;
	int				map_height;
	int				**door_state;

	int				col_ceil;
	int				col_floor;

	bool			minimap;

	struct timeval	time_fps;
	double			ms_fps;
	struct timeval	time_anim;
	double			ms_anim;
}					t_game;

typedef struct s_raydata
{
	t_vector		vect;
	int				wall_side;
	double			angle;
	double			dist;
	double			height;
	int				start_y;
	int				end;
}					t_raydata;

typedef struct s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct s_stack
{
	t_coord			*coord;
	struct s_stack	*next;
}					t_stack;

/*==================================*/
/*============FONCTIONS=============*/
/*==================================*/

/*===================*/
/*=====Mini_Libf=====*/
/*===================*/
/*Mini_Libf*/
int					ft_isdigit(int c);
int					ft_isnum(char *string);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
char				*ft_strdup(const char *src);

/*Mini_Libf2*/
char				*skip_white_space(char *string);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_perror(char *string);
void				*ft_bzero(void *ptr, size_t num);
size_t				ft_strlcat(char *dst, const char *src, size_t size);

/*Mini_Libf3*/
int					ft_is_visible(char *string);

/*Ft_Realloc*/
char				**ft_realloc(char **tab, char *string);

/*Tab_utils*/
void				tab_char_clear(char **tab);
int					lenght_tab(char **tab);

/*Ft_Split*/
char				**ft_split(char const *s, char c);

/*Ft_Transpose*/
char				**ft_transpose(char **tab_map);

/*===================*/
/*=======Stack=======*/
/*===================*/
int					is_empty_stack(t_stack *st);
t_stack				*push_stack(t_stack *st, int x, int y);
t_stack				*clear_stack(t_stack *st);
t_stack				*pop_stack(t_stack *st);

/*===================*/
/*======Checking=====*/
/*===================*/
/*Checking Map*/
int					check_map(char **tab_map);
t_coord				get_pos_player(char **tab_map);
int					get_ori_player(char **tab_map);
int					in(t_stack *stack_path, int x, int y);
int					get_width_map(char **tab_map);
t_stack				*parse_map(char **tab_map);

/*Checking Map Path*/
int					check_map_path(char **tab_map);

/*Checking Map Path2*/
int					clear_map(t_stack *stack_wall, t_stack **stack_path,
						t_stack **stack_save);

/*Checking Colour*/
int					check_colour(char **tab_col, t_game *data);

/*Checking Texture*/
int					check_texture(char **tab_tex, t_game *data);


/*Checking Texture2*/
int 				check_texture2(t_game *data, char *name_file, char *path, int i);
void    			clear_texture(t_game *data);

/*Checking Texture3*/
int 				texture_copy_info(t_game *data, char *tmp, int i);

/*===================*/
/*======Parsing======*/
/*===================*/
/*Parsing*/
int					parsing(char *name_map, t_game *data);
int					open_map(char *name_map);

/*Parsing2*/
int					fill_information(char *string, char ***tab_tex,
						char ***tab_col);
int					fill_colour_texture(char *string, char ***tab_col);
int					clear_parsing(char **tab_map, char **tab_tex,
						char **tab_col);
int					check_extension(char *name_map, char *extention);

/*Parsing3*/
int					manage_data_loop(char ***tab_map, char ***tab_tex,
						char ***tab_col, char *string);

/*===================*/
/*======PLAYER=======*/
/*===================*/

/*Player*/
void				init_player(t_player *player);
void				move_player(t_game *data, t_player *player);
void				turn_player(t_player *player);

/*Door check*/
void				door_check(t_game *data, t_player *player);

/*Player collision*/
void				move_collision(t_game *data, t_player *player, double x_spd,
						double y_spd);

/*===================*/
/*========DRAW=======*/
/*===================*/

/*Draw_Basic*/
void				draw_pixel(t_game *data, int x, int y, int color);
void				draw_rectangle(t_game *data, t_rectangle rect, int color);
void				draw_line(t_game *data, t_vector vct1, t_vector vct2,
						int color);

/*Draw_Arrow*/
void				draw_arrow(t_game *data, t_arrow arrow, int color);

/*=========================*/
/*========REDNDERING=======*/
/*=========================*/

/*Draw_Minimap*/
void				draw_minimap(t_game *data);

/*Raycast rendering*/
void				render_raycast(t_game *data, t_player player);
t_img				*render_get_img(t_game *data, t_raydata *ray);
int					door_img_x_add(t_game *data, t_raydata ray, t_img img);

/*===================*/
/*===MATHEMATIQUES===*/
/*===================*/

/*Angle_Math*/
double				deg2rad(double angle);
double				rad2deg(double angle);
double				angle_limit(double angle);

/*Dtrig*/
double				dsin(double angle);
double				dcos(double angle);
double				dtan(double angle);

/*Point_Math*/
double				point_angle(double x1, double y1, double x2, double y2);
double				point_dist(double x1, double y1, double x2, double y2);
double				vect_angle(t_vector vct1, t_vector vct2);
double				vect_dist(t_vector vct1, t_vector vct2);

/*Vect_Math*/
void				vect_add(t_vector *dest, t_vector src, double angle,
						double dist);

/*========================*/
/*=======RAYCASTING=======*/
/*========================*/

/*Raycast*/
int					raycast(t_game *data, t_vector *ray_vect, double angle,
						bool prec);
bool				is_raycast_hztl(t_game *data, t_vector hztl, t_vector vtcl,
						bool prec);

/*Ray collison*/
bool				ray_collision(t_game *data, t_vector ray_vect,
						bool is_hztl);

/*Collision*/
bool				vect_in_wall(t_game *data, t_vector point);
bool				player_in_wall(t_game *data, t_player player);
char				vect_get_tile(t_game *data, t_vector point);
void				vect_to_mapcoord(t_vector point, t_coord *map_coord);

/*======================*/
/*=======TEXTURES=======*/
/*======================*/

/*Initialise images*/
bool				init_imgs(t_game *data, t_imgtextures *imgs,
						t_texture *texts);

/*Texture reading*/
unsigned int		get_img_pixel_col(t_img *img, int x, int y);

/*===================*/
/*=======EVENT=======*/
/*===================*/

/*Key Events*/
int					key_press(int key, t_game *data);
int					key_release(int key, t_game *data);

/*Loop_Event*/
int					loop_event(t_game *data);

/*Timing*/
double				add_timer_ms(struct timeval *time_src);

/*Door*/
void				door_anim(t_game *data);

/*=======================*/
/*=======GAME DATA=======*/
/*=======================*/

/*initialise game*/
bool				init_game(t_game *data);

/*Close game window*/
int					close_game(t_game *data);

/*Free mlx structure*/
void				kill_game(t_game *data);

#endif