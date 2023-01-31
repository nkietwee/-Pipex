/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:40:13 by nkietwee          #+#    #+#             */
/*   Updated: 2023/01/31 14:26:47 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

// int	main(int argc, char **argv)
// {
// 	int	i;

// 	i = 0;
// 	mkfifo("myfifo1", 0770);

// }

static size_t ft_countword(char const *s, char c)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			if (s[i] == '\0' || s[i] == c)
				count++;
		}
	}
	return (count);
}

static char *ft_printword(char const *s, char c, size_t *start)
{
	size_t i;
	size_t len;
	char *res;

	i = 0;
	len = 0;
	while (s[*start] == c)
		*start += 1;
	while (s[*start + len] != '\0' && s[*start + len] != c)
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		res[i] = s[*start + i];
		i++;
	}
	*start += len;
	res[i] = '\0';
	return (res);
}

char **ft_split(char const *s, char c)
{
	size_t i;
	size_t start;
	size_t count;
	char **ans;

	i = 0;
	start = 0;
	if (!s)
		return (NULL);
	count = ft_countword(s, c);
	ans = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ans)
		return (NULL);
	while (i < count)
	{
		ans[i] = ft_printword(s, c, &start);
		i++;
	}
	ans[i] = NULL;
	return (ans);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	char **path;
	int i;
	int j;

	i = 0;
	j = 0;
	char *in_path;
	while (envp[i][j]) // envp for find path
	{
		if (envp[i][1] == 'P' && envp[i][1] == 'A' && envp[i][1] == 'T' && envp[i][1] == 'H' && envp[i][1] == '=')
	}
	// path = ft_split(envp, ':');

	int i;
	for (i = 0; path[i] != NULL; i++)
		printf("\n%s", path[i]);
	return 0;
}
