/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:45:00 by jalbers           #+#    #+#             */
/*   Updated: 2023/10/11 14:45:01 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_left(t_game *game)
{
	mlx_texture_t	*text;
	unsigned int	x;
	unsigned int	y;

	x = 0;
	text = game->finger_left_text;
	while (x < text->width)
	{
		y = 0;
		while (y < text->height)
		{
			if (ft_get_pixel(text, x, y) != 0)
				mlx_put_pixel(game->mlx_img, x + game->screen_width / 3, \
				y + game->screen_height - text->height, ft_get_pixel(text, x, y));
			y++;
		}
		x++;
	}
}

void	ft_draw_right(t_game *game)
{
	mlx_texture_t	*text;
	unsigned int	x;
	unsigned int	y;

	x = 0;
	text = game->finger_right_text;
	while (x < text->width)
	{
		y = 0;
		while (y < text->height)
		{
			if (ft_get_pixel(text, x, y) != 0)
				mlx_put_pixel(game->mlx_img, x + game->screen_width * 2 / 3 - text->width, \
				y + game->screen_height - text->height, ft_get_pixel(text, x, y));
			y++;
		}
		x++;
	}
}

void	ft_finger(int finger, t_game *game)
{
	if (finger == 0)
		return ;
	if (finger == MLX_KEY_N)
		ft_draw_left(game);
	if (finger == MLX_KEY_M)
		ft_draw_right(game);
}
