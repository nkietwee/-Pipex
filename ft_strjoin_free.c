/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:08:51 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/27 20:28:42 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*size;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	size = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!size)
		return (NULL);
	while (s1[i] != '\0')
	{
		size[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		size[i] = s2[j];
		i++;
		j++;
	}
	size[i] = '\0';
	free(s1);
	return (size);
}
