/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:15:48 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/10 17:02:21 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_hit(int *wall, int *hit, t_game *game, t_rc_data *rc_data)
{
	if (game->map[(int)rc_data->field.y][(int)rc_data->field.x] == 2)
		*wall += 1;
	else
		*wall = 0;
	if (game->map[(int)rc_data->field.y][(int)rc_data->field.x] == 1 \
	|| *wall == 2)
		*hit = 1;
}

void	ft_dda(t_rc_data *rc_data, t_game *game)
{
	int	hit;
	int	wall;

	hit = 0;
	wall = 0;
	if (get_player_block(game) == 2)
		wall++;
	while (hit != 1)
	{
		if (rc_data->side_dist.x < rc_data->side_dist.y)
		{
			rc_data->side_dist.x += rc_data->d_side_dist.x;
			rc_data->field.x += rc_data->step.x;
			rc_data->side = 0;
		}
		else
		{
			rc_data->side_dist.y += rc_data->d_side_dist.y;
			rc_data->field.y += rc_data->step.y;
			rc_data->side = 1;
		}
		ft_hit(&wall, &hit, game, rc_data);
	}
}

void	ft_line_height(t_rc_data *rc_data, t_game *game)
{	
	if (rc_data->side == 0)
		rc_data->perpWallDist = rc_data->side_dist.x - rc_data->d_side_dist.x;
	else
		rc_data->perpWallDist = rc_data->side_dist.y - rc_data->d_side_dist.y;
	rc_data->line_height = (int)(game->screen_height / rc_data->perpWallDist \
	+ 0.5);
}

void	raycasting(t_game *game)
{
	t_rc_data	*rc_data;
	int			x;

	x = 0;
	while (x < game->screen_width)
	{
		rc_data = ft_init_rc(x, game);
		ft_dda(rc_data, game);
		ft_line_height(rc_data, game);
		ft_draw_line(x, rc_data, game);
		ft_sprite(x, rc_data, game);
		free(rc_data);
		x++;
	}
}
