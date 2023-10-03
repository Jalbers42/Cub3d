/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/03 11:42:22 by ycardona         ###   ########.fr       */
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
	game->screen_width = WIDTH;
	game->screen_height = HEIGHT;
    game->mouse_pos.x = WIDTH / 2;
    game->mouse_pos.x = HEIGHT / 2;

    return (game);
}