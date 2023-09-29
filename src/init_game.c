/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/29 14:32:59 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game  *init_game()
{
    t_game  *game;

    game = malloc(sizeof(t_game));
    game->map = NULL;
    game->tokens = NULL;
    game->player_pos_count = 0;

    game->map_width = 25;
	game->map_height = 10;
	game->screen_width = WIDTH;
	game->screen_height = HEIGHT;
	game->plane.x = -0.66;
	game->plane.y = 0;
	game->pos.x = 1.5;
	game->pos.y = 1.5;
	game->dir.x = 0;
	game->dir.y = 1;

    return (game);
}