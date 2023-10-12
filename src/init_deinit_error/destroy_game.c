/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:45:19 by jalbers           #+#    #+#             */
/*   Updated: 2023/10/12 12:02:05 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	delete_textures(t_game *game)
{
	if (game->NO)
		mlx_delete_texture(game->NO);
	if (game->SO)
		mlx_delete_texture(game->SO);
	if (game->WE)
		mlx_delete_texture(game->WE);
	if (game->EA)
		mlx_delete_texture(game->EA);
	if (game->DOOR)
		mlx_delete_texture(game->DOOR);
	if (game->DOOR_WALL_1)
		mlx_delete_texture(game->DOOR_WALL_1);
	if (game->DOOR_WALL_2)
		mlx_delete_texture(game->DOOR_WALL_2);
	if (game->finger_left_text)
		mlx_delete_texture(game->finger_left_text);
	if (game->finger_right_text)
		mlx_delete_texture(game->finger_right_text);
	if (game->game_over_text)
		mlx_delete_texture(game->game_over_text);
}

void	delete_sprite(t_game *game)
{
	if (game->sprite_text1)
		mlx_delete_texture(game->sprite_text1);
	if (game->sprite_text2)
		mlx_delete_texture(game->sprite_text2);
	if (game->sprite_text3)
		mlx_delete_texture(game->sprite_text3);
}

void	destroy_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->file_content != NULL)
		free(game->file_content);
	if (game->tokens != NULL)
		free(game->tokens);
	if (game->map != NULL)
		free_map(game, game->map);
	if (game->mlx)
		mlx_delete_image(game->mlx, game->mlx_img);
	delete_textures(game);
	delete_sprite(game);
	if (game->sky_box)
	{
		i = 0;
		while (i < (int)game->sky_text->width)
			free(game->sky_box[i++]);
		free(game->sky_box);
		mlx_delete_texture(game->sky_text);
	}
	if (game->mlx)
		mlx_terminate(game->mlx);
	free(game);
}
