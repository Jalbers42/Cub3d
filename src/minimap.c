/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/05 20:03:40 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int draw_circle()
// {
//     int y;
//     int x;

//     while ()
// }
#include <math.h>
#define MINIMAP_MARGIN 25
#define MINIMAP_RADIUS 80
#define MINIMAP_ZOOM 0.12
#define MINIMAP_PLAYER_RADIUS 2

int get_start_x(int y, int radius)
{
    // center_x = radius;
    // center_y = radius;
    int x;    
    int y_offset = radius - y;

    x = radius - sqrt(radius * radius - (y_offset * y_offset));
    return (x);
}

int draw_pixel(t_game *game, int y, int x)
{
    int minimap_pos_y = game->screen_height - MINIMAP_RADIUS * 2 - MINIMAP_MARGIN;
    int minimap_pos_x = MINIMAP_MARGIN;
    int block;

    double  y_delta = (MINIMAP_RADIUS - y) * -1;
    double  x_delta = (MINIMAP_RADIUS - x) * -1;
    int     y_map_value = game->pos.y + (y_delta * MINIMAP_ZOOM);
    int     x_map_value = game->pos.x + (x_delta * MINIMAP_ZOOM);

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