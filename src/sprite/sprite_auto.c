/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_auto.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:10:11 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/09 12:42:18 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check_x(int new_x, int new_x_min, int new_x_max, t_game *game)
{
	if (0 <= new_x && 0 <= new_x_min
		&& 0 <= new_x_max && new_x < game->map_width
		&& new_x_min < game->map_width
		&& new_x_max < game->map_width)
	{
		if (game->map[(int)(game->sprite_pos.y)][new_x] == 0 \
			&& game->map[(int)(game->sprite_pos.y)][new_x_min] == 0 \
			&& game->map[(int)(game->sprite_pos.y)][new_x_max] == 0)
			return (0);
	}
	return (1);
}

static int	ft_check_y(int new_y, int new_y_min, int new_y_max, t_game *game)
{
	if (0 <= new_y && 0 <= new_y_min
		&& 0 <= new_y_max && new_y < game->map_height
		&& new_y_min < game->map_height
		&& new_y_max < game->map_height)
	{
		if (game->map[new_y][(int)(game->sprite_pos.x)] == 0 \
			&& game->map[new_y_min][(int)(game->sprite_pos.x)] == 0 \
			&& game->map[new_y_max][(int)(game->sprite_pos.x)] == 0)
			return (0);
	}
	return (1);
}

static int	ft_stet_text(t_game *game)
{
	if (game->finger != 0)
	{
		game->sprite_text = game->sprite_text3;
		return (1);
	}
	if (game->counter == 0)
		game->sprite_text = game->sprite_text1;
	if (game->counter == 15)
		game->sprite_text = game->sprite_text2;
	return (0);
}

void	ft_move_sprite(t_game *game)
{
	t_vector	sprite_dir;
	t_vector	sprite_dir_neg;

	if (ft_stet_text(game) != 0)
		return ;
	sprite_dir.x = game->pos.x - game->sprite_pos.x;
	sprite_dir.y = game->pos.y - game->sprite_pos.y;
	sprite_dir_neg.x = -sprite_dir.y;
	sprite_dir_neg.y = sprite_dir.x;
	if (ft_check_x((game->sprite_pos.x + sprite_dir.x * MOV_SPEED / 2), \
	(game->sprite_pos.x + sprite_dir_neg.x + sprite_dir.x * MOV_SPEED / 2), \
	(game->sprite_pos.x - sprite_dir_neg.x + sprite_dir.x * MOV_SPEED / 2), \
	game) == 0)
		game->sprite_pos.x += sprite_dir.x * MOV_SPEED / 2;
	if (ft_check_y((game->sprite_pos.y + sprite_dir.y * MOV_SPEED / 2), \
	(game->sprite_pos.y + sprite_dir_neg.y + sprite_dir.y * MOV_SPEED / 2), \
	(game->sprite_pos.y - sprite_dir_neg.y + sprite_dir.y * MOV_SPEED / 2), \
	game) == 0)
			game->sprite_pos.y += sprite_dir.y * MOV_SPEED / 2;
}
