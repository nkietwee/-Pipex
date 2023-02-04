/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:53:23 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/04 23:11:36 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
// #include <errno.h>
#include <sys/errno.h>
#include <fcntl.h>
#include "pipex.h"


void ft_execve(char **path,char **cmd, char **envp)
{
	int	i;
	char	*findpath = NULL;

	i = 0;
	if (access(cmd[0] , F_OK) != -1)
	{
		if (execve(cmd[0], cmd , envp) == -1)
			exit(errno);
	}
	while(path[i] != NULL) // keep path with cmd1
	{
		findpath = ft_strjoin(path[i] , cmd[0]);
		if (access(findpath , F_OK) != -1) // if find == 0
		{
				if(execve(findpath, cmd , envp) == -1)
					exit(errno);
		}
		i++;
	}
	if (path[i] == NULL)
	{
		ft_putstr_fd("zsh: command not found: " , STDERR_FILENO);
		ft_putstr_fd(cmd[0] , STDERR_FILENO);
		exit (127);
	}
}

void		ft_createparent(int fd_pipe[], char **argv , char **path, char **envp)
{
	int	fd_outfile;
	char **cmd2;
	int	i;

	i = 0;
	fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC , 0777); // 0644  This mode gives read and write permissions to the owner of the file and read permissions to everyone else.
	if  (fd_outfile < 1)
	{
		// printf("Can't open outfile");
		exit(2);
	}
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	// write(1, "sadfgsdfghj---", 15); // error ==> outfile
	close(fd_outfile);
	close(fd_pipe[0]);
	cmd2 = ft_split(argv[3] ,  ' ');
	// printf("cmd ==== %s" , cmd2[0]);
	ft_execve(path, cmd2, envp);
}

void		ft_createchild(int fd_pipe[], char **argv , char **path, char **envp)
{
	int	fd_infile;
	char **cmd1;
	int	i;
	int	test;

	test = 0;
	close(fd_pipe[0]);
	fd_infile = open(argv[1] ,O_RDONLY); // argv[1] = infile
	if (fd_infile < 0)
	{
		// printf("Can't not open file ");
		exit(0);
	}
	dup2(fd_infile, STDIN_FILENO); // change point from STDIN_FILENO to fd_infle(fd == 0)
	dup2(fd_pipe[1], STDOUT_FILENO); // change write from STDOUT_FILENO to fd_pipe[1] becaz it can pass value accross function

	close(fd_infile);
	close(fd_pipe[1]);

	// write(1, "sadfgsdfghj", 8); // error ==> outfile ,why use fd = 1 it is pipe
	cmd1 = ft_split(argv[2] ,' '); // protect cmd1 > 2 ex "ls -l a"
	// while(cmd1[test])
	// {
	// 	printf("%s" ,cmd1[test++]);
	// }
	i = 0;
	ft_execve(path, cmd1, envp);

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
	char **path;
	int		fd_pipe[2];
	/* ft_pipe[0] = read;
		ft_pipe[1] = write;	*/
	int	id;

	if (argc != 5)
		exit(1);
	path = ft_findpath(envp);
	if (pipe(fd_pipe) == -1) // protect pipe
	{
		printf("ERROR PIPE");
		return(errno);
	}
	id = fork();
	if (id == -1) // for parent process
	{
		printf("ERROR FORK");
		return(errno);
	}
	// if (id > 0) // wait children process finish
	// 	wait(NULL);
	if (id == 0 ) //for children process
	{
		ft_createchild(fd_pipe, argv , path, envp);
		// ft_putstr_fd("command not found" , STDOUT_FILENO);
	}
	ft_createparent (fd_pipe, argv, path, envp);
	wait(NULL); // wait child parent or parent process that finish first (in case sleep)
	return(0);
}
