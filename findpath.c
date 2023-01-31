/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:26:59 by nkietwee          #+#    #+#             */
/*   Updated: 2023/01/31 20:24:30 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for pipe
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "libft/libft.h"

char	**ft_findpath(char **envp)
{
	int i;
	char	**path;

	i = 0;
	while (envp[i]) // envp for find path
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'&& envp[i][2] == 'T'
		&& envp[i][3] == 'H' && envp[i][4] == '=')
			break;
		i++;
		// printf("i = %d\n" , i); // i : start path
	}
	path = ft_split(ft_strtrim(envp[i],"PATH="), ':'); //cut PATH =
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i] , "/") ;
		printf("%s\n" ,path[i]);
		i++;
	}
	return(path);

}
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char **path;
	int		fd_pipe[2];
	/* ft_pipe[0] = read;
		ft_pipe[1] = write;	*/
	int	id;

	// if (1) // 5

	path = ft_findpath(envp);
	if (pipe(fd_pipe) == -1) // protect pipe
	{
		printf("Error pipe");
		exit(1);
	}
	else
	{

	}

	id = fork();
	if (id == -1)
		exit(2);
}

