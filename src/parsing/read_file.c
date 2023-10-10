/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 20:36:22 by josephalber       #+#    #+#             */
/*   Updated: 2023/09/27 15:41:15 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_cub_file(char *filename)
{
	int		i;
	int		j;
	char	*cub_suffix;

	i = ft_strlen(filename) - 1;
	j = 3;
	cub_suffix = ".cub";
	while (j >= 0)
	{
		if (filename[i--] != cub_suffix[j--])
			return (0);
	}
	return (1);
}

char	*append_buffer(char *old_str, char *buffer, int bytes_read)
{
	char		*new_str;
	static int	new_str_length = 0;
	int			i;
	int			j;

	i = 0;
	j = 0;
	new_str_length += bytes_read;
	new_str = malloc(new_str_length + 1);
	while (old_str != NULL && old_str[i])
	{
		new_str[i] = old_str[i];
		i++;
	}
	while (buffer[j])
		new_str[i++] = buffer[j++];
	new_str[i] = '\0';
	if (old_str != NULL)
		free (old_str);
	return (new_str);
}

char	*read_file(int fd)
{
	char		*file_content;
	char		*buffer;
	ssize_t		bytes_read;

	file_content = NULL;
	buffer = malloc(BUFFER_SIZE_READFILE + 1);
	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE_READFILE);
		if (bytes_read == -1)
			return (0);
		buffer[bytes_read] = '\0';
		file_content = append_buffer(file_content, buffer, bytes_read);
	}
	free (buffer);
	return (file_content);
}

char	*get_file_content(t_game *game, char *file_name)
{
	int		fd;
	char	*file_content;

	if (is_cub_file(file_name) == 0)
		handle_error("No .cub file", game);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		handle_error("Cannot open file", game);
	file_content = read_file(fd);
	close(fd);
	return (file_content);
}
