/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_auto.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:10:11 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/06 14:40:49 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_move_sprite(t_game *game)
{
    t_vector sprite_dir;

    sprite_dir.x = game->pos.x - game->sprite_pos.x;
    sprite_dir.y = game->pos.y - game->sprite_pos.y;

    if(game->map[(int)(game->sprite_pos.y)][(int)((game->sprite_pos.x + sprite_dir.x * MOV_SPEED))] == 0)
	  	game->sprite_pos.x += sprite_dir.x * MOV_SPEED;
	if(game->map[(int)((game->sprite_pos.y + sprite_dir.y * MOV_SPEED))][(int)(game->sprite_pos.x)] == 0)
	  	game->sprite_pos.y += sprite_dir.y * MOV_SPEED;
}