/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:53:23 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/11 16:15:15by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_createparent(int fd_pipe[], char **argv, char **path, char **env)
{
	int fd_outfile;
	char **cmd2;

	fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777); // 0644  This mode gives read and write permissions to the owner of the file and read permissions to everyone else.
	if (fd_outfile < 1)
	{
		ft_sleep(10000000);
		ft_error(5, argv[4],NULL);
		// ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		// ft_putstr_fd(argv[4], STDERR_FILENO);
		// ft_putstr_fd("\n", STDERR_FILENO);
		exit(2);
	}
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	// write(1, "sadfgsdfghj---", 15); // error ==> outfile
	close(fd_outfile);
	close(fd_pipe[0]);
	cmd2 = ft_split(argv[3], ' ');
	if (ft_strcmp(cmd2[0] , '/') == 1) //path
		ft_execve_path(cmd2, env);
	else if (ft_strcmp(cmd2[0] , '/') == 0)
		ft_execve_cmd(path, cmd2, env);

	// if (ft_find_substring(cmd2[0] , "/") == 1) // found /
	// 	ft_execve_path(cmd2, env); // move into function ft_find_substr
	// else if (ft_find_substring(cmd2[0] , "/") != 1)
	// 	ft_execve_cmd(path, cmd2, env);
}

void ft_createchild(int fd_pipe[], char **argv, char **path, char **env)
{
	int fd_infile;
	char **cmd1;

	close(fd_pipe[0]);
	cmd1 = ft_split(argv[2], ' ');// protect cmd1 > 2 ex "ls -l a"
	fd_infile = open(argv[1], O_RDONLY); // argv[1] = infile
	if (fd_infile < 0)
	{
		ft_error(5, argv[1], NULL);
		// ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		// ft_putstr_fd(argv[1], STDERR_FILENO);
		// ft_putstr_fd("\n", STDERR_FILENO);
		exit(0);
	}
	// fd move pointer right?
	dup2(fd_infile, STDIN_FILENO);   // change point from STDIN_FILENO to fd_infle(fd == 0)
	dup2(fd_pipe[1], STDOUT_FILENO); // change write from STDOUT_FILENO to fd_pipe[1] becaz it can pass value accross function
	close(fd_infile);
	close(fd_pipe[1]);
	if (ft_strcmp(cmd1[0] , '/') == 1) //path
		ft_execve_path(cmd1, env);
	else if (ft_strcmp(cmd1[0] , '/') == 0)
		ft_execve_cmd(path, cmd1, env);
	// if (ft_find_substring(cmd1[0] , "/") == 1) //path
	// 	ft_execve_path(cmd1, envp);
	// else if (ft_find_substring(cmd1[0] , "/") == 0)
	// 	ft_execve_cmd(path, cmd1, envp);
}

char **ft_findpath(char **envp)
{
	int i;
	char **path;

	i = 0;
	while (envp[i]) // envp for find path
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
			break;
		i++;
	}
	path = ft_split((envp[i] + 5), ':'); //cut PATH
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/"); //for find path
		i++;
	}
	return (path);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	char **path;
	int fd_pipe[2];
	int id;

	if (argc != 5)
	{
		ft_error(1, NULL, NULL);
		// ft_putstr_fd("plz check your argument" ,STDOUT_FILENO);
		exit(1);
	}
	path = ft_findpath(env);
	if (pipe(fd_pipe) == -1) // protect pipe
	{
		ft_error(2, NULL, NULL);
		// ft_putstr_fd("Cannot create pipe or check your capacity", STDOUT_FILENO);
		exit (errno);
	}
	id = fork();
	if (id == -1) // for parent process
	{
		ft_error(3, NULL, NULL);
		// ft_putstr_fd("Cannot create fork or check your capacity", STDOUT_FILENO);
		exit (errno);
	}
	if (id == 0) //for children process
		ft_createchild(fd_pipe, argv, path, env);
	ft_createparent(fd_pipe, argv, path, env);
	wait(NULL); // wait child parent or parent process that finish first (in case sleep)
	return (0);
}
