/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:09:15 by jalbers           #+#    #+#             */
/*   Updated: 2023/09/27 14:57:36 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_error(char *error, t_game *game)
{
	printf("Error: %s", error);
	if (game != NULL)
		destroy_game(game);
	exit(EXIT_FAILURE);
}
