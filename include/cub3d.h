/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/27 12:29:27 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#define BPP sizeof(int32_t)
#define BUFFER_SIZE_READFILE 100

#include "MLX42/MLX42.h"
//#include "libft/libft.h"
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

typedef struct	s_game {

	char		**map;
	t_vector	pos; //position of character on the map
	t_vector	dir; //looking direktion of the character on start
	t_vector	plane; //camera plane (set to x = 0; y = 0.66)

} t_game;

t_game          *init_game();
char	        *read_file(int fd);
int	            parse_file(t_game *game, char *file_name);
void            handle_error(char *error, t_game *game);
void            destroy_game(t_game *game);
void			raycasting(t_game *game);

#endif