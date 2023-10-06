/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/03 00:37:00 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    print_map(t_game *game, int **map)
{
	int y = 0;
	int x;
	
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
			printf("%i", map[y][x++]);
		printf("\n");
		y++;
	}
}

char *get_next_element(char *file_content, int element_index)
{
	static int  i = 0;
	char        *next_element;

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

int count_tokens(char *str, char delimeter)
{
	int count = 0;
	int i = 0;

	while (str[i])
	{
		if(str[i] != delimeter && (i == 0 || str[i - 1] == delimeter))
			count++;
		i++;
	}
	return (count);
}

int insert_tokens(char **tokens, char *str, char delimeter, int number_of_elements)
{
	int     token_count = count_tokens(str, delimeter);
	int     i = 0;
	int     j = 0;

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

int   set_rgb(t_rgb *color, char *str)
{
	char    **tokens = malloc(sizeof(char*) * 3);
	if (!insert_tokens(tokens, str, ',', 3))
	{
		free (tokens);
		return (0);
	}
	color->r = ft_atoi(tokens[0]);
	color->g = ft_atoi(tokens[1]);
	color->b = ft_atoi(tokens[2]);
	color->a = 255;
	free(tokens);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255 || color->b < 0 || color->b > 255)
		return (0);
	return (1);
}

void	set_texture(t_game *game, mlx_texture_t	**texture, char *path)
{
	*texture = mlx_load_png(path);
	if (!*texture)
		handle_error("Error opening texture PNG.", game);
}

void    parse_element(t_game *game, char *element)
{
	char    *identifiers[TOTAL_INPUT_ELEMENTS - 1] = {"NO", "SO", "WE", "EA", "D", "D1", "D2", "F", "C"};

	game->tokens = malloc(sizeof(char *) * 2);
	if (!insert_tokens(game->tokens, element, ' ', 2))
		handle_error("Element has wrong number of arguments", game); 
	int i = 0;
	while (i < TOTAL_INPUT_ELEMENTS - 1)
	{
		if (strcmp(game->tokens[0], identifiers[i]) == 0)
			break;
		i++;
	}
	if (i == 0)
		set_texture(game, &game->NO, game->tokens[1]);	
	else if (i == 1)
		set_texture(game, &game->SO, game->tokens[1]);	
	else if (i == 2)
		set_texture(game, &game->WE, game->tokens[1]);	
	else if (i == 3)
		set_texture(game, &game->EA, game->tokens[1]);	
	else if (i == 4)
		set_texture(game, &game->DOOR, game->tokens[1]);
	else if (i == 5)
		set_texture(game, &game->DOOR_WALL_1, game->tokens[1]);
	else if (i == 6)
		set_texture(game, &game->DOOR_WALL_2, game->tokens[1]);
	else if (i == 7 && !set_rgb(&game->colors.F, game->tokens[1]))
		handle_error("Wrong RGB value", game);
	else if (i == 8 && !set_rgb(&game->colors.C, game->tokens[1]))
		handle_error("Wrong RGB value", game);
	else if (i >= 9)
		handle_error("Incorrect element identifier", game);
	free (game->tokens);
	game->tokens = NULL;
}

int parse_file(t_game *game, char *file_name)
{
	int     element_index = 1;
	char    *element;

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
	game->c_color = game->colors.C.r << 24 | game->colors.C.g << 16 | game->colors.C.b << 8 | game->colors.C.a;
	game->f_color = game->colors.F.r << 24 | game->colors.F.g << 16 | game->colors.F.b << 8 | game->colors.F.a;
	return (0);
}