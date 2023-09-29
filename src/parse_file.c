/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/29 14:40:21 by ycardona         ###   ########.fr       */
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
 */
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
    free(tokens);
    if (color->r < 0 || color->r > 250 || color->g < 0 || color->g > 250 || color->b < 0 || color->b > 250)
        return (0);
    return (1);
}

void    parse_element(t_game *game, char *element)
{
    char    *identifiers[6] = {"NO", "SO", "WE", "EA", "F", "C"};

    game->tokens = malloc(sizeof(char *) * 2);
    if (!insert_tokens(game->tokens, element, ' ', 2))
        handle_error("Element has wrong number of arguments", game); 
    int i = 0;
    while (i < 6)
    {
        if (strcmp(game->tokens[0], identifiers[i]) == 0)
            break;
        i++;
    }
    if (i == 0)
        game->textures.NO = game->tokens[1];
    else if (i == 1)
        game->textures.SO = game->tokens[1];
    else if (i == 2)
        game->textures.WE = game->tokens[1];
    else if (i == 3)
        game->textures.EA = game->tokens[1];
    else if (i == 4 && !set_rgb(&game->colors.F, game->tokens[1]))
        handle_error("Wrong RGB value", game);
    else if (i == 5 && !set_rgb(&game->colors.C, game->tokens[1]))
        handle_error("Wrong RGB value", game);
    else if (i >= 6)
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
    // check for missing texture
	return (0);
}
