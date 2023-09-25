/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:09:15 by jalbers           #+#    #+#             */
/*   Updated: 2023/01/23 23:12:12 by jalbers          ###   ########.fr       */
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
