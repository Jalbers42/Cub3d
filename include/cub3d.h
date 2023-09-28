/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/27 15:23:06 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#define BPP sizeof(int32_t)
#define BUFFER_SIZE_READFILE 100
#define TOTAL_INPUT_ELEMENTS 7
#define FOV 0.66

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

typedef struct s_colors{
	char *F;
	char *C;
} t_colors;

typedef struct	s_game {

	char		*file_content;
	int			**map;
	int			map_width;
    int			map_height;
	t_textures	textures;
	t_colors	colors;

	t_vector	pos; //position of character on the map
	t_vector	dir; //looking direktion of the character on start
	t_vector	plane; //camera plane (set to x = 0; y = 0.66)

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
#endif