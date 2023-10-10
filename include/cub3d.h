/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/10 18:13:07 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define BPP sizeof(int32_t)
#define BUFFER_SIZE_READFILE 100
#define TOTAL_INPUT_ELEMENTS 10
#define FOV 0.66
#define SKY 0x2bdafcFF
#define	FLOOR 0x4a1e06FF
#define RED 0xFF0000FF
#define LIGHT_RED 0xdb3232FF
#define WIDTH 1280
#define HEIGHT 720
#define LEFT 0
#define RIGHT 1
#define ROT_SPEED 0.03
#define MOV_SPEED 0.2

#define MINIMAP_MARGIN 25
#define MINIMAP_RADIUS 80
#define MINIMAP_ZOOM 0.12
#define MINIMAP_PLAYER_RADIUS 2
#define MINIMAP_PLAYER_COLOR 15669971
#define MINIMAP_BG_COLOR 1778473
#define MINIMAP_WALL_COLOR 16699713

#include "MLX42/MLX42.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

// for memset
#include <string.h>

typedef struct	s_vector {

	double	x;
	double	y;

} t_vector;

typedef struct s_textures {
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *DOOR;
} t_textures;

typedef struct s_rgb{
	int	r;
	int	g;
	int	b;
	int	a;
} t_rgb;

typedef struct s_colors{
	t_rgb F;
	t_rgb C;
} t_colors;

typedef	struct s_rc_data
{
	double		cam_x;
	double		perpWallDist;
	double		text_hit;

	t_vector	ray;
	t_vector	norm_ray;
	t_vector	d_side_dist;	
	t_vector	side_dist;
	t_vector	field;
	t_vector 	step;
	int			side;
	int			line_height;
	int			start;
	int			end;
	mlx_texture_t	*text;

} t_rc_data;


typedef struct	s_game {

	char		*file_content;
	int			**map;
	int			map_width;
    int			map_height;
	int			screen_width;
	int			screen_height;

	int			player_pos_count;
	t_textures	textures;
	t_colors	colors;
	char		**tokens;


	t_vector	pos; //position of character on the map
	t_vector	dir; //looking direktion of the character on start
	t_vector	plane; //camera plane (set to x = 0; y = 0.66)
	int			counter; //counting frames

	mlx_image_t		*mlx_img;
	mlx_t			*mlx;

	mlx_texture_t	*NO;
	mlx_texture_t	*SO;
	mlx_texture_t	*WE;
	mlx_texture_t	*EA;
	mlx_texture_t	*DOOR;
	mlx_texture_t	*DOOR_WALL_1;
	mlx_texture_t	*DOOR_WALL_2;

	int				c_color;
	int				f_color;

	t_vector	mouse_pos;

	t_vector		sprite_pos;
	double			sprite_width;
	mlx_texture_t	*sprite_text;
	mlx_texture_t	*sprite_text1;
	mlx_texture_t	*sprite_text2;
	mlx_texture_t	*sprite_text3;

	mlx_texture_t	*sky_text;
	int				**sky_box;

	mlx_texture_t	*finger_left_text;
	mlx_texture_t	*finger_right_text;
	int				finger;

	bool	finished;
	mlx_texture_t	*game_over_text;

	int		minimap_pos_x;
	int		minimap_pos_y;

} t_game;

t_game          *init_game();
char	        *get_file_content(t_game *game, char *file_name);
int	            parse_file(t_game *game, char *file_name);
void            handle_error(char *error, t_game *game);
void            destroy_game(t_game *game);
void			raycasting(t_game *game);
int				check_wall(t_game *game);
int             create_map(t_game *game, char *map_str);
void    		print_map(t_game *game, int **map);
int				**malloc_map(t_game *game);
void    		free_map(t_game *game, int **map);
void			set_player_details(t_game *game, int y, int x, char input);
int				calc_max_width(char *map_str);
int				calc_max_height(char *map_str);
int 			**malloc_map(t_game *game);
int 			is_invalid_character(char input);
int				minimap(t_game *game);
void			ft_sprite(int x, t_rc_data *rc_data, t_game *game);

int				ft_get_pixel(mlx_texture_t* texture, int x, int y);
int				ft_min(int	a, int b);
void			ft_move_sprite(t_game *game);
double			ft_dist(t_vector p_a, t_vector p_b);
int				ft_get_a(int rgba);
t_rgb			ft_get_rgba(int color);
t_vector		ft_intersect(t_vector sprite_pos, t_vector plane, t_vector pos, t_vector ray);
int				ft_vect_dir(t_vector vector, t_vector p_a, t_vector p_b);
void			ft_set_text(t_rc_data *rc_data, t_game *game);
void			ft_draw_line(int x, t_rc_data *rc_data, t_game *game);
int				ft_blur(int color, double dist);
int				ft_min(int	a, int b);

void			ft_draw_sky(int x, int *y, t_game *game, t_rc_data *rc_data);
t_rc_data		*ft_init_rc(int x, t_game *game);


void			ft_finger(int mlx_key, t_game *game);

int				get_player_block(t_game *game);
void			ft_cursor_hook(double xpos, double ypos, void* param);
void			ft_key_hook(mlx_key_data_t keydata, void* param);
void			ft_plot(void* param);
void			ft_move(int mov_dir, t_game *game);
void			open_door(t_game *game);
int				ft_game_over(t_game *game);
void			set_texture(t_game *game, mlx_texture_t	**texture, char *path);
int				set_rgb(t_game *game, t_rgb *color, char *str);
void			print_map(t_game *game, int **map);
int				insert_tokens(char **tokens, char *str, char delimeter, int number_of_elements);

#endif