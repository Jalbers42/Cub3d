/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/27 20:22:03 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
// static void ft_hook(void* param)
// {
// 	const mlx_t* mlx = param;

// 	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }

int	main(int argc, char **argv)
{
	t_game *game;

	if (argc != 2)
		handle_error("Wrong number of arguments", NULL);
	game = init_game();
	parse_file(game, argv[1]);
	//raycasting(game);


	// MLX allows you to define its core behaviour before startup.
	//mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	//mlx_image_t* img;
	game->mlx_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_t* img = game->mlx_img;
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    //memset(img->pixels, 255, img->width * img->height * BPP);
	// Even after the image is being displayed, we can still modify the buffer.
	//mlx_put_pixel(img, 20, 100, RED);
	raycasting(game);
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	//mlx_loop_hook(mlx, ft_hook, mlx);
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	destroy_game(game);
	return (EXIT_SUCCESS);
}