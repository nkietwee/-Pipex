/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:10:11 by nkietwee          #+#    #+#             */
/*   Updated: 2023/01/31 20:12:20 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	check(char const s1, char const *set)
{
	while (*set != '\0')
	{
		if (s1 == *set++)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	front;
	size_t	back;
	char	*dest;
	char	*tmp;

	if (!s1 || !set)
		return (NULL);
	front = 0;
	back = ft_strlen((char *)s1);
	while (s1[front] != '\0' && check(s1[front], set))
		front++;
	while (back > front && check(s1[back - 1], set))
		back--;
	dest = (char *)malloc(sizeof(char) * (back - front) + 1);
	if (!dest)
		return (NULL);
	tmp = dest;
	while (front < back)
		*dest++ = *(s1 + front++);
	*dest = '\0';
	return (tmp);
}
