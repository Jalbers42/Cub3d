/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:16:43 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/12 12:22:43 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_a(int rgba)
{
	int	alpha;

	alpha = (rgba >> 24) & 0xFF;
	return (alpha);
}

//checks if the vector of points p_a, p_b points in the same direction as vector
int	ft_vect_dir(t_vector vector, t_vector p_a, t_vector p_b)
{
	t_vector	ab;
	double		dot_prod;

	ab.x = p_b.x - p_a.x;
	ab.y = p_b.y - p_a.y;
	dot_prod = vector.x * ab.x + vector.y * ab.y;
	if (dot_prod > 0)
		return (1);
	else if (dot_prod < 0)
		return (-1);
	else
		return (0);
}

t_vector	ft_intersect(t_vector sprite_pos, t_vector plane, \
t_vector pos, t_vector ray)
{
	t_vector	intersect;
	double		m_1;
	double		m_2;

	m_1 = plane.y / plane.x;
	if (ray.x == 0)
		return (sprite_pos);
	else
		m_2 = ray.y / ray.x;
	intersect.x = (m_1 * sprite_pos.x - m_2 * pos.x + pos.y - sprite_pos.y) \
	/ (m_1 - m_2);
	intersect.y = m_1 * (intersect.x - sprite_pos.x) + sprite_pos.y;
	return (intersect);
}

double	ft_dist(t_vector p_a, t_vector p_b)
{
	return (sqrt(pow(p_b.x - p_a.x, 2) + pow(p_b.y - p_a.y, 2)));
}
