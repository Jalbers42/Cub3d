/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Jalbers42                                         #+#    #+#             */
/*   https://github.com/Jalbers42                     ###   ###########       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

int	set_rgb(t_game *game, t_rgb *color, char *str)
{
	char	**tokens;

	tokens = malloc(sizeof(char *) * 3);
	if (!insert_tokens(tokens, str, ',', 3))
	{
		free (tokens);
		return (0);
	}
	color->r = ft_atoi(tokens[0]);
	color->g = ft_atoi(tokens[1]);
	color->b = ft_atoi(tokens[2]);
	color->a = 255;
	free(tokens);
	if (color->r < 0 || color->r > 255 || color->g < 0 
		|| color->g > 255 || color->b < 0 || color->b > 255)
	{
		handle_error("Wrong RGB value", game);
		return (1);
	}
	return (0);
}

void	set_texture(t_game *game, mlx_texture_t	**texture, char *path)
{
	*texture = mlx_load_png(path);
	if (!*texture)
		handle_error("Error opening texture PNG.", game);
}
