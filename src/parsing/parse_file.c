/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:46:02 by jalbers           #+#    #+#             */
/*   Updated: 2023/10/12 11:49:23 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_next_element(char *file_content, int element_index)
{
	static int	i = 0;
	char		*next_element;

	while (file_content[i] == '\n')
		i++;
	next_element = file_content + i;
	if (element_index != TOTAL_INPUT_ELEMENTS)
	{
		while (file_content[i] && file_content[i] != '\n')
			i++;
		file_content[i++] = '\0';
	}
	return (next_element);
}

int	count_tokens(char *str, char delimeter)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != delimeter && (i == 0 || str[i - 1] == delimeter))
			count++;
		i++;
	}
	return (count);
}

int	insert_tokens(char **tokens, char *str, char delimeter, 
	int number_of_elements)
{
	int	token_count;
	int	i;
	int	j;

	token_count = count_tokens(str, delimeter);
	i = 0;
	j = 0;
	if (token_count != number_of_elements)
		return (0);
	while (str[i] && j < token_count)
	{
		while (str[i] == delimeter)
			i++;
		tokens[j++] = str + i;
		while (str[i] && str[i] != delimeter)
			i++;
		str[i++] = '\0';
	}
	return (1);
}

void	parse_element(t_game *game, char *element)
{
	game->tokens = malloc(sizeof(char *) * 2);
	if (!insert_tokens(game->tokens, element, ' ', 2))
		handle_error("Element has wrong number of arguments", game); 
	if (strcmp(game->tokens[0], "NO") == 0)
		set_texture(game, &game->NO, game->tokens[1]);
	else if (strcmp(game->tokens[0], "SO") == 0)
		set_texture(game, &game->SO, game->tokens[1]);
	else if (strcmp(game->tokens[0], "WE") == 0)
		set_texture(game, &game->WE, game->tokens[1]);
	else if (strcmp(game->tokens[0], "EA") == 0)
		set_texture(game, &game->EA, game->tokens[1]);
	else if (strcmp(game->tokens[0], "D") == 0)
		set_texture(game, &game->DOOR, game->tokens[1]);
	else if (strcmp(game->tokens[0], "D1") == 0)
		set_texture(game, &game->DOOR_WALL_1, game->tokens[1]);
	else if (strcmp(game->tokens[0], "D2") == 0)
		set_texture(game, &game->DOOR_WALL_2, game->tokens[1]);
	else if (strcmp(game->tokens[0], "F") == 0)
		set_rgb(game, &game->colors.F, game->tokens[1]);
	else if (strcmp(game->tokens[0], "C") == 0)
		set_rgb(game, &game->colors.C, game->tokens[1]);
	else
		handle_error("Incorrect element identifier", game);
	free (game->tokens);
	game->tokens = NULL;
}

int	parse_file(t_game *game, char *file_name)
{
	int		element_index;
	char	*element;

	element_index = 1;
	game->file_content = get_file_content(game, file_name);
	while (element_index <= TOTAL_INPUT_ELEMENTS)
	{
		element = get_next_element(game->file_content, element_index);
		if (element_index < TOTAL_INPUT_ELEMENTS) 
			parse_element(game, element);
		else
			create_map(game, element);
		element_index++;
	}
	game->c_color = game->colors.C.r << 24 | game->colors.C.g << 16 
		| game->colors.C.b << 8 | game->colors.C.a;
	game->f_color = game->colors.F.r << 24 | game->colors.F.g << 16 
		| game->colors.F.b << 8 | game->colors.F.a;
	return (0);
}
