/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:15:48 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/12 13:14:17 by jalbers          ###   ########.fr       */
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
		return (NULL);
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

static void	ft_init_sprite(t_game *game)
{
	game->sprite_width = 1;
	game->sprite_text1 = mlx_load_png("./textures/spriteA.png");
	game->sprite_text2 = mlx_load_png("./textures/spriteB.png");
	game->sprite_text3 = mlx_load_png("./textures/spriteE.png");
	game->sprite_text = game->sprite_text1;
}

static void	ft_init_sky(t_game *game)
{
	int	x;

	game->sky_text = mlx_load_png("./textures/sky4.png");
	game->sky_box = malloc(game->sky_text->width * sizeof(int *));
	x = 0;
	while (x < (int)game->sky_text->width)
	{
		game->sky_box[x] = ft_get_pix_col(game->sky_text, x, game);
		x++;
	}
}

void	init_textures(t_game *game)
{
	game->no = NULL;
	game->so = NULL;
	game->we = NULL;
	game->ea = NULL;
	game->door = NULL;
	game->door_wall_1 = NULL;
	game->door_wall_2 = NULL;
	game->sprite_text1 = NULL;
	game->sprite_text2 = NULL;
	game->sprite_text3 = NULL;
	game->finger_left_text = NULL;
	game->finger_right_text = NULL;
	game->game_over_text = NULL;
}

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	game->mlx = NULL;
	game->map = NULL;
	game->tokens = NULL;
	game->file_content = NULL;
	game->player_pos_count = 0;
	game->screen_width = WIDTH;
	game->screen_height = HEIGHT;
	game->mouse_pos.x = WIDTH / 2;
	game->mouse_pos.y = HEIGHT / 2;
	game->finished = false;
	game->counter = 0;
	init_textures(game);
	ft_init_sprite(game);
	ft_init_sky(game);
	game->game_over_text = mlx_load_png("./textures/game_over2.png");
	game->finger = 0;
	game->finger_left_text = mlx_load_png("./textures/middle_left.png");
	game->finger_right_text = mlx_load_png("./textures/middle_right.png");
	return (game);
}
