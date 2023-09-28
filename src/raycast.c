/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:15:48 by ycardona          #+#    #+#             */
/*   Updated: 2023/09/28 10:24:27 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rc_data	*ft_init_rc(int x, t_game *game)
{
	t_rc_data *rc_data;
	rc_data = malloc(sizeof(t_rc_data));
	//calculate x coordinate in camera space
	rc_data->cam_x = 2 * x / (double)game->screen_width - 1;
	//calculate ray position and direction
	rc_data->ray.x = game->dir.x + game->plane.x * rc_data->cam_x;
	rc_data->ray.y =	game->dir.y + game->plane.y * rc_data->cam_x;
	//calculate initial d_side_dist
	if (rc_data->ray.x == 0)
		rc_data->d_side_dist.x = 1e30; //prevent divion with zero
	else
		rc_data->d_side_dist.x = fabs(1 / rc_data->ray.x);
	if (rc_data->ray.y == 0)
		rc_data->d_side_dist.y = 1e30;
	else
		rc_data->d_side_dist.y = fabs(1 / rc_data->ray.y);
	//calculate initial field on the map
	rc_data->field.x = (int)(game->pos.x);
	rc_data->field.y = (int)(game->pos.y);
	//calculate step and initial side_dist
	if(rc_data->ray.x < 0)
	{
		rc_data->step.x = -1;
		rc_data->side_dist.x = (game->pos.x - rc_data->field.x) * rc_data->d_side_dist.x;
	}
	else
	{
		rc_data->step.x = 1;
		rc_data->side_dist.x = (rc_data->field.x + 1.0 - game->pos.x) * rc_data->d_side_dist.x;
	}
	if(rc_data->ray.y < 0)
	{
		rc_data->step.y = -1;
		rc_data->side_dist.y = (game->pos.y - rc_data->field.y) * rc_data->d_side_dist.y;
	}
	else
	{
		rc_data->step.y = 1;
		rc_data->side_dist.y = (rc_data->field.y + 1.0 - game->pos.y) * rc_data->d_side_dist.y;
	}
	return (rc_data);
}

void	ft_dda(t_rc_data *rc_data, t_game *game)
{
	int hit; //was there a wall hit?

	hit = 0;
	while(hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if(rc_data->side_dist.x < rc_data->side_dist.y)
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
		//Check if ray has hit a wall
		if(game->map[(int)rc_data->field.y][(int)rc_data->field.x] != '0') //maybe adjust depending on the type of map
			hit = 1;
	}
}

void	ft_line_height(t_rc_data *rc_data, t_game *game)
{
	double	perpWallDist;
	
	if(rc_data->side == 0)
		perpWallDist = rc_data->side_dist.x - rc_data->d_side_dist.x;
	else          
		perpWallDist = rc_data->side_dist.y - rc_data->d_side_dist.y;
	rc_data->line_height = (int)(game->screen_height / perpWallDist);
}

void	ft_draw_line(int x, t_rc_data *rc_data, t_game *game)
{
	int	y;
	int start;
	int end;
	int color;

	start = -rc_data->line_height / 2 + game->screen_height / 2;
	if (start < 0)
		start = 0;
	end = rc_data->line_height / 2 + game->screen_height / 2;
	if(end >= game->screen_height)
		end = game->screen_height - 1;	
	y = 0;
	color = RED;
	if (rc_data->side == 1)
		color = LIGHT_RED;
	while (y < game->screen_height)
	{
		if (y < start)
			mlx_put_pixel(game->mlx_img, x, y, SKY);
		else if (end < y)
			mlx_put_pixel(game->mlx_img, x, y, FLOOR);
		else
			mlx_put_pixel(game->mlx_img, x, y, color);
		y++;
	}
}

void	raycasting(t_game *game)
{
	t_rc_data	*rc_data;
	int			x;

	x = 0;
	while(x < game->screen_width)
	{
		rc_data = ft_init_rc(x, game);
		//perform DDA to find wich field is hit
		ft_dda(rc_data, game);
		//calculate line_height
		ft_line_height(rc_data, game);
		//draw line
		ft_draw_line(x, rc_data, game);
		free(rc_data);
		x++;
	}
}