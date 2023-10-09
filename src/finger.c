/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:32 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/08 22:52:19 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_finger(int finger, t_game *game)
{
	unsigned int	x;
	unsigned int	y;
	mlx_texture_t	*text;

	if (finger == 0)
		return ;
	if (finger == MLX_KEY_N)
	{
		x = 0;
		text = mlx_load_png("./textures/middle_left.png");
		while (x < text->width)
		{
			y = 0;
			while (y < text->height)
			{
				if (ft_get_pixel(text, x, y) != 0)
					mlx_put_pixel(game->mlx_img, x + 275, y + 350, ft_get_pixel(text, x, y));
				y++;
			}
			x++;
		}
	}
	if (finger == MLX_KEY_M)
	{
		x = 0;
		text = mlx_load_png("./textures/middle_right.png");
		while (x < text->width)
		{
			y = 0;
			while (y < text->height)
			{
				//printf("%i ", ft_get_pixel(text, x, y));
				if (ft_get_pixel(text, x, y) != 0 && ft_get_pixel(text, x, y) != 1077952516 && ft_get_pixel(text, x, y) != -2147483646 && ft_get_pixel(text, x, y) != 1431655683)
					mlx_put_pixel(game->mlx_img, x + 475, y + 350, ft_get_pixel(text, x, y));
				y++;
			}
			x++;
			//printf("\n\n\n");
		}
	}
}
