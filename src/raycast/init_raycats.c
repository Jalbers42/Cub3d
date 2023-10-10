/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:03:41 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/10 14:27:03 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_ray(int x, t_game *game, t_rc_data *rc_data)
{
	rc_data->cam_x = 2 * x / (double)game->screen_width - 1;
	rc_data->ray.x = game->dir.x + game->plane.x * rc_data->cam_x;
	rc_data->ray.y = game->dir.y + game->plane.y * rc_data->cam_x;
}

static void	ft_init_side_d(t_game *game, t_rc_data *rc_data)
{
	if (rc_data->ray.x < 0)
	{
		rc_data->step.x = -1;
		rc_data->side_dist.x = (game->pos.x - rc_data->field.x) \
		* rc_data->d_side_dist.x;
	}
	else
	{
		rc_data->step.x = 1;
		rc_data->side_dist.x = (rc_data->field.x + 1.0 - game->pos.x) \
		* rc_data->d_side_dist.x;
	}
	if (rc_data->ray.y < 0)
	{
		rc_data->step.y = -1;
		rc_data->side_dist.y = (game->pos.y - rc_data->field.y) \
		* rc_data->d_side_dist.y;
	}
	else
	{
		rc_data->step.y = 1;
		rc_data->side_dist.y = (rc_data->field.y + 1.0 - game->pos.y) \
		* rc_data->d_side_dist.y;
	}
}

t_rc_data	*ft_init_rc(int x, t_game *game)
{
	t_rc_data	*rc_data;

	rc_data = malloc(sizeof(t_rc_data));
	ft_init_ray(x, game, rc_data);
	if (rc_data->ray.x == 0)
		rc_data->d_side_dist.x = 2; //1e30;
	else
		rc_data->d_side_dist.x = fabs(1 / rc_data->ray.x);
	if (rc_data->ray.y == 0)
		rc_data->d_side_dist.y = 2; //1e30;
	else
		rc_data->d_side_dist.y = fabs(1 / rc_data->ray.y);
	rc_data->field.x = (int)(game->pos.x);
	rc_data->field.y = (int)(game->pos.y);
	ft_init_side_d(game, rc_data);
	return (rc_data);
}
