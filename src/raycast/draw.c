/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:53:58 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/12 13:11:50 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	double	wall_hit;

	if (rc_data->side == 0)
		wall_hit = game->pos.y + rc_data->perp_wall_dist * rc_data->ray.y;
	else
		wall_hit = game->pos.x + rc_data->perp_wall_dist * rc_data->ray.x;
	wall_hit -= (int)(wall_hit);
	rc_data->text_hit = (wall_hit * rc_data->text->width);
}

int	ft_get_pixel(mlx_texture_t *texture, int x, int y)
{
	int	offset;

	if ((int)texture->width <= x)
		x = texture->width - 1;
	if ((int)texture->height <= y)
		y = texture->height - 1;
	offset = (y * texture->width + x) * texture->bytes_per_pixel;
	return (texture->pixels[offset] << 24 | \
	texture->pixels[offset + 1] << 16 | texture->pixels[offset + 2] << 8 \
	| texture->pixels[offset + 3]);
}

int	*ft_get_pix_col(t_rc_data *rc_data, t_game *game)
{
	int		y;
	double	step;
	int		*pix_col;

	pix_col = malloc(ft_min(rc_data->line_height, game->screen_height) \
	* sizeof(int));
	if (!pix_col)
		return (NULL);
	if (rc_data->line_height <= game->screen_height)
		step = 0;
	else
		step = (rc_data->line_height - game->screen_height) / 2 \
		* 1.0 * rc_data->text->height / rc_data->line_height;
	y = 0;
	while (y < ft_min(rc_data->line_height, game->screen_height))
	{
		pix_col[y] = ft_get_pixel(rc_data->text, rc_data->text_hit, \
		(int)(step + 0.5));
		step += 1.0 * rc_data->text->height / rc_data->line_height;
		y++;
	}
	return (pix_col);
}

void	ft_draw_line(int x, t_rc_data *rc_data, t_game *game)
{
	int	y;
	int	*text_col;

	ft_set_start_end(rc_data, game);
	ft_set_text(rc_data, game);
	ft_text_hit(rc_data, game);
	text_col = ft_get_pix_col(rc_data, game);
	y = 0;
	while (y < game->screen_height)
	{
		if (y < rc_data->start)
			ft_draw_sky(x, &y, game, rc_data);
		if (rc_data->end <= y)
			mlx_put_pixel(game->mlx_img, x, y, game->f_color);
		else
			mlx_put_pixel(game->mlx_img, x, y, \
			ft_blur(text_col[y - rc_data->start], rc_data->perp_wall_dist));
		y++;
	}
	free(text_col);
}
