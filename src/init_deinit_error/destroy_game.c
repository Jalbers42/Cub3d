/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:45:19 by jalbers           #+#    #+#             */
/*   Updated: 2023/10/12 13:11:50 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	delete_textures(t_game *game)
{
	if (game->no)
		mlx_delete_texture(game->no);
	if (game->so)
		mlx_delete_texture(game->so);
	if (game->we)
		mlx_delete_texture(game->we);
	if (game->ea)
		mlx_delete_texture(game->ea);
	if (game->door)
		mlx_delete_texture(game->door);
	if (game->door_wall_1)
		mlx_delete_texture(game->door_wall_1);
	if (game->door_wall_2)
		mlx_delete_texture(game->door_wall_2);
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
