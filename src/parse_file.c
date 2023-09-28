/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Jalbers42                                         #+#    #+#             */
/*   https://github.com/Jalbers42                     ###   ###########       */
/*                                                                            */
/******************************************************************************/

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

char **get_tokens(char *element)
{
    char    **tokens = malloc(sizeof(char*) * 2);
    int     i = 0;
    int     j = 0;

    while (element[i] && j < 2)
    {
        while (element[i] == ' ')
            i++;
        tokens[j++] = element + i;
        while (element[i] && element[i] != ' ')
            i++;
        element[i++] = '\0'; 
    }
    return (tokens);
}

void    parse_element(t_game *game, char *element)
{
    char    *identifiers[6] = {"NO", "SO", "WE", "EA", "F", "C"};
    char    **tokens = get_tokens(element);
    int     i = 0;

    while (i < 6)
    {
        if (strcmp(tokens[0], identifiers[i]) == 0)
            break;
        i++;
    }
    if (i == 0)
        game->textures.NO = tokens[1];
    else if (i == 1)
        game->textures.SO = tokens[1];
    else if (i == 2)
        game->textures.WE = tokens[1];
    else if (i == 3)
        game->textures.EA = tokens[1];
    else if (i == 4)
        game->colors.F = tokens[1];
    else if (i == 5)
        game->colors.C = tokens[1];
    else
    {
        free(tokens);
        handle_error("Incorrect element identifier", game);
    }
    free (tokens);
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
	return (0);
}
