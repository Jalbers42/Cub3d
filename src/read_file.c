/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 20:36:22 by josephalber       #+#    #+#             */
/*   Updated: 2023/01/19 18:35:23 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*append_buffer(char *old_str, char *buffer, int bytes_read)
{	
	char		*new_str;
	static int	new_str_length = 0;
	int			i = 0;
	int			j = 0;

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
	char		*file_content = NULL;
	char		*buffer = malloc(BUFFER_SIZE_READFILE + 1);
	ssize_t		bytes_read = 1;

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

// char	*read_file(int fd)
// {
// 	ssize_t		bytes_read;
// 	char		*buffer;
// 	ssize_t		BUFFER_SIZE_READFILE;
// 	static char	*file_content;

// 	BUFFER_SIZE_READFILE = 100;
// 	buffer = malloc(BUFFER_SIZE_READFILE + 1);
// 	buffer[BUFFER_SIZE_READFILE] = '\0';
// 	bytes_read = BUFFER_SIZE_READFILE;
// 	while (bytes_read == BUFFER_SIZE_READFILE)
// 	{
// 		bytes_read = read(fd, buffer, BUFFER_SIZE_READFILE);
// 		if (bytes_read == -1)
// 			return (0);
// 		buffer[bytes_read] = '\0';
// 		file_content = str_to_map(file_content, buffer, bytes_read);
// 	}
// 	free (buffer);
// 	return (file_content);
// }
