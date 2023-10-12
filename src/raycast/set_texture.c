/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:48:41 by ycardona          #+#    #+#             */
/*   Updated: 2023/10/12 13:11:50 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_first(t_game *game, t_rc_data *rc_data)
{
	if (rc_data->side == 1)
	{
		if (game->map[(int)rc_data->field.y - 1][(int)rc_data->field.x] >= 2)
			rc_data->text = game->door_wall_2;
		else
			rc_data->text = game->no;
	}
	if (rc_data->side == 0)
	{
		if (game->map[(int)rc_data->field.y][(int)rc_data->field.x - 1] >= 2)
			rc_data->text = game->door_wall_1;
		else
			rc_data->text = game->we;
	}
}

static void	ft_second(t_game *game, t_rc_data *rc_data)
{
	if (rc_data->side == 1)
	{
		if (game->map[(int)rc_data->field.y - 1][(int)rc_data->field.x] >= 2)
			rc_data->text = game->door_wall_2;
		else
			rc_data->text = game->no;
	}
	if (rc_data->side == 0)
	{
		if (game->map[(int)rc_data->field.y][(int)rc_data->field.x + 1] >= 2)
			rc_data->text = game->door_wall_2;
		else
			rc_data->text = game->ea;
	}
}

static void	ft_third(t_game *game, t_rc_data *rc_data)
{
	if (rc_data->side == 1)
	{
		if (game->map[(int)rc_data->field.y + 1][(int)rc_data->field.x] >= 2)
			rc_data->text = game->door_wall_1;
		else
			rc_data->text = game->so;
	}
	if (rc_data->side == 0)
	{
		if (game->map[(int)rc_data->field.y][(int)rc_data->field.x + 1] >= 2)
			rc_data->text = game->door_wall_2;
		else
			rc_data->text = game->ea;
	}
}

static void	ft_fourth(t_game *game, t_rc_data *rc_data)
{
	if (rc_data->side == 1)
	{
		if (game->map[(int)rc_data->field.y + 1][(int)rc_data->field.x] >= 2)
			rc_data->text = game->door_wall_1;
		else
			rc_data->text = game->so;
	}
	if (rc_data->side == 0)
	{
		if (game->map[(int)rc_data->field.y][(int)rc_data->field.x - 1] >= 2)
			rc_data->text = game->door_wall_1;
		else
			rc_data->text = game->we;
	}
}

void	ft_set_text(t_rc_data *rc_data, t_game *game)
{
	if (game->map[(int)rc_data->field.y][(int)rc_data->field.x] == 2)
		rc_data->text = game->door;
	else if (0.0 <= rc_data->ray.x && 0.0 <= rc_data->ray.y)
		ft_first(game, rc_data);
	else if (rc_data->ray.x <= 0.0 && 0.0 <= rc_data->ray.y)
		ft_second(game, rc_data);
	else if (rc_data->ray.x <= 0.0 && rc_data->ray.y <= 0.0)
		ft_third(game, rc_data);
	else if (0.0 <= rc_data->ray.x && rc_data->ray.y <= 0.0)
		ft_fourth(game, rc_data);
}
