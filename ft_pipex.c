/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:53:23 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/03 17:59:34 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include "pipex.h"


// char	*ft_execve(char **path,char *cmd1, char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while(path[i] != NULL) // keep path with cmd1
// 	{
// 		findpath = ft_strjoin(path[i] , cmd1[0]);
// 		if (access(findpath , F_OK) != -1) // if find == 0
// 			// execl (findpath, findpath ,cmd1[1], NULL);
// 			// execve(findpath, cmd1 , envp);
// 		else
// 			ft_createparent
// 		i++;
// 	}

// }

int		ft_createparent(int fd_pipe[], char **argv , char **path, char **envp)
{
	int	fd_outfile;
	char	*findpath = NULL;
	char **cmd2;
	int	i;

	i = 0;
	//argv[4] = outfile
	fd_outfile = open(argv[4], O_CREAT | O_RDONLY, 0644); // 0644  This mode gives read and write permissions to the owner of the file and read permissions to everyone else.
	if  (fd_outfile < 1)
	{
		printf("Can't open outfile");
	}
	close(fd_pipe[1]);

	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);

	close(fd_outfile);
	close(fd_pipe[0]);
	cmd2 = ft_split(argv[3] ,  ' ');
	while (path[i] != NULL)
	{
		findpath = ft_strjoin(path[i], cmd2[0]);
		if (access(findpath, F_OK) == 0)
			if (execve(findpath, cmd2, envp) == -1)
			{
				printf("Can't execve from parent process");
				return(6);
			}
		i++;
	}
	return(0);
}

int		ft_createchild(int fd_pipe[], char **argv , char **path, char **envp)
{
	int	fd_infile;
	char	*findpath = NULL;
	char **cmd1;
	int	i;
	int	test;

	test = 0;
	close(fd_pipe[0]);
	fd_infile = open(argv[1] ,O_RDONLY); // argv[1] = infile
	if (fd_infile < 0)
	{
		printf("Can't not open file ");
		return(4);
	}

	dup2(fd_infile, STDIN_FILENO); // change point from STDIN_FILENO to fd_infle(fd == 0)
	dup2(fd_pipe[1], STDOUT_FILENO); // change write from STDOUT_FILENO to fd_pipe[1] becaz it can pass value accross function

	close(fd_infile);
	close(fd_pipe[1]);

	cmd1 = ft_split(argv[2] ,' '); // protect cmd1 > 2 ex "ls -l a"
	// while(cmd1[test])
	// {
	// 	printf("%s" ,cmd1[test++]);
	// }
	i = 0;
	while(path[i] != NULL) // keep path with cmd1
	{
		findpath = ft_strjoin(path[i] , cmd1[0]);
		if (access(findpath , F_OK) == 0) // if find == 0 // protext It doesn't have flag
		{
			if (execve(findpath, cmd1 , envp) == -1) // execve  
			{
				printf("----Can't execve----");
				// free
				return(5);
			}
		}
		i++;
	}
	return(0);
}

char	**ft_findpath(char **envp)
{
	int i;
	char	**path;

	i = 0;
	while (envp[i]) // envp for find path
	{
		// printf("i = %d\n" , i); // i : start path
		if (envp[i][0] == 'P' && envp[i][1] == 'A'&& envp[i][2] == 'T'
		&& envp[i][3] == 'H' && envp[i][4] == '=')
			break;
		i++;
	}

	path = ft_split((envp[i] + 5), ':'); //cut PATH
	// path = ft_split(ft_strtrim(envp[i],"PATH="), ':'); //cut PATH
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i] , "/") ; //for find path
		// printf("   %s\n" ,path[i]);
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

	path = ft_findpath(envp);
	if (pipe(fd_pipe) == -1) // protect pipe
	{
		printf("ERROR PIPE");
		return(1);
	}
	id = fork();
	if (id == -1) // for parent process
	{
		printf("ERROR FORK");
		return(2);
	}
	// if (id > 0) // wait children process finish
	// 	wait(NULL);
	if (id == 0 ) //for children process
	{
		ft_createchild(fd_pipe, argv , path, envp);
	}
	ft_createparent (fd_pipe, argv, path, envp);
	return(0);


}
