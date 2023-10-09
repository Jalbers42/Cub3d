/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:32 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/09 16:56:56 by ycardona         ###   ########.fr       */
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
				mlx_put_pixel(game->mlx_img, x + 275, y \
				+ 350, ft_get_pixel(text, x, y));
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
				mlx_put_pixel(game->mlx_img, x + 475, y \
				+ 350, ft_get_pixel(text, x, y));
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
