/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:47:41 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/09 20:26:22 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calc_move(t_vector *move, int mov_dir, t_game *game)
{
	if (mov_dir == MLX_KEY_W)
	{
		move->y = game->pos.y + game->dir.y * MOV_SPEED;
		move->x = game->pos.x + game->dir.x * MOV_SPEED;
	}
	if (mov_dir == MLX_KEY_S)
	{
		move->y = game->pos.y - game->dir.y * MOV_SPEED;
		move->x = game->pos.x - game->dir.x * MOV_SPEED;
	}
	if (mov_dir == MLX_KEY_D)
	{
		move->y = game->pos.y + game->dir.x * MOV_SPEED;
		move->x = game->pos.x - game->dir.y * MOV_SPEED;
	}	
	if (mov_dir == MLX_KEY_A)
	{
		move->y = game->pos.y - game->dir.x * MOV_SPEED;
		move->x = game->pos.x + game->dir.y * MOV_SPEED;
	}
}

void	ft_move(int mov_dir, t_game *game)
{
	t_vector	move;
	int			current_block;
	int			new_block;

	current_block = get_player_block(game);
	move.x = game->pos.x;
	move.y = game->pos.y;
	ft_calc_move(&move, mov_dir, game);
	new_block = game->map[(int)move.y][(int)game->pos.x];
	if ((int)move.y == (int)game->pos.y)
		game->pos.y = move.y;
	else if (new_block != 1 && !(new_block == 2 && current_block == 2))
		game->pos.y = move.y;
	new_block = game->map[(int)game->pos.y][(int)move.x];
	if ((int)move.x == (int)game->pos.x)
		game->pos.x = move.x;
	else if (new_block != 1 && !(new_block == 2 && current_block == 2))
		game->pos.x = move.x;
}

void	open_door(t_game *game)
{
	if (get_player_block(game) == 2)
	{
		game->map[(int)game->pos.y][(int)game->pos.x] = 3;
		if (game->map[(int)game->pos.y][(int)game->pos.x + 1] == 2)
			game->map[(int)game->pos.y][(int)game->pos.x + 1] = 3;
		else if (game->map[(int)game->pos.y][(int)game->pos.x - 1] == 2)
			game->map[(int)game->pos.y][(int)game->pos.x - 1] = 3;
		else if (game->map[(int)game->pos.y + 1][(int)game->pos.x] == 2)
			game->map[(int)game->pos.y + 1][(int)game->pos.x] = 3;
		else if (game->map[(int)game->pos.y - 1][(int)game->pos.x] == 2)
			game->map[(int)game->pos.y - 1][(int)game->pos.x] = 3;
	}
	else if (get_player_block(game) == 3)
	{
		game->map[(int)game->pos.y][(int)game->pos.x] = 2;
		if (game->map[(int)game->pos.y][(int)game->pos.x + 1] == 3)
			game->map[(int)game->pos.y][(int)game->pos.x + 1] = 2;
		else if (game->map[(int)game->pos.y][(int)game->pos.x - 1] == 3)
			game->map[(int)game->pos.y][(int)game->pos.x - 1] = 2;
		else if (game->map[(int)game->pos.y + 1][(int)game->pos.x] == 3)
			game->map[(int)game->pos.y + 1][(int)game->pos.x] = 2;
		else if (game->map[(int)game->pos.y - 1][(int)game->pos.x] == 3)
			game->map[(int)game->pos.y - 1][(int)game->pos.x] = 2;
	}
}

int	ft_game_over(t_game *game)
{
	mlx_texture_t	*text;
	unsigned int	x;
	unsigned int	y;

	if (ft_dist(game->pos, game->sprite_pos) < 0.4)
	{
		x = 0;
		text = game->game_over_text;
		while (x < text->width)
		{
			y = 0;
			while (y < text->height)
			{
				if (ft_get_pixel(text, x, y) != 0)
					mlx_put_pixel(game->mlx_img, x + (game->screen_width - text->width) / 2, \
					y + (game->screen_height - text->height) / 2, ft_get_pixel(text, x, y));
				y++;
			}
			x++;
		}
		game->finished = true;
		return (1);
	}
	else
		return (0);
}
