/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:15:48 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/06 20:54:39 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double ft_rad_to_deg(double radians)
{
    return radians * (180.0 / M_PI);
}

double	ft_vect_to_angle(t_vector vector)
{
    double	angle_rad = atan2(vector.y, vector.x);
    return (ft_rad_to_deg(angle_rad) + 180);
}
t_rc_data	*ft_init_rc(int x, t_game *game)
{
	t_rc_data *rc_data;
	rc_data = malloc(sizeof(t_rc_data));
	//calculate x coordinate in camera space
	rc_data->cam_x = 2 * x / (double)game->screen_width - 1;
	//calculate ray position and direction
	rc_data->ray.x = game->dir.x + game->plane.x * rc_data->cam_x;
	rc_data->ray.y = game->dir.y + game->plane.y * rc_data->cam_x;
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
	int hit = 0;
	int	wall = 0;

	if (get_player_block(game) == 2)
		wall++;
	while(hit != 1)
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
		if(game->map[(int)rc_data->field.y][(int)rc_data->field.x] == 2)
			wall++;
		else
			wall = 0;
		//Check if ray has hit a wall
		if(game->map[(int)rc_data->field.y][(int)rc_data->field.x] == 1 || wall == 2) //maybe adjust depending on the type of map
			hit = 1;
	}
}

void	ft_line_height(t_rc_data *rc_data, t_game *game)
{	
	if(rc_data->side == 0)
		rc_data->perpWallDist = rc_data->side_dist.x - rc_data->d_side_dist.x;
	else          
		rc_data->perpWallDist = rc_data->side_dist.y - rc_data->d_side_dist.y;
	rc_data->line_height = (int)(game->screen_height / rc_data->perpWallDist + 0.5);
}

int	ft_get_pixel(mlx_texture_t* texture, int x, int y)
{
	int	offset;
	
	if ((int)texture->width <= x)
		x = texture->width - 1;
	if ((int)texture->height <= y)
		y = texture->height - 1;
	offset = (y * texture->width + x) * texture->bytes_per_pixel;
    return (texture->pixels[offset] << 24 | texture->pixels[offset + 1] << 16 | texture->pixels[offset + 2] << 8 | texture->pixels[offset + 3]);
}

int	ft_min(int	a, int b)
{
	if (a < b)
		return (a);
	else
		return b;
}

// Function to get a column x of pixels from texture
int	*ft_get_pix_col(t_rc_data *rc_data, t_game *game)
{
	int		y;
	double	step;
	int		*pix_col;

	pix_col = malloc(ft_min(rc_data->line_height, game->screen_height) * sizeof(int));
	if (!pix_col)
        return NULL;
	if (rc_data->line_height <= game->screen_height)
		step = 0;
	else
		step = (rc_data->line_height - game->screen_height) / 2 * 1.0 * rc_data->text->height / rc_data->line_height;
	y = 0;
	while (y < ft_min(rc_data->line_height, game->screen_height))
	{
		pix_col[y] = ft_get_pixel(rc_data->text, rc_data->text_hit, (int)(step + 0.5));
		step += 1.0 * rc_data->text->height / rc_data->line_height;
		y++;
	}
	return (pix_col);
}

void	ft_set_start_end(t_rc_data *rc_data, t_game *game)
{
	rc_data->start = (game->screen_height - rc_data->line_height) / 2;
	if (rc_data->start < 0)
		rc_data->start = 0;
	rc_data->end = (rc_data->line_height + game->screen_height) / 2;
	if (game->screen_height < rc_data->end)
		rc_data->end = game->screen_height;	
}

void	ft_text_hit(t_rc_data *rc_data, t_game *game)
{
	double wall_hit;

	if (rc_data->side == 0)
		wall_hit = game->pos.y + rc_data->perpWallDist * rc_data->ray.y;
	else
		wall_hit = game->pos.x + rc_data->perpWallDist * rc_data->ray.x;
	wall_hit -= (int)(wall_hit);
	//x coordinate on the texture
	rc_data->text_hit = (wall_hit * rc_data->text->width);
}

// int	is_door_wall(t_game *game, t_rc_data *rc_data)
// {
// 	int	bordering_block;
// 	if (0.0 <= rc_data->ray.x && 0.0 <= rc_data->ray.y)
// 	{

// 	}
// 		else if (rc_data->ray.x <= 0.0 && 0.0 <= rc_data->ray.y)
// 		{

// 		}
		
// 	int	x = rc_data->field.x;
// 	int	y = rc_data->field.y;

// 	if (game->map[y + 1][x] == )
// }

static void	ft_set_text(t_rc_data *rc_data, t_game *game)
{
	if(game->map[(int)rc_data->field.y][(int)rc_data->field.x] == 2)
		rc_data->text = game->DOOR;

	// else if(game->map[(int)rc_data->field.y][(int)rc_data->field.x + 1] == 2 && rc_data->side == 0)
	// else if (is_door_wall(game, rc_data))
	// 	rc_data->text = game->DOOR_WALL_1;

	//1. Quadrant
	else if (0.0 <= rc_data->ray.x && 0.0 <= rc_data->ray.y)
	{
		if (rc_data->side == 1)
		{
			if (game->map[(int)rc_data->field.y - 1][(int)rc_data->field.x] >= 2)
				rc_data->text = game->DOOR_WALL_2;
			else
				rc_data->text = game->NO;
		}
		if (rc_data->side == 0)
		{
			if (game->map[(int)rc_data->field.y][(int)rc_data->field.x - 1] >= 2)
				rc_data->text = game->DOOR_WALL_1;
			else
				rc_data->text = game->WE;
		}
	}
	//2. Quadrant
	else if (rc_data->ray.x <= 0.0 && 0.0 <= rc_data->ray.y)
	{
		if (rc_data->side == 1)
		{
			if (game->map[(int)rc_data->field.y - 1][(int)rc_data->field.x] >= 2)
				rc_data->text = game->DOOR_WALL_2;
			else
				rc_data->text = game->NO;
		}
		if (rc_data->side == 0)
		{
			if (game->map[(int)rc_data->field.y][(int)rc_data->field.x + 1] >= 2)
				rc_data->text = game->DOOR_WALL_2;
			else
				rc_data->text = game->EA;
		}
	}
	//3. Quadrant 
	else if (rc_data->ray.x <= 0.0 && rc_data->ray.y <= 0.0)
	{
		if (rc_data->side == 1)
		{
			if (game->map[(int)rc_data->field.y + 1][(int)rc_data->field.x] >= 2)
				rc_data->text = game->DOOR_WALL_1;
			else
				rc_data->text = game->SO;
		}
		if (rc_data->side == 0)
		{
			if (game->map[(int)rc_data->field.y][(int)rc_data->field.x + 1] >= 2)
				rc_data->text = game->DOOR_WALL_2;
			else
				rc_data->text = game->EA;
		}
	}
	//4. Quadrant 
	else if(0.0 <= rc_data->ray.x && rc_data->ray.y <= 0.0)
	{
		if (rc_data->side == 1)
		{
			if (game->map[(int)rc_data->field.y + 1][(int)rc_data->field.x] >= 2)
				rc_data->text = game->DOOR_WALL_1;
			else
				rc_data->text = game->SO;
		}
		if (rc_data->side == 0)
		{
			if (game->map[(int)rc_data->field.y][(int)rc_data->field.x - 1] >= 2)
				rc_data->text = game->DOOR_WALL_1;
			else
				rc_data->text = game->WE;
		}
	}
}

void	ft_draw_sky(int x, int *y, t_game *game, t_rc_data *rc_data)
{
	int *col;
	int	pos;

	pos = (int)(ft_vect_to_angle(rc_data->ray) * game->sky_text->width / 360);
	col = game->sky_box[pos];
	while (*y < rc_data->start)
	{
		mlx_put_pixel(game->mlx_img, x, *y, game->sky_box[pos][*y]);
		*y += 1;
	}
}

t_rgb ft_get_rgba(int color) 
{
	t_rgb rgba;

    rgba.r = (color >> 24) & 0xFF;  // Red
    rgba.g = (color >> 16) & 0xFF;  // Green
    rgba.b = (color >> 8) & 0xFF;   // Blue
    rgba.a = color & 0xFF;          // Alpha
	return (rgba);
}

int	ft_blur(int color, t_rc_data *rc_data)
{
	t_rgb	rgba;
	double	darkness;

	if (rc_data->perpWallDist < 5)
		return (color);
	rgba = ft_get_rgba(color);
	darkness = 5 / rc_data->perpWallDist;
	color = (int)(rgba.r * darkness) << 24 | (int)(rgba.g * darkness) << 16 | (int)(rgba.b * darkness) << 8 | rgba.a;
	return (color);
}

void	ft_draw_line(int x, t_rc_data *rc_data, t_game *game)
{
	int	y;
	int	*text_col;

	//calculate start end end of the wall
	ft_set_start_end(rc_data, game);
	//find the correct texture
	ft_set_text(rc_data, game);
	//calculate where exactly the wall was hit and where it is on the texture
	ft_text_hit(rc_data, game);
	//get the correct column of the texture
	text_col = ft_get_pix_col(rc_data, game);
	y = 0;
	while (y < game->screen_height)
	{
		if (y < rc_data->start)
			ft_draw_sky(x, &y, game, rc_data);
			//mlx_put_pixel(game->mlx_img, x, y, game->c_color);
		if (rc_data->end <= y)
			mlx_put_pixel(game->mlx_img, x, y, game->f_color);
		else
			mlx_put_pixel(game->mlx_img, x, y, ft_blur(text_col[y - rc_data->start], rc_data));
		y++;
	}
	free(text_col);
}

void	raycasting(t_game *game)
{
	t_rc_data	*rc_data;
	int			x;

	mlx_image_t *temp_img = game->mlx_img;
	game->mlx_img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
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
		ft_sprite(x, rc_data, game);
		free(rc_data);
		x++;
	}
	minimap(game);
	mlx_delete_image(game->mlx, temp_img);
	mlx_image_to_window(game->mlx, game->mlx_img, 0, 0);
}
