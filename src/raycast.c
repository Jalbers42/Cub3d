/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:15:48 by ycardona          #+#    #+#             */
/*   Updated: 2023/09/27 14:24:05 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_game *game)
{
	/* double posX = 22, posY = 12;  //x and y start position
 	double dirX = -1, dirY = 0; //initial direction vector
  	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame */

	//screen(screenWidth, screenHeight, 0, "Raycaster");

	while(1)
	{
		for(int x = 0; x < game->map_width; x++)
		{
	  		//calculate ray position and direction
			t_vector	ray_dir;	
			double	cameraX = 2 * x / (double)game->map_width - 1; //x-coordinate in camera space
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
				if(game->map[mapX][mapY] != '0') //maybe adjust depending on the type of map
					hit = 1;
			}
	  
	  //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
	  //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
	  //This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
	  //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
	  //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
	  //steps, but we subtract deltaDist once because one step more into the wall was taken above.
	  
			if(side == 0)
				perpWallDist = side_dist.x - d_side_dist.x;
			else          
				perpWallDist = side_dist.y - d_side_dist.y;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(game->map_height / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + game->map_height / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + game->map_height / 2;
			if(drawEnd >= game->map_height)
				drawEnd = game->map_height - 1;

			//choose wall color
			ColorRGB color;
			switch(worldMap[mapX][mapY])
			{
				case 1:  color = RGB_Red;    break; //red
				case 2:  color = RGB_Green;  break; //green
				case 3:  color = RGB_Blue;   break; //blue
				case 4:  color = RGB_White;  break; //white
				default: color = RGB_Yellow; break; //yellow
			}

			//give x and y sides different brightness
			if(side == 1) {color = color / 2;}

			//draw the pixels of the stripe as a vertical line
			verLine(x, drawStart, drawEnd, color);
	}
	//timing for input and FPS counter
	oldTime = time;
	time = getTicks();
	double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	print(1.0 / frameTime); //FPS counter
	redraw();
	cls();

	//speed modifiers
	double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
	double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
	readKeys();
	//move forward if no wall in front of you
	if(keyDown(SDLK_UP))
	{
	  if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
	  if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if(keyDown(SDLK_DOWN))
	{
	  if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
	  if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}
	//rotate to the right
	if(keyDown(SDLK_RIGHT))
	{
	  //both camera direction and camera plane must be rotated
	  double oldDirX = dirX;
	  dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	  dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	  double oldPlaneX = planeX;
	  planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	  planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	//rotate to the left
	if(keyDown(SDLK_LEFT))
	{
	  //both camera direction and camera plane must be rotated
	  double oldDirX = dirX;
	  dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	  dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	  double oldPlaneX = planeX;
	  planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	  planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
  }
}
