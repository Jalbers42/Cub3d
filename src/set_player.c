/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/11 12:33:06 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_direction(t_game *game, char input)
{
	game->dir.x = 0;
	game->dir.y = 0;
	if (input == 'N')
		game->dir.y = -1;
	else if (input == 'S')
		game->dir.y = 1;
	else if (input == 'E')
		game->dir.x = 1;
	else if (input == 'W')
		game->dir.x = -1;
}

void	set_plane(t_game *game)
{
	game->plane.y = game->dir.x * FOV;
	game->plane.x = game->dir.y * -1 * FOV;
}

void	set_player_pos(t_game *game, int y, int x)
{
	if (game->player_pos_count == 1)
		handle_error("Multiple player positions on map", game);
	game->pos.y = y + 0.5;
	game->pos.x = x + 0.5;
	game->player_pos_count++;
}

void	set_player_details(t_game *game, int y, int x, char input)
{
	set_player_pos(game, y, x);
	set_player_direction(game, input);
	set_plane(game);
}
