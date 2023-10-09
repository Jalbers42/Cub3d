/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:37:46 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/09 16:25:21 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*ft_get_pix_col(int sprite_height, int hit, t_game *game)
{
	int		y;
	double	step;
	int		*pix_col;

	pix_col = malloc(ft_min(sprite_height, game->screen_height) * sizeof(int));
	if (!pix_col)
		return (NULL);
	if (sprite_height <= game->screen_height)
		step = 0;
	else
		step = (sprite_height - game->screen_height) / 2 * 1.0 \
		* game->sprite_text->height / sprite_height;
	y = 0;
	while (y < ft_min(sprite_height, game->screen_height))
	{
		pix_col[y] = ft_get_pixel(game->sprite_text, hit, (int)(step));
		step += 1.0 * game->sprite_text->height / sprite_height;
		y++;
	}
	return (pix_col);
}

static void	ft_draw_sprite(int x, double dist, t_rc_data *rc_data, t_game *game)
{
	int	*pix_col;
	int	y;

	pix_col = ft_get_pix_col(rc_data->line_height, \
	(int)(rc_data->text_hit + 0.5), game);
	y = 0;
	while (y < game->screen_height)
	{
		if (rc_data->start <= y && y < rc_data->end
			&& pix_col[y - rc_data->start] != 11141120)
			mlx_put_pixel(game->mlx_img, x, y, \
			ft_blur(pix_col[y - rc_data->start], dist));
		y++;
	}
	free(pix_col);
}

void	ft_sprite(int x, t_rc_data *rc_data, t_game *game)
{
	t_vector	inter;
	double		d_is;
	double		d_sp;

	inter = ft_intersect(game->sprite_pos, game->plane, game->pos, \
	rc_data->ray);
	d_is = ft_dist(inter, game->sprite_pos);
	d_sp = ft_dist(game->sprite_pos, game->pos);
	if (game->sprite_width / 2 <= d_is
		|| rc_data->perpWallDist < d_sp
		|| ft_vect_dir(rc_data->ray, game->pos, inter) != 1)
		return ;
	rc_data->line_height = (int)((game->screen_height) / d_sp);
	rc_data->end = (game->screen_height + rc_data->line_height) / 2;
	if (game->screen_height < rc_data->end)
		rc_data->end = game->screen_height;
	rc_data->start = rc_data->end - rc_data->line_height;
	if (rc_data->end == game->screen_height)
		rc_data->start = 0;
	if (0 <= ft_vect_dir(game->plane, inter, game->sprite_pos))
		rc_data->text_hit = game->sprite_width / 2 - d_is;
	else
		rc_data->text_hit = game->sprite_width / 2 + d_is;
	rc_data->text_hit *= game->sprite_text->width / game->sprite_width;
	ft_draw_sprite(x, d_sp, rc_data, game);
}
