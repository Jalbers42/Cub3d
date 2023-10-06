/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/06 17:09:04 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	ft_rotate(int rot_dir, t_game *game)
{
	t_vector old_dir;
	t_vector old_plane;

	old_dir = game->dir;
	old_plane = game->plane;
	if (rot_dir == MLX_KEY_LEFT)
	{
		game->dir.x = old_dir.x * cos(-ROT_SPEED) - old_dir.y * sin(-ROT_SPEED);
		game->dir.y = old_dir.x * sin(-ROT_SPEED) + old_dir.y * cos(-ROT_SPEED);
	 	game->plane.x = old_plane.x * cos(-ROT_SPEED) - old_plane.y * sin(-ROT_SPEED);
		game->plane.y = old_plane.x * sin(-ROT_SPEED) + old_plane.y * cos(-ROT_SPEED);
	}
	if (rot_dir == MLX_KEY_RIGHT)
	{
		game->dir.x = old_dir.x * cos(ROT_SPEED) - old_dir.y * sin(ROT_SPEED);
		game->dir.y = old_dir.x * sin(ROT_SPEED) + old_dir.y * cos(ROT_SPEED);
		game->plane.x = old_plane.x * cos(ROT_SPEED) - old_plane.y * sin(ROT_SPEED);
		game->plane.y = old_plane.x * sin(ROT_SPEED) + old_plane.y * cos(ROT_SPEED);
	}
}

int	get_player_block(t_game *game)
{
	int	new_y = (int)game->pos.y;
	int	new_x = (int)game->pos.x;

	return (game->map[new_y][new_x]);
}

void	ft_move(int mov_dir, t_game *game)
{
	double	x_move = 0;
	double	y_move = 0;
	int		current_block = get_player_block(game);
	int		new_block;

	if (mov_dir == MLX_KEY_W)
    {
		y_move += game->pos.y + game->dir.y * MOV_SPEED;
		x_move += game->pos.x + game->dir.x * MOV_SPEED;
	}
    if (mov_dir == MLX_KEY_S)
    {
		y_move += game->pos.y - game->dir.y * MOV_SPEED;
		x_move += game->pos.x - game->dir.x * MOV_SPEED;
    }
	if (mov_dir == MLX_KEY_D)
	{
		y_move += game->pos.y + game->dir.x * MOV_SPEED;
		x_move += game->pos.x - game->dir.y * MOV_SPEED;
	}	
	if (mov_dir == MLX_KEY_A)
	{
		y_move += game->pos.y - game->dir.x * MOV_SPEED;
		x_move += game->pos.x + game->dir.y * MOV_SPEED;
	}
	new_block = game->map[(int)y_move][(int)game->pos.x];
	if ((int)y_move == (int)game->pos.y)
	  	game->pos.y = y_move;
	else if(new_block != 1 && !(new_block == 2 && current_block == 2))
	  	game->pos.y = y_move;
	new_block = game->map[(int)game->pos.y][(int)x_move];
	if ((int)x_move == (int)game->pos.x)
	  	game->pos.x = x_move;
	else if(new_block != 1 && !(new_block == 2 && current_block == 2))
	  	game->pos.x = x_move;
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

void	ft_key_hook(mlx_key_data_t keydata, void* param)
{
	t_game *game = param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		open_door(game);
}

void	ft_cursor_hook(double xpos, double ypos, void* param)
{
	t_game *game = param;
	
	if (game->screen_width / 2 < xpos)
		ft_rotate(MLX_KEY_RIGHT, game);
	if (xpos < game->screen_width / 2)
		ft_rotate(MLX_KEY_LEFT, game);
	xpos = game->screen_width / 2;
	ypos = game->screen_height / 2;
	mlx_set_mouse_pos(game->mlx, xpos, ypos);
	//raycasting(game);
}

/* void	ft_resize_hook(int32_t width, int32_t height, void* param)
{
	t_game *game = param;

	game->screen_width = width;
	game->screen_height = height;
} */

void	ft_plot(void* param)
{
	t_game *game = param;
	if (game->counter % 15 == 0)
		ft_move_sprite(game);
	//mlx_delete_image(game->mlx, game->mlx_img);
	//game->mlx_img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
	game->counter++;
	if (45 == game->counter )
		game->counter = 0;
	raycasting(game);
	minimap(game);
	return ;
}

int	main(int argc, char **argv)
{
	t_game *game;

	if (argc != 2)
		handle_error("Wrong number of arguments", NULL);
	game = init_game();
	parse_file(game, argv[1]);

	// MLX allows you to define its core behaviour before startup.
	//mlx_set_setting(mlx_settings_t setting, int32_t value);
	game->mlx = mlx_init(game->screen_width, game->screen_height, "cub3d", false);
	if (!game->mlx)
		ft_error();
	mlx_set_cursor_mode(game->mlx, 0x00034002);
	game->mlx_img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
	if (!game->mlx_img || (mlx_image_to_window(game->mlx, game->mlx_img, 0, 0) < 0))
		ft_error();

	raycasting(game);
	mlx_key_hook(game->mlx, &ft_key_hook, game);
	mlx_cursor_hook(game->mlx, &ft_cursor_hook, game);
	//mlx_resize_hook(game->mlx, &ft_resize_hook, game);
	mlx_loop_hook(game->mlx, &ft_plot, game);
	mlx_loop(game->mlx);
	mlx_delete_image(game->mlx, game->mlx_img);
	mlx_delete_texture(game->NO);
	mlx_delete_texture(game->SO);
	mlx_delete_texture(game->WE);
	mlx_delete_texture(game->EA);
	//delete all textures
	destroy_game(game);
	return (EXIT_SUCCESS);
}
