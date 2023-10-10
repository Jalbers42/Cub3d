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

#include "cub3d.h"

int	**copy_map(t_game *game)
{
	int	**map_copy;
	int	y;
	int	x;

	map_copy = malloc_map(game);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			map_copy[y][x] = game->map[y][x];
			x++;
		}
		y++;
	}
	return (map_copy);
}

int	is_wall_incomplete(t_game *game, int **map, int y, int x)
{
	int	w;
	int	h;

	w = game->map_width;
	h = game->map_height;
	map[y][x] = 1;
	if (y == 0 || y == h - 1 || x == 0 || x == w - 1)
		return (1);
	if (map[y][x - 1] != 1 && is_wall_incomplete(game, map, y, x - 1))
		return (1);
	if (map[y][x + 1] != 1 && is_wall_incomplete(game, map, y, x + 1))
		return (1);
	if (map[y - 1][x] != 1 && is_wall_incomplete(game, map, y - 1, x))
		return (1);
	if (map[y + 1][x] != 1 && is_wall_incomplete(game, map, y + 1, x))
		return (1);
	return (0);
}

int	check_wall(t_game *game)
{
	int	**map_copy;

	map_copy = copy_map(game);
	if (is_wall_incomplete(game, map_copy, game->pos.y, game->pos.x))
	{
		free_map(game, map_copy);
		handle_error("Incomplete wall", game);
	}
	free_map(game, map_copy);
	return (0);
}
