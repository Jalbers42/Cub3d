/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:58:30 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/10 14:03:00 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	ft_rad_to_deg(double radians)
{
	return (radians * (180.0 / M_PI));
}

static double	ft_vect_to_angle(t_vector vector)
{
	double	angle_rad;

	angle_rad = atan2(vector.y, vector.x);
	return (ft_rad_to_deg(angle_rad) + 180);
}

void	ft_draw_sky(int x, int *y, t_game *game, t_rc_data *rc_data)
{
	int	*col;
	int	pos;

	pos = (int)(ft_vect_to_angle(rc_data->ray) * game->sky_text->width / 360);
	if ((int)game->sky_text->width <= pos)
		pos -= game->sky_text->width;
	//printf("pos %i\n", pos);
	col = game->sky_box[pos];
	while (*y < rc_data->start)
	{
		mlx_put_pixel(game->mlx_img, x, *y, game->sky_box[pos][*y]);
		*y += 1;
	}
}
