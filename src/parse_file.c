/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/27 22:20:48 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void    print_map(t_game *game)
{
    int y = 0;
    int x;
    
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
            printf("%c", game->map[y][x++]);
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
    if (element_index == TOTAL_INPUT_ELEMENTS)
        return (next_element);
    while (file_content[i] && file_content[i] != '\n')
        i++;
    file_content[i++] = '\0';
    return (next_element);
}

void    parse_element(t_game *game, char *element, int element_index)
{
    if (element_index == TOTAL_INPUT_ELEMENTS)
        create_map(game, element);
    else
    {
        
        // parse_element();
    }
}

int parse_file(t_game *game, char *file_name)
{
    char    *file_content;
    int     element_index = 1;
    char    *element;

    file_content = get_file_content(game, file_name);
    while (element_index <= TOTAL_INPUT_ELEMENTS)
    {
        element = get_next_element(file_content, element_index);
        parse_element(game, element, element_index);
        element_index++;
    }
    //print_map(game);
    free(file_content); 
	return (0);
}
