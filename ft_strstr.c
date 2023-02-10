/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:02:47 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/06 17:02:48 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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

#include <string.h>
#include <stdio.h>

int	find_substring(const char *haystack, const char *needle)
{
	char *found = ft_strstr(haystack, needle);
	if (found != NULL)
    	return 1;
	else
    	return 0;
}

/*
int main() {
  char str[] = "This is a test string";
  int result = find_substring(str, "atest");
  if (result == 1) {
    printf("Substring found\n");
  } else {
    printf("Substring not found\n");
  }
  return 0;
}

*/
