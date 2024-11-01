/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:47:06 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/11 19:06:42 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr_(left_str, '\n') && rd_bytes)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (free(buff), free(left_str), NULL);
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin_(left_str, buff);
	}
	return (free(buff), left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str = NULL;
	int			is_malloc_error;

	is_malloc_error = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (left_str != NULL)
			free(left_str);
		left_str = NULL;
		return (0);
	}
	left_str = ft_read_to_left_str(fd, left_str);
	if (!left_str)
		return (NULL);
	line = ft_get_line(left_str, &is_malloc_error);
	if (is_malloc_error)
		return (free(left_str), NULL);
	left_str = ft_new_left_str(left_str, &is_malloc_error);
	if (is_malloc_error)
		return (NULL);
	return (line);
}
