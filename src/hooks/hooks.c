/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:42:47 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/09 17:21:57 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_rotate(int rot_dir, t_game *game)
{
	t_vector	old_dir;
	t_vector	old_plane;

	old_dir = game->dir;
	old_plane = game->plane;
	if (rot_dir == MLX_KEY_LEFT)
	{
		game->dir.x = old_dir.x * cos(-ROT_SPEED) - old_dir.y * sin(-ROT_SPEED);
		game->dir.y = old_dir.x * sin(-ROT_SPEED) + old_dir.y * cos(-ROT_SPEED);
		game->plane.x = old_plane.x * cos(-ROT_SPEED) \
		- old_plane.y * sin(-ROT_SPEED);
		game->plane.y = old_plane.x * sin(-ROT_SPEED) \
		+ old_plane.y * cos(-ROT_SPEED);
	}
	if (rot_dir == MLX_KEY_RIGHT)
	{
		game->dir.x = old_dir.x * cos(ROT_SPEED) - old_dir.y * sin(ROT_SPEED);
		game->dir.y = old_dir.x * sin(ROT_SPEED) + old_dir.y * cos(ROT_SPEED);
		game->plane.x = old_plane.x * cos(ROT_SPEED) \
		- old_plane.y * sin(ROT_SPEED);
		game->plane.y = old_plane.x * sin(ROT_SPEED) \
		+ old_plane.y * cos(ROT_SPEED);
	}
}

void	ft_move_check(mlx_key_data_t keydata, t_game *game)
{
	int	key;

	key = keydata.key;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		ft_move(MLX_KEY_W, game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		ft_move(MLX_KEY_S, game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		ft_move(MLX_KEY_D, game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		ft_move(MLX_KEY_A, game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		ft_rotate(MLX_KEY_LEFT, game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		ft_rotate(MLX_KEY_RIGHT, game);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_N)
		|| mlx_is_key_down(game->mlx, MLX_KEY_M))
		game->finger = keydata.key;
	else
		game->finger = 0;
	if (game->finished == true)
		return ;
	ft_move_check(keydata, game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		open_door(game);
}

void	ft_cursor_hook(double xpos, double ypos, void *param)
{
	t_game	*game;

	game = param;
	if (game->screen_width / 2 < xpos)
		ft_rotate(MLX_KEY_RIGHT, game);
	if (xpos < game->screen_width / 2)
		ft_rotate(MLX_KEY_LEFT, game);
	xpos = game->screen_width / 2;
	ypos = game->screen_height / 2;
	mlx_set_mouse_pos(game->mlx, xpos, ypos);
}

void	ft_plot(void *param)
{
	t_game		*game;
	mlx_image_t	*temp_img;

	game = param;
	if (ft_game_over(game) == 0)
	{
		temp_img = game->mlx_img;
		game->mlx_img = mlx_new_image(game->mlx, \
		game->screen_width, game->screen_height);
		game->counter++;
		if (30 == game->counter)
			game->counter = 0;
		raycasting(game);
		if (game->counter % 15 == 0)
			ft_move_sprite(game);
		ft_finger(game->finger, game);
		minimap(game);
		mlx_delete_image(game->mlx, temp_img);
		mlx_image_to_window(game->mlx, game->mlx_img, 0, 0);
	}
	return ;
}
