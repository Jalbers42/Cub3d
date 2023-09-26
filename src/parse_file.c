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

int ft_strlen(char *str)
{
    int i;

    i = 0;
	while (str[i] != '\0')
		i++;
    return (i);
}

int	is_cub_file(char *filename)
{
	int i = ft_strlen(filename) - 1;
    int j = 3;
    char    *cub_suffix = ".cub";

    while (j >= 0)
    {
        if (filename[i--] != cub_suffix[j--])
            return (0);
    }
    return (1);
}

// char    **create_map(char *file_content)
// {
//     int map_width;
//     int map_height;
//     data->map_width = calc_width(map_str);
// 	data->map_height = calc_height(map_str);
// }

int parse_file(t_game *game, char *file_name)
{
	int		fd;
    char    *file_content;

    if (is_cub_file(file_name) == 0)
        handle_error("No .cub file", game);
    fd = open(file_name, O_RDONLY);
	if (fd == -1)
        handle_error("Cannot open file", game);
    file_content = read_file(fd);
    printf("%s", file_content);
    // create map
	close(fd);
    free(file_content); 
	return (0);
}
