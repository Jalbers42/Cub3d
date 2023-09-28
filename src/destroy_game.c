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

void    destroy_game(t_game *game)
{
    if (game->file_content != NULL)
        free(game->file_content);
    if (game->tokens != NULL)
        free(game->tokens);
    if (game->map != NULL)
        free_map(game, game->map);

    free(game);
}