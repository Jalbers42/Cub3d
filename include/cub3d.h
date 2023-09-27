/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Jalbers42                                         #+#    #+#             */
/*   https://github.com/Jalbers42                     ###   ###########       */
/*                                                                            */
/******************************************************************************/

#ifndef SO_LONG_H
# define SO_LONG_H

#define BPP sizeof(int32_t)
#define BUFFER_SIZE_READFILE 100
#define TOTAL_INPUT_ELEMENTS 7

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// for memset
#include <string.h>

typedef struct s_game {
    int     map_width;
    int     map_height;
    char    **map;
    // player position
    
} t_game;
t_game          *init_game();
char	        *get_file_content(t_game *game, char *file_name);
int	            parse_file(t_game *game, char *file_name);
void            handle_error(char *error, t_game *game);
void            destroy_game(t_game *game);
int             parse_map(t_game *game, char *file_content);
#endif