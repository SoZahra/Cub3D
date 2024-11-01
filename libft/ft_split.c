/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:33:18 by fzayani           #+#    #+#             */
/*   Updated: 2024/10/23 14:24:50 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_split(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// char	*ft_strncpy(char *dst, const char *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (src[i] && i < n)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	while (i < n)
// 	{
// 		dst[i] = '\0';
// 		i++;
// 	}
// 	return (dst);
// }

static int	count_words(const char *s, char c)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (count);
}

// static char	*ft_strndup(const char *s, size_t n)
// {
// 	char	*str;

// 	str = (char *)malloc(sizeof(char) * n + 1);
// 	if (!str)
// 		return (NULL);
// 	str = ft_strncpy(str, s, n);
// 	str[n] = '\0';
// 	return (str);
// }

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = 0;
	k = 0;
	tab = (char **)malloc(sizeof(char *) * ((count_words(s, c)) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
		{
			tab[k] = ft_strndup(s + j, i - j);
			if (!tab[k++])
				return (ft_free_split(tab), NULL);
		}
	}
	return (tab[k] = NULL, tab);
}
/*
void	print_split(char **split) {
	int i = 0;
	while (split[i]) {
		printf("split[%d] = %s\n", i, split[i]);
		free(split[i]);
		i++;
	}
	free(split);
}

int	main(void) {
	char str[] = "Hello, world! This is a test.";
	char delimiter = ' ';
	char **result = ft_split(str, delimiter);

	if (result) {
		print_split(result);
	} else {
		printf("Memory allocation failed\n");
	}

	return (0);
}
*/