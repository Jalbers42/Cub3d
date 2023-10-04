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

#define MINIMAP_MARGIN 25
#define MINIMAP_RADIUS 80
#define MINIMAP_ZOOM 0.12
#define MINIMAP_PLAYER_RADIUS 2

int get_start_x(int y, int radius)
{
    int x;    
    int y_offset = radius - y;

    x = radius - sqrt(radius * radius - (y_offset * y_offset));
    return (x);
}

t_vector    get_rotated_pixel(t_game *game, t_vector minimap_pixel)
{
    t_vector rotated_pixel;

    double radians = atan2(game->dir.y, game->dir.x) - atan2(1, 0);

    rotated_pixel.x = minimap_pixel.x * cos(radians) - minimap_pixel.y * sin(radians);
    rotated_pixel.y = minimap_pixel.x * sin(radians) + minimap_pixel.y * cos(radians);
    return (rotated_pixel);
}

int draw_pixel(t_game *game, int y, int x)
{
    int minimap_pos_y = game->screen_height - MINIMAP_RADIUS * 2 - MINIMAP_MARGIN;
    int minimap_pos_x = MINIMAP_MARGIN;
    int block;

    t_vector minimap_pixel = {(MINIMAP_RADIUS - x), (MINIMAP_RADIUS - y)};
    t_vector    rotated_pixel = get_rotated_pixel(game, minimap_pixel);

    int     y_map_value = game->pos.y + (rotated_pixel.y * MINIMAP_ZOOM);
    int     x_map_value = game->pos.x + (rotated_pixel.x * MINIMAP_ZOOM);

    if (y_map_value >= 0 && y_map_value < game->map_height && x_map_value >= 0 && x_map_value < game->map_width)
        block = game->map[y_map_value][x_map_value];
    else
        block = 0;
    if (block == 1)
        mlx_put_pixel(game->mlx_img, x + minimap_pos_x, y + minimap_pos_y, 16699713);
    else
        mlx_put_pixel(game->mlx_img, x + minimap_pos_x, y + minimap_pos_y, 1778473);
    return (0);
}

void    draw_player(t_game *game)
{
    int player_pos_y = game->screen_height - MINIMAP_MARGIN - MINIMAP_RADIUS - MINIMAP_PLAYER_RADIUS;
    int player_pos_x = MINIMAP_MARGIN + MINIMAP_RADIUS - MINIMAP_PLAYER_RADIUS;
    int y;
    int x;
    int end_x;
    
    y = 0;
    while (y <= MINIMAP_PLAYER_RADIUS * 2)
    {
        x = get_start_x(y, MINIMAP_PLAYER_RADIUS);
        end_x = MINIMAP_PLAYER_RADIUS * 2 - x;
        while (x <= end_x)
        {
            mlx_put_pixel(game->mlx_img, x + player_pos_x, y + player_pos_y, 15669971);
            x++;
        }
        y++;
    } 
}
            
int minimap(t_game *game)
{
    int y;
    int x;
    int end_x;
    
    y = 0;
    while (y <= MINIMAP_RADIUS * 2)
    {
        x = get_start_x(y, MINIMAP_RADIUS);
        end_x = MINIMAP_RADIUS * 2 - x;
        while (x <= end_x)
        {
            draw_pixel(game, y, x);
            x++;
        }
        y++;
    } 
    draw_player(game);
    return (0);
}