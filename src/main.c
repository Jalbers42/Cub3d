/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/04 13:53:56 by ycardona         ###   ########.fr       */
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

void	ft_rotate_dir(t_vector *dir, int rot_dir)
{
	t_vector	old_dir;

	old_dir = *dir;
	if (rot_dir == MLX_KEY_D)
	{
		dir->x = -old_dir.y;
		dir->y = old_dir.x;
	}
	if (rot_dir == MLX_KEY_A)
	{
		dir->x = old_dir.y;
		dir->y = -old_dir.x;
	}
}

void	ft_move(int mov_dir, t_game *game)
{
	t_vector	temp_dir;
	
	if (mov_dir == MLX_KEY_W)
    {
    	if(game->map[(int)game->pos.y][(int)(game->pos.x + game->dir.x * MOV_SPEED)] == 0)
	  		game->pos.x += game->dir.x * MOV_SPEED;
		if(game->map[(int)(game->pos.y + game->dir.y * MOV_SPEED)][(int)game->pos.x] == 0)
	  		game->pos.y += game->dir.y * MOV_SPEED;
	}
    if (mov_dir == MLX_KEY_S)
    {
		if(game->map[(int)game->pos.y][(int)(game->pos.x - game->dir.x * MOV_SPEED)] == 0)
	  		game->pos.x -= game->dir.x * MOV_SPEED;
		if(game->map[(int)(game->pos.y - game->dir.y * MOV_SPEED)][(int)game->pos.x] == 0)
			game->pos.y -= game->dir.y * MOV_SPEED;
    }
	if (mov_dir == MLX_KEY_D || mov_dir == MLX_KEY_A)
	{
		temp_dir = game->dir;
		ft_rotate_dir(&temp_dir, mov_dir);
		if(game->map[(int)game->pos.y][(int)(game->pos.x + temp_dir.x * MOV_SPEED)] == 0)
	  		game->pos.x += temp_dir.x * MOV_SPEED;
		if(game->map[(int)(game->pos.y + temp_dir.y * MOV_SPEED)][(int)game->pos.x] == 0)
	  		game->pos.y += temp_dir.y * MOV_SPEED;
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
}

void	ft_cursor_hook(double xpos, double ypos, void* param)
{
	t_game *game = param;
	
	if (game->mouse_pos.x < xpos)
		ft_rotate(MLX_KEY_RIGHT, game);
	if (xpos < game->mouse_pos.x)
		ft_rotate(MLX_KEY_LEFT, game);
	if (xpos < 5 || game->screen_width - 5 < xpos)
	{
		xpos = game->screen_width / 2;
		ypos = game->screen_height / 2;
		mlx_set_mouse_pos(game->mlx, xpos, ypos);
	}
	game->mouse_pos.x = xpos;
	game->mouse_pos.y = ypos;
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
	destroy_game(game);
	return (EXIT_SUCCESS);
}
