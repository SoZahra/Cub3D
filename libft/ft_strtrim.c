/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:06:13 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/23 19:31:16 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*cs1;

	j = ft_strlen(s1);
	i = 0;
	if (j == 0)
	{
		cs1 = (char *)malloc(sizeof(char));
		if (cs1)
			cs1[0] = '\0';
		return (cs1);
	}
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
		j--;
	cs1 = (char *)malloc(sizeof(char) * (j - i + 1));
	if (cs1)
		ft_strlcpy(cs1, &s1[i], j - i + 1);
	return (cs1);
}

/*
int	main(void)
{
	char *str = "   salut   ";
	char *dest = ft_strtrim(str, " ");

	printf("%s\n", dest);

}*/