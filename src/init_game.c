/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/09 09:49:28 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*ft_get_pix_col(mlx_texture_t *text, int x, t_game *game)
{
	int		y;
	double	step;
	int		*pix_col;

	pix_col = malloc((game->screen_height / 2 + 1) * sizeof(int));
	if (!pix_col)
        return NULL;
	step = 0;
	y = 0;
	while (y <= game->screen_height / 2)
	{
		pix_col[y] = ft_get_pixel(text, x, (int)(step));
		step += 1.0 * text->height / (game->screen_height / 2 + 1);
		y++;
	}
	return (pix_col);
}

t_game  *init_game()
{
	t_game  *game;

	game = malloc(sizeof(t_game));
	game->map = NULL;
	game->tokens = NULL;
	game->player_pos_count = 0;
	game->screen_width = WIDTH;
	game->screen_height = HEIGHT;
	game->mouse_pos.x = WIDTH / 2;
	game->mouse_pos.y = HEIGHT / 2;
	game->finished = false;
	//sprite
	game->counter = 0;
	game->sprite_width = 1;
	game->sprite_text1 = mlx_load_png("./textures/spriteA.png");
	game->sprite_text2 = mlx_load_png("./textures/spriteB.png");
	game->sprite_text3 = mlx_load_png("./textures/spriteE.png");
	game->sprite_text = game->sprite_text1;
	//finger
	game->finger_left_text = mlx_load_png("./textures/middle_left.png");
	game->finger_right_text = mlx_load_png("./textures/middle_right.png");
	
	//sky
	game->sky_text = mlx_load_png("./textures/sky4.png");
	game->sky_box = malloc(game->sky_text->width * sizeof(int *));
	int	x = 0;
	while (x < (int)game->sky_text->width)
	{
		game->sky_box[x] = ft_get_pix_col(game->sky_text, x, game);
		x++;
	}
	return (game);
}