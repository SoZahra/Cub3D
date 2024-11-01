/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:05:37 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/12 18:26:17 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_(char *s, int occ)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (occ == '\0')
		return ((char *)&s[ft_strlen_(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)occ)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		if (!left_str)
			return (NULL);
		left_str[0] = '\0';
	}
	str = malloc(sizeof(char) * ((ft_strlen_(left_str) + ft_strlen_(buff))
				+ 1));
	if (str == NULL)
		return (free(left_str), NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i])
			str[i] = left_str[i];
	while (buff[j])
		str[i++] = buff[j++];
	str[ft_strlen_(left_str) + ft_strlen_(buff)] = '\0';
	return (free(left_str), str);
}

char	*ft_get_line(char *left_str, int *is_malloc_error)
{
	int		i;
	char	*str;

	i = 0;
	if (!left_str[i])
		return (NULL);
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (left_str[i] == '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (*is_malloc_error = 1, NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_new_left_str(char *left_str, int *is_malloc_error)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
		return (free(left_str), NULL);
	i++;
	str = (char *)malloc(sizeof(char) * (ft_strlen_(left_str) - i + 1));
	if (!str)
		return (*is_malloc_error = 1, free(left_str), NULL);
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	str[j] = '\0';
	return (free(left_str), str);
}
