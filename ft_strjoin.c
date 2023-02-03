/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:08:51 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/03 17:08:10 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*size;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	size = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
	if (!size)
		return (NULL);
	while (s1[i] != '\0')
	{
		size[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		size[i] = s2[j];
		i++;
		j++;
	}
	size[i] = '\0';
	// free((void *)s1);
	// free((void *)s2);
	return (size);
}

// #include<stdio.h>
// int	main(void)
// {
// 	// char *name;

// 	printf("%s" , ft_strjoin("name11111", "name"));
// }
