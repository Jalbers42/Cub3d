/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:37:46 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/06 20:55:38 by ycardona         ###   ########.fr       */
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

static int	*ft_get_pix_col(int sprite_height, int hit, t_game *game)
{
	int		y;
	double	step;
	int		*pix_col;

	pix_col = malloc(ft_min(sprite_height, game->screen_height) * sizeof(int));
	if (!pix_col)
        return NULL;
	if (sprite_height <= game->screen_height)
		step = 0;
	else
		step = (sprite_height - game->screen_height) / 2 * 1.0 * game->sprite_text->height / sprite_height;
	y = 0;
	while (y < ft_min(sprite_height, game->screen_height))
	{
		pix_col[y] = ft_get_pixel(game->sprite_text, hit, (int)(step));
		step += 1.0 * game->sprite_text->height / sprite_height;
		y++;
	}
	return (pix_col);
}
//checks if the vector of points p_a, p_b points in the same direction as vector
int ft_vect_dir(t_vector vector, t_vector p_a, t_vector p_b) 
{
    // Schritt 1: Berechne den Vektor AB
    t_vector ab;

    ab.x = p_b.x - p_a.x;
    ab.y = p_b.y - p_a.y;

    // Schritt 2: Berechne das Skalarprodukt v · AB
    double	dotProduct = vector.x * ab.x + vector.y * ab.y;

    // Schritt 3: Interpretiere das Ergebnis
    if (dotProduct > 0) {
        // v und AB zeigen in die gleiche Richtung
        return 1;
    } else if (dotProduct < 0) {
        // v und AB zeigen in entgegengesetzte Richtungen
        return -1;
    } else {
        // v und AB sind orthogonal (rechtwinklig zueinander)
        return 0;
    }
}

int	ft_get_a(int rgba)
{
	int alpha = (rgba >> 24) & 0xFF;
    return alpha;
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
	//check if the intersection point doesnt lie behind you
	if (ft_vect_dir(rc_data->ray, game->pos, inter) != 1)
		return ;
	//get perpwalldistance for sprite (which is distance pos - sprite_pos)
	//and check if its closer to perpwalldist
	sprite_dist = ft_dist(game->sprite_pos, game->pos);
	if (rc_data->perpWallDist < sprite_dist)
		return ;
	//calc height of sprite
	sprite_height = (int)((game->screen_height) / sprite_dist);
	//calc start/end for drawing
	
	int	end = (game->screen_height + sprite_height) / 2;
	if (game->screen_height < end)
		end = game->screen_height;
	int	start = end - sprite_height;
	if (end == game->screen_height)
		start = 0;
	//calc where texture is hit
	double	hit_text;
	if (0 <= ft_vect_dir(game->plane, inter, game->sprite_pos))
		hit_text = game->sprite_width / 2 - ft_dist(inter, game->sprite_pos);
	else
		hit_text = game->sprite_width / 2 + ft_dist(inter, game->sprite_pos);
	hit_text *= game->sprite_text->width / game->sprite_width;
	//get col of pixels
	int *pix_col = ft_get_pix_col(sprite_height, (int)(hit_text + 0.5), game);
	int	y = 0;
	while (y < game->screen_height)
	{
		if (start <= y && y < end && pix_col[y - start] !=-1744795393)
			mlx_put_pixel(game->mlx_img, x, y, pix_col[y - start]);
		y++;
	}
	free(pix_col);
}
