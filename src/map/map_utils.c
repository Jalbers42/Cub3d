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

int	calc_max_width(char *map_str)
{
	int	max_width;
	int	line_width;
	int	i;

	i = 0;
	max_width = 0;
	while (map_str[i])
	{
		line_width = 0;
		while (map_str[i] && map_str[i] != '\n')
		{
			line_width++;
			i++;
		}
		if (line_width > max_width)
			max_width = line_width;
		if (map_str[i])
			i++;
	}
	return (max_width);
}

int	calc_max_height(char *map_str)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (map_str[i])
	{
		if (map_str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

int	is_invalid_character(char input)
{
	if (input != '1' && input != '0' && input != '2' && input != ' '
		&& input != 'N' && input != 'S' 
		&& input != 'W' && input != 'E' && input != 'X')
		return (1);
	return (0);
}

int	**malloc_map(t_game *game)
{
	int	**map;
	int	i;

	map = malloc(game->map_height * sizeof(int *));
	i = 0;
	while (i < game->map_height)
		map[i++] = malloc(game->map_width * sizeof(int));
	return (map);
}

void	free_map(t_game *game, int **map)
{
	int	y;

	y = 0;
	while (y < game->map_height)
		free(map[y++]);
	free(map);
}
