/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:55:42 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/21 14:21:44 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s)) + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char	example_function(unsigned int i, char c)
{
	// Convertir chaque caractère en majuscule
	// ajouter l'index du caractère au code ASCII
	return (char)(c - 32 + i);
}

int	main(void)
{
	const char	*original_str = "hello";
	char		*modified_str;

	modified_str = ft_strmapi(original_str, example_function);
	if (modified_str)
	{
		printf("La chaîne originale est : %s\n", original_str);
		printf("La chaîne modifiée est : %s\n", modified_str);
		free(modified_str); // Libérer la mémoire allouée par malloc
	}
	else
	{
		printf("Erreur lors de l'allocation de mémoire.\n");
	}
	return (0);
}*/