/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:15:48 by ycardona          #+#    #+#             */
/*   Updated: 2023/09/27 20:35:54 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(int x, int start, int end, int side, t_game *game)
{
	int	y;

	y = 0;
	int color = RED;
	if (side == 1)
		color = LIGHT_RED;
	while (y < game->screen_height)
	{
		if (y < start)
			mlx_put_pixel(game->mlx_img, x, y, BLUE);
		else if (end < y)
			mlx_put_pixel(game->mlx_img, x, y, BROWN);
		else
			mlx_put_pixel(game->mlx_img, x, y, color);
		y++;
	}
	
}

void	raycasting(t_game *game)
{
	/* double posX = 22, posY = 12;  //x and y start position
 	double dirX = -1, dirY = 0; //initial direction vector
  	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame */

	//screen(screenWidth, screenHeight, 0, "Raycaster");
	game->map_width = 25;
	game->map_height = 10;
	game->screen_width = WIDTH;
	game->screen_height = HEIGHT;
	game->plane.x = 0;
	game->plane.y = 0.66;
	game->pos.x = 10;
	game->pos.y = 2;
	game->dir.x = -1;
	game->dir.y = 0;
	for(int x = 0; x < game->screen_width; x++)
	{
		//calculate ray position and direction
		t_vector	ray_dir;	
		double	cameraX = 2 * x / (double)game->screen_width - 1; //x-coordinate in camera space
		ray_dir.x = game->dir.x + game->plane.x * cameraX;
		ray_dir.y =	game->dir.y + game->plane.y * cameraX;
		//which box of the map we're in

		int mapX = (int)(game->pos.x);
		int mapY = (int)(game->pos.y);

		t_vector	side_dist;
		t_vector	d_side_dist;
		if (ray_dir.x == 0)
			d_side_dist.x = 1e30; //prevent divion with zero
		else
			d_side_dist.x = fabs(1 / ray_dir.x);
		if (ray_dir.y == 0)
			d_side_dist.y = 1e30;
		else
			d_side_dist.y = fabs(1 / ray_dir.y);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		
		//calculate step and initial sideDist
		if(ray_dir.x < 0)
		{
			stepX = -1;
			side_dist.x = (game->pos.x - mapX) * d_side_dist.x;
		}
		else
		{
			stepX = 1;
			side_dist.x = (mapX + 1.0 - game->pos.x) * d_side_dist.x;
		}

		if(ray_dir.y < 0)
		{
			stepY = -1;
			side_dist.y = (game->pos.y - mapY) * d_side_dist.y;
		}
		
		else
		{
			stepY = 1;
			side_dist.y = (mapY + 1.0 - game->pos.y) * d_side_dist.y;
		}
		//perform DDA
		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(side_dist.x < side_dist.y)
			{
				side_dist.x += d_side_dist.x;
				mapX += stepX;
				side = 0;
			}
			else
			{
				side_dist.y += d_side_dist.y;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(game->map[mapY][mapX] != '0') //maybe adjust depending on the type of map
				hit = 1;
		}
		if(side == 0)
			perpWallDist = side_dist.x - d_side_dist.x;
		else          
			perpWallDist = side_dist.y - d_side_dist.y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(game->screen_height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int start = -lineHeight / 2 + game->screen_height / 2;
		if (start < 0)
			start = 0;
		int end = lineHeight / 2 + game->screen_height / 2;
		if(end >= game->screen_height)
			end = game->screen_height - 1;	
		draw_line(x, start, end, side, game);
	}
  }