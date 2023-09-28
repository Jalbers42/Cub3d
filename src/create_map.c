/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/27 15:08:42 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int set_map_value(t_game *game, int y, int x, char input)
{
    
    if (is_invalid_character(input))
        return (1);
    else if (input == ' ')
        game->map[y][x] = 0;
    else if (input == 'N' || input == 'S' || input == 'E' || input == 'W')
    {
        set_player_details(game, y, x, input);
        game->map[y][x] = 0;
    }
    else
        game->map[y][x] = input - '0';
    return (0);
}

void    fill_map(t_game *game, char *file_content)
{
    int y = 0;
    int x;
    int i = 0;

    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width && file_content[i] && file_content[i] != '\n')
            set_map_value(game, y, x++, file_content[i++]);
        while (x < game->map_width)
            game->map[y][x++] = 0;
        i++;
        y++;
    }
}

int create_map(t_game *game, char *map_str)
{
    game->map_width = calc_max_width(map_str);
    game->map_height = calc_max_height(map_str);
    game->map = malloc_map(game);
    fill_map(game, map_str);
    check_wall(game);
    return (0);
}
