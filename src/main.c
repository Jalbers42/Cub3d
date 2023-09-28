/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/28 18:24:52 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define LEFT 0
#define RIGHT 1
#define ROT_SPEED 0.1
#define MOV_SPEED 0.5

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
	if (rot_dir == LEFT)
	{
		game->dir.x = old_dir.x * cos(-ROT_SPEED) - old_dir.y * sin(-ROT_SPEED);
		game->dir.y = old_dir.x * sin(-ROT_SPEED) + old_dir.y * cos(-ROT_SPEED);
	 	game->plane.x = old_plane.x * cos(-ROT_SPEED) - old_plane.y * sin(-ROT_SPEED);
		game->plane.y = old_plane.x * sin(-ROT_SPEED) + old_plane.y * cos(-ROT_SPEED);
	}
	if (rot_dir == RIGHT)
	{
		game->dir.x = old_dir.x * cos(ROT_SPEED) - old_dir.y * sin(ROT_SPEED);
		game->dir.y = old_dir.x * sin(ROT_SPEED) + old_dir.y * cos(ROT_SPEED);
		game->plane.x = old_plane.x * cos(ROT_SPEED) - old_plane.y * sin(ROT_SPEED);
		game->plane.y = old_plane.x * sin(ROT_SPEED) + old_plane.y * cos(ROT_SPEED);
	}
}

void	ft_move(int mov_dir, t_game *game)
{
	if (mov_dir == MLX_KEY_W)
    {
    	if(game->map[(int)game->pos.y][(int)(game->pos.x + game->dir.x * MOV_SPEED)] == '0')
	  		game->pos.x += game->dir.x * MOV_SPEED;
		if(game->map[(int)(game->pos.y + game->dir.y * MOV_SPEED)][(int)game->pos.x] == '0')
	  		game->pos.y += game->dir.y * MOV_SPEED;
	}
    if (mov_dir == MLX_KEY_S)
    {
		if(game->map[(int)game->pos.y][(int)(game->pos.x - game->dir.x * MOV_SPEED)] == '0')
	  		game->pos.x -= game->dir.x * MOV_SPEED;
		if(game->map[(int)(game->pos.y - game->dir.y * MOV_SPEED)][(int)game->pos.x] == '0')
			game->pos.y -= game->dir.y * MOV_SPEED;
    }

}
void	ft_key_hook(mlx_key_data_t keydata, void* param)
{
	t_game *game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		ft_move(MLX_KEY_W, game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		ft_move(MLX_KEY_S, game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->pos.x -= 0.1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->pos.x += 0.1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		ft_rotate(LEFT, game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		ft_rotate(RIGHT, game);
	raycasting(game);
}

int	main(int argc, char **argv)
{
	t_game *game;

	if (argc != 2)
		handle_error("Wrong number of arguments", NULL);
	game = init_game();
	parse_file(game, argv[1]);

	// MLX allows you to define its core behaviour before startup.
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();
	game->mlx = mlx;
	game->mlx_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_t* img = game->mlx_img;
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	raycasting(game);
	mlx_key_hook(mlx, &ft_key_hook, game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	destroy_game(game);
	return (EXIT_SUCCESS);
}
