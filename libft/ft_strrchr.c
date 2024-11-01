/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:15:47 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/22 18:11:17 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int occ)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)occ)
			return ((char *)str + i);
		i--;
	}
	return (NULL);
}
/*
int	main(void)
{
  char buffer1[40] = "computer program";
  char * ptr;
  int    ch = 'p';

  ptr = ft_strrchr( buffer1, '\0' );
  printf( "The last occurrence of %c in '%s' is '%s'\n",
			ch, buffer1, ptr );
}*/