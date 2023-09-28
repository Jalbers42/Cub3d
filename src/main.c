/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/28 11:20:29 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	ft_key_hook(mlx_key_data_t keydata, void* param)
{
	t_game *game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->pos.y += 0.1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->pos.y -= 0.1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->pos.x -= 0.1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->pos.x += 0.1;
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
