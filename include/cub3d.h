/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/26 15:12:05 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#define BPP sizeof(int32_t)
#define BUFFER_SIZE_READFILE 100

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// for memset
#include <string.h>

typedef struct	s_vector {

	double	x;
	double	y;

} t_vector;

typedef struct	s_game {

	char		**map;
	t_vector	start_pos; //position of character on the map
	t_vector	start_dir; //looking direktion of the character on start

} t_game;

t_game          *init_game();
char	        *read_file(int fd);
int	            parse_file(t_game *game, char *file_name);
void            handle_error(char *error, t_game *game);
void            destroy_game(t_game *game);

#endif