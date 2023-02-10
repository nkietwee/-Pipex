/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_substring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:03:00 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/09 22:20:30 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

#include "pipex.h"
char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		while (str[i + j] == to_find[j] && str[i + j] != '\0')
			j++;
		if (to_find[j] == '\0')
			return (str + i);
		i++;
	}
	return (0);
}

int	ft_find_substring(char *haystack, char *needle)
{
	char	*found = ft_strstr(haystack, needle);
	if (found != NULL)
		return (1);
  return (0);
}


// int main() {
//   char str[] = "This is a test string";
//   int result = ft_find_substring(str, "/");
//   if (result == 1)
// 		printf("1Substring found\n");
//   else
//     printf("0Substring not found\n");
//   return 0;
// }

