/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:46:39 by jalbers           #+#    #+#             */
/*   Updated: 2023/10/12 12:10:51 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_game *game, int **map)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
			printf("%i", map[y][x++]);
		printf("\n");
		y++;
	}
}

int	set_map_value(t_game *game, int y, int x, char input)
{
	if (is_invalid_character(input))
		handle_error("Invalid map character", game);
	else if (input == ' ')
		game->map[y][x] = 0;
	else if (input == 'N' || input == 'S' || input == 'E' || input == 'W')
	{
		set_player_details(game, y, x, input);
		game->map[y][x] = 0;
	}
	else if (input == 'X')
	{
		game->sprite_pos.y = y + 0.5;
		game->sprite_pos.x = x + 0.5;
		game->map[y][x] = 0;
	}
	else
		game->map[y][x] = input - '0';
	return (0);
}

void	fill_map(t_game *game, char *file_content)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width
			&& file_content[i] && file_content[i] != '\n')
			set_map_value(game, y, x++, file_content[i++]);
		while (x < game->map_width)
			game->map[y][x++] = 0;
		i++;
		y++;
	}
	if (game->player_pos_count == 0)
		handle_error("No player starting position found on map", game);
}

int	create_map(t_game *game, char *map_str)
{
	if (!*map_str)
		handle_error("no map", game);
	game->map_width = calc_max_width(map_str);
	game->map_height = calc_max_height(map_str);
	game->map = malloc_map(game);
	fill_map(game, map_str);
	check_wall(game);
	return (0);
}
