/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/28 10:51:05 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#define BPP sizeof(int32_t)
#define BUFFER_SIZE_READFILE 100
#define TOTAL_INPUT_ELEMENTS 7

#include "MLX42/MLX42.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

// for memset
#include <string.h>

#define SKY 0x2bdafcFF
#define	FLOOR 0x4a1e06FF
#define RED 0xFF0000FF
#define LIGHT_RED 0xdb3232FF
#define WIDTH 1024
#define HEIGHT 768

typedef struct	s_vector {

	double	x;
	double	y;

} t_vector;

typedef	struct s_rc_data
{
	double		cam_x;
	t_vector	ray;
	t_vector	d_side_dist;	
	t_vector	side_dist;
	t_vector	field;
	t_vector 	step;
	int			side;
	int			line_height;
} t_rc_data;


typedef struct	s_game {

	char		**map;
	int			map_width;
    int			map_height;
	int			screen_width;
	int			screen_height;
	t_vector	pos; //position of character on the map
	t_vector	dir; //looking direktion of the character on start
	t_vector	plane; //camera plane (set to x = 0; y = 0.66)
	mlx_image_t		*mlx_img;
	mlx_t			*mlx;

} t_game;

t_game          *init_game();
char	        *get_file_content(t_game *game, char *file_name);
int	            parse_file(t_game *game, char *file_name);
void            handle_error(char *error, t_game *game);
void            destroy_game(t_game *game);
void			raycasting(t_game *game);

int             create_map(t_game *game, char *file_content);
#endif