/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:53:23 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/10 23:45:07 by nkietwee         ###   ########.fr       */
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

void ft_execve_cmd(char **path, char **cmd, char **envp)
{
	int i;
	char *findpath = NULL;

	i = 0;
	while (path[i] != NULL) // keep path with cmd1
	{
		findpath = ft_strjoin(path[i], cmd[0]);
		if (access(findpath, F_OK) == 0) // if find == 0
		{
			if (execve(findpath, cmd, envp) == -1)
				exit(errno);
		}
		i++;
	}
	if (path[i] == NULL) // case not found command
	{
		ft_putstr_fd("zsh: command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(127);
	}
}

void ft_execve_path(char **path, char **cmd, char **envp) // path don't use
// void ft_execve_path(char **cmd, char **envp) // path don't use
{
	int i;

	i = 0;
	(void)path;
	// if ((find_substring(cmd[0] , "bin" ) == 1) || (find_substring(cmd[0] , "srcs" ) == 1))

	// dprintf(2, "cmd[0]execve : %s\n" , cmd[0] );
	if (access(cmd[0], F_OK) == 0) // found
	{
		// write (2, "path\n", 5);
		if (execve(cmd[0], cmd, envp) == -1)
			exit(errno);
	}
	// dprintf(2, "\njhgfhjgjh %d\n" , access ( "/srcs/a.outdfghjiko", R_OK));
	// dprintf(2, "jhgfhjgjh %d\n" , access(cmd[0] , R_OK));
	// exit(0);
	else if (access(cmd[0] , F_OK) == -1) //protect
	// if (access(cmd[0] , F_OK) != 0) //protect , Why path don't entry
	{
		ft_putstr_fd("zsh: no such file or directory: " , STDERR_FILENO);
		ft_putstr_fd(cmd[0] , STDERR_FILENO);
		ft_putstr_fd("\n" , STDERR_FILENO);
		exit (127);
	}
}

void ft_createparent(int fd_pipe[], char **argv, char **path, char **envp)
{
	int fd_outfile;
	char **cmd2;
	int i;
	// char *checkmode = NULL;

	i = 0;
	fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777); // 0644  This mode gives read and write permissions to the owner of the file and read permissions to everyone else.
	if (fd_outfile < 1)
	{
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(argv[4], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		// printf("Can't open outfile");
		exit(2);
	}
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	// write(1, "sadfgsdfghj---", 15); // error ==> outfile
	close(fd_outfile);
	close(fd_pipe[0]);
	cmd2 = ft_split(argv[3], ' ');
	// printf("cmd ==== %s" , cmd2[0]);
	// ft_execve(path, cmd2, envp);
	// checkmode = ft_strjoin("/", cmd2[0]);
	// printf("checkmode === %s\n" , checkmode);
	if (ft_find_substring(cmd2[0] , "/") == 1) // found /
	{
		// write(2, "parent==found\n", 15);
		ft_execve_path(path, cmd2, envp); // move into function ft_find_substr
	}
	else if (ft_find_substring(cmd2[0] , "/") != 1)
	{
		// write(2, "parent==notfound\n", 18);
		ft_execve_cmd(path, cmd2, envp);
	}
}

void ft_createchild(int fd_pipe[], char **argv, char **path, char **envp)
{
	int fd_infile;
	char **cmd1;
	// char	*checkmode=NULL;
	int i;

	close(fd_pipe[0]);
	cmd1 = ft_split(argv[2], ' ');// protect cmd1 > 2 ex "ls -l a"
	fd_infile = open(argv[1], O_RDONLY); // argv[1] = infile
	if (fd_infile < 0)
	{
		// puts("12134354567rte");
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(0);
	}
	// fd move pointer right?
	dup2(fd_infile, STDIN_FILENO);   // change point from STDIN_FILENO to fd_infle(fd == 0)
	dup2(fd_pipe[1], STDOUT_FILENO); // change write from STDOUT_FILENO to fd_pipe[1] becaz it can pass value accross function

	close(fd_infile);
	close(fd_pipe[1]);

	// write(1, "sadfgsdfghj", 8); // error ==> outfile ,why use fd = 1 it is pipe
	i = 0;
	// checkmode = ft_strjoin("/", cmd1[0]);
	// write(2, cmd1[0], 10);
	// dprintf(2, "cmd = %s =\n" ,cmd1[0]);
	if (ft_find_substring(cmd1[0] , "/") == 1) //path
	{
		// write(2, "child==found\n", 13);
		// ft_execve_path(path, cmd1);
		ft_execve_path(path, cmd1, envp);
	}
	// else if (ft_find_substring(cmd1[0] , "/") == 0)
	if (ft_find_substring(cmd1[0] , "/") == 0)
	{
		// write(2, "child==notfound\n", 16);
		ft_execve_cmd(path, cmd1, envp);
	}
}

char **ft_findpath(char **envp)
{
	int i;
	char **path;

	i = 0;
	while (envp[i]) // envp for find path
	{
		// printf("i = %d\n" , i); // i : start path
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
			break;
		i++;
	}
	path = ft_split((envp[i] + 5), ':'); //cut PATH
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/"); //for find path
		// printf("   %s\n" ,path[i]);
		i++;
	}
	return (path);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	char **path;
	int fd_pipe[2];
	/* ft_pipe[0] = read;
		ft_pipe[1] = write;	*/
	int id;

	if (argc != 5)
	{
		ft_putstr_fd("plz check your argument" ,STDOUT_FILENO);
		exit(1);
	}
	path = ft_findpath(envp);
	if (pipe(fd_pipe) == -1) // protect pipe
	{
		ft_putstr_fd("ERROR PIPE", STDOUT_FILENO);
		return (errno);
	}
	id = fork();
	if (id == -1) // for parent process
	{
		ft_putstr_fd("ERROR FORK", STDOUT_FILENO);
		return (errno);
	}
	// if (id > 0) // wait children process finish
	// 	wait(NULL);
	if (id == 0) //for children process
	{
		ft_createchild(fd_pipe, argv, path, envp);
		// ft_putstr_fd("command not found" , STDOUT_FILENO);
	}
	ft_createparent(fd_pipe, argv, path, envp);
	wait(NULL); // wait child parent or parent process that finish first (in case sleep)
	return (0);
}
