/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_auto.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:10:11 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/09 19:16:39 by ycardona         ###   ########.fr       */
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
		if ((game->map[(int)(game->sprite_pos.y)][new_x] == 0
			|| game->map[(int)(game->sprite_pos.y)][new_x] == 3) \
			&& (game->map[(int)(game->sprite_pos.y)][new_x_min] == 0
			|| game->map[(int)(game->sprite_pos.y)][new_x_min] == 3) \
			&& (game->map[(int)(game->sprite_pos.y)][new_x_max] == 0
			|| game->map[(int)(game->sprite_pos.y)][new_x_max] == 3))
			return (0);
	}
	return (1);
}

static int	ft_check_y(int new_y, int new_y_min, int new_y_max, t_game *game)
{
	if (0 < new_y && 0 < new_y_min
		&& 0 < new_y_max && new_y < game->map_height
		&& new_y_min < game->map_height
		&& new_y_max < game->map_height)
	{
		if ((game->map[new_y][(int)(game->sprite_pos.x)] == 0
			|| game->map[new_y][(int)(game->sprite_pos.x)] == 3) \
			&& (game->map[new_y_min][(int)(game->sprite_pos.x)] == 0
			|| game->map[new_y_min][(int)(game->sprite_pos.x)] == 3) \
			&& (game->map[new_y_max][(int)(game->sprite_pos.x)] == 0
			|| game->map[new_y_max][(int)(game->sprite_pos.x)] == 3))
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

/* void	ft_find_new(t_vector *new_pos, t_game *game)
{
	t_vector	sprite_dir;
	
	sprite_dir.x = game->pos.x - game->sprite_pos.x;
	sprite_dir.y = game->pos.y - game->sprite_pos.y;
	
} */

void	ft_move_sprite(t_game *game)
{
	t_vector	sprite_dir;
	t_vector	sprite_ortho;
	t_vector	new_pos;
	double		fact;

	if (ft_stet_text(game) != 0)
		return ;
	fact = 2.0;
	sprite_dir.x = game->pos.x - game->sprite_pos.x;
	sprite_dir.y = game->pos.y - game->sprite_pos.y;
	sprite_dir.x = sprite_dir.x / sqrt(pow(sprite_dir.x, 2) + pow(sprite_dir.y, 2));
	sprite_dir.y = sprite_dir.y / sqrt(pow(sprite_dir.x, 2) + pow(sprite_dir.y, 2));
	/* sprite_dir_neg.x = -sprite_dir.y;
	sprite_dir_neg.y = sprite_dir.x; */
	new_pos.x = game->sprite_pos.x;
	new_pos.y = game->sprite_pos.y;
	sprite_ortho.x = -sprite_dir.y / sqrt(pow(-sprite_dir.y, 2) + pow(sprite_dir.x, 2));
	sprite_ortho.y = sprite_dir.x / sqrt(pow(-sprite_dir.y, 2) + pow(sprite_dir.x, 2));
	if (ft_check_x((game->sprite_pos.x + sprite_dir.x * MOV_SPEED), \
	(game->sprite_pos.x + sprite_ortho.x * fact + sprite_dir.x * MOV_SPEED), \
	(game->sprite_pos.x - sprite_ortho.x * fact + sprite_dir.x * MOV_SPEED), \
	game) == 0)
		new_pos.x = game->sprite_pos.x + sprite_dir.x * MOV_SPEED;
	if (ft_check_y((game->sprite_pos.y + sprite_dir.y * MOV_SPEED), \
	(game->sprite_pos.y + sprite_ortho.y * fact + sprite_dir.y * MOV_SPEED), \
	(game->sprite_pos.y - sprite_ortho.y * fact + sprite_dir.y * MOV_SPEED), \
	game) == 0)
		new_pos.y = game->sprite_pos.y + sprite_dir.y * MOV_SPEED;
	/* if (new_pos.y == game->sprite_pos.y && new_pos.x == game->sprite_pos.x)
		ft_find_new(&new_pos, game); */
	game->sprite_pos.x = new_pos.x;
	game->sprite_pos.y = new_pos.y; 
}
