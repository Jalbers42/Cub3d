/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/06 00:52:49 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define BPP sizeof(int32_t)
#define BUFFER_SIZE_READFILE 100
#define TOTAL_INPUT_ELEMENTS 7
#define FOV 0.66
#define SKY 0x2bdafcFF
#define	FLOOR 0x4a1e06FF
#define RED 0xFF0000FF
#define LIGHT_RED 0xdb3232FF
#define WIDTH 960
#define HEIGHT 640
#define LEFT 0
#define RIGHT 1
#define ROT_SPEED 0.01
#define MOV_SPEED 0.2

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
	
	mlx_image_t		*mlx_img;
	mlx_t			*mlx;

	mlx_texture_t	*NO;
	mlx_texture_t	*SO;
	mlx_texture_t	*WE;
	mlx_texture_t	*EA;

	int				c_color;
	int				f_color;

	t_vector	mouse_pos;

	t_vector	sprite_pos;
	double		sprite_width;
	mlx_texture_t	*sprite_text;

	mlx_texture_t	*sky_text;
	int				**sky_box;

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

#endif