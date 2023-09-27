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

void    free_map(t_game *game)
{
    int y = 0;
    
    while (y < game->map_height)
        free(game->map[y++]);
    free(game->map);
}

void    destroy_game(t_game *game)
{
    if (game->map != NULL)
        free_map(game);
    free(game);
}