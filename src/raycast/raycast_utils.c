/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:57:54 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/09 16:16:30 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rgb	ft_get_rgba(int color)
{
	t_rgb	rgba;

	rgba.r = (color >> 24) & 0xFF;
	rgba.g = (color >> 16) & 0xFF;
	rgba.b = (color >> 8) & 0xFF;
	rgba.a = color & 0xFF;
	return (rgba);
}

int	ft_blur(int color, double dist)
{
	t_rgb	rgba;
	double	darkness;

	if (dist < 5)
		return (color);
	rgba = ft_get_rgba(color);
	darkness = 5 / dist;
	color = (int)(rgba.r * darkness) << 24 | (int)(rgba.g * darkness) << 16 \
	| (int)(rgba.b * darkness) << 8 | rgba.a;
	return (color);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
