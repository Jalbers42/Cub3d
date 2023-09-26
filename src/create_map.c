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

int	calc_max_width(char *file_str)
{
    int max_width = 0;
    int current_width;
	int	i = 0;
    
	while (file_str[i])
    {
        current_width = 0;
        while (file_str[i] && file_str[i] != '\n')
        {
            current_width++;
            i++;
        }
        if (current_width > max_width)
            max_width = current_width;
        if (file_str[i])
            i++;
    }
	return (max_width);
}

int	calc_max_height(char *file_str)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (file_str[i])
	{
		if (file_str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

char    **malloc_map(t_game *game)
{
    char **map = malloc(game->map_height * sizeof(char*));
    int i = 0;
    while (i < game->map_height)
        map[i++] = malloc(game->map_width * sizeof(char));
    return (map);
}

void    fill_map(t_game *game, char *file_content)
{
    int i = 0;
    int y = 0;
    int x;

    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width && file_content[i] != '\n')
            game->map[y][x++] = file_content[i++];
        while (x < game->map_width)
            game->map[y][x++] = ' ';
        i++;
        y++;
    }
}

int create_map(t_game *game, char *file_content)
{
    game->map_width = calc_max_width(file_content);
    game->map_height = calc_max_height(file_content);
    game->map = malloc_map(game);
    fill_map(game, file_content);
    return (0);
}
