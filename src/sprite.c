/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:37:46 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/04 16:31:13 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	ft_intersect(t_vector sprite_pos, t_vector plane, t_vector pos, t_vector ray)
{
	t_vector	intersect;
	double		m_1;
	double		m_2;

	if (plane.x == 0)
		plane.x = 1e30;
	m_1 = plane.y / plane.x;
	if (ray.x == 0)
		ray.x = 1e30;
	m_2 = ray.y / ray.x;
	intersect.x = (m_1 * sprite_pos.x - m_2 * pos.x + pos.y - sprite_pos.y) / (m_1 - m_2);
	intersect.y = m_1 * (intersect.x - sprite_pos.x) + sprite_pos.y;
	return (intersect);
}

double	ft_dist(t_vector p_a, t_vector p_b)
{
	return (sqrt(pow(p_b.x - p_a.x, 2) + pow(p_b.y - p_a.y, 2)));
}

void	ft_sprite(int x, t_rc_data *rc_data, t_game *game)
{
	t_vector	inter;
	double		sprite_dist;
	int			sprite_height;

	//calculate where ray intersects the plane of sprite
	inter = ft_intersect(game->sprite_pos, game->plane, game->pos, rc_data->ray);
	//check if the intersection point lies inside the width of sprite
	if (game->sprite_width / 2 <= ft_dist(inter, game->sprite_pos))
		return ;
	//get perpwalldistance for sprite (which is distance pos - sprite_pos)
	//and check if its closer to perpwalldist
	sprite_dist = ft_dist(game->sprite_pos, game->pos);
	if (rc_data->perpWallDist < sprite_dist)
		return ;
	//calc height of sprite
	sprite_height = (int)((game->screen_height) / sprite_dist - 0.5);
	//calc start/end for drawing
	int	start = game->screen_height / 2 - sprite_height * 1 / 3;
	if (rc_data->start < 0)
		rc_data->start = 0;
	int	end = game->screen_height / 2 + sprite_height * 2 / 3;
	if (game->screen_height < end)
		end = game->screen_height;
	int	y = 0;
	while (y < game->screen_height)
	{
		if (start <= y && y < end)
			mlx_put_pixel(game->mlx_img, x, y, RED);
		y++;
	}
}