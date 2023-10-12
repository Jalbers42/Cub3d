/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:46:51 by jalbers           #+#    #+#             */
/*   Updated: 2023/10/12 13:12:29 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_start_x(int y, int radius)
{
	int	x;
	int	y_offset;

	y_offset = radius - y;
	x = radius - sqrt(radius * radius - (y_offset * y_offset));
	return (x);
}

t_vector	get_rotated_pixel(t_game *game, t_vector minimap_pixel)
{
	t_vector	rotated_pixel;
	double		radians;

	radians = atan2(game->dir.y, game->dir.x) - atan2(1, 0);
	rotated_pixel.x = minimap_pixel.x
		* cos(radians) - minimap_pixel.y * sin(radians);
	rotated_pixel.y = minimap_pixel.x
		* sin(radians) + minimap_pixel.y * cos(radians);
	return (rotated_pixel);
}

int	draw_pixel(t_game *game, int y, int x)
{
	int			block;
	t_vector	minimap_pixel;
	t_vector	rotated_pixel;
	int			y_map_value;
	int			x_map_value;

	minimap_pixel.x = (MINIMAP_RADIUS - x);
	minimap_pixel.y = (MINIMAP_RADIUS - y);
	rotated_pixel = get_rotated_pixel(game, minimap_pixel);
	y_map_value = game->pos.y + (rotated_pixel.y * MINIMAP_ZOOM);
	x_map_value = game->pos.x + (rotated_pixel.x * MINIMAP_ZOOM);
	if (y_map_value >= 0 && y_map_value < game->map_height
		&& x_map_value >= 0 && x_map_value < game->map_width)
		block = game->map[y_map_value][x_map_value];
	else
		block = 0;
	if (block == 1)
		mlx_put_pixel(game->mlx_img, x + game->minimap_pos_x,
			y + game->minimap_pos_y, MINIMAP_WALL_COLOR);
	else
		mlx_put_pixel(game->mlx_img, x + game->minimap_pos_x,
			y + game->minimap_pos_y, MINIMAP_BG_COLOR);
	return (0);
}

void	draw_player(t_game *game)
{
	int	player_pos_y;
	int	player_pos_x;
	int	y;
	int	x;
	int	end_x;

	player_pos_y = game->screen_height - MINIMAP_MARGIN - 
		MINIMAP_RADIUS - MINIMAP_PLAYER_RADIUS;
	player_pos_x = MINIMAP_MARGIN + MINIMAP_RADIUS - MINIMAP_PLAYER_RADIUS;
	y = 0;
	while (y <= MINIMAP_PLAYER_RADIUS * 2)
	{
		x = get_start_x(y, MINIMAP_PLAYER_RADIUS);
		end_x = MINIMAP_PLAYER_RADIUS * 2 - x;
		while (x <= end_x)
		{
			mlx_put_pixel(game->mlx_img, x + player_pos_x, y + player_pos_y,
				MINIMAP_PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

int	minimap(t_game *game)
{
	int	y;
	int	x;
	int	end_x;

	game->minimap_pos_y = game->screen_height - 
		MINIMAP_RADIUS * 2 - MINIMAP_MARGIN;
	game->minimap_pos_x = MINIMAP_MARGIN;
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
