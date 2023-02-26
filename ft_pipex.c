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

void ft_createchild2(int fd_pipe[], char **argv, char **path, char **env)
{
	int fd_outfile;
	char **cmd2;

	fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777); // 0644  This mode gives read and write permissions to the owner of the file and read permissions to everyone else.
	if (fd_outfile < 1)
	{
		// ft_sleep(10000000);
		ft_error(5, argv[4],NULL);
		// exit(errno);
		exit(1);
	}
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);
	close(fd_pipe[0]);
	cmd2 = ft_split(argv[3], ' ');
	if (ft_strcmp(cmd2[0] , '/') == 1) //path
		ft_execve_path(cmd2, env);
	else if (ft_strcmp(cmd2[0] , '/') == 0)
		ft_execve_cmd(path, cmd2, env);
}

void ft_createchild1(int fd_pipe[], char **argv, char **path, char **env)
{
	int fd_infile;
	char **cmd1;

	close(fd_pipe[0]);
	fd_infile = open(argv[1], O_RDONLY); // argv[1] = infile
	if (fd_infile < 1)
	{
		ft_freefree(path);
		ft_error(5, argv[1], NULL);
		exit(errno);
		// exit(127); // //
	}
	cmd1 = ft_split(argv[2], ' ');// protect cmd1 > 2 ex "ls -l a"
	// fd move pointer right?
	dup2(fd_infile, STDIN_FILENO);   // change point from STDIN_FILENO to fd_infle(fd == 0)
	dup2(fd_pipe[1], STDOUT_FILENO); // change write from STDOUT_FILENO to fd_pipe[1] becaz it can pass value accross function
	close(fd_infile);
	close(fd_pipe[1]);
	if (ft_strcmp(cmd1[0] , '/') == 1) //path
		ft_execve_path(cmd1, env);
	else if (ft_strcmp(cmd1[0] , '/') == 0)
		ft_execve_cmd(path, cmd1, env);
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
		path[i] = ft_strjoin_free(path[i], "/"); //for find path and free first argument
		// free(path[i]);
		i++;
	}
	return (path);
}

int main(int argc, char **argv, char **env)
{
	char **path;
	int fd_pipe[2];
	int id1;
	int id2;

	if (argc != 5)
	{
		ft_error(1, NULL, NULL);
		exit(1);
	}
	path = ft_findpath(env);
	if (pipe(fd_pipe) == -1) // protect pipe
	{
		ft_error(2, NULL, NULL);
		exit (errno);
	}
	id1 = fork();
	if (id1 == -1) // for parent process
	{
		ft_error(3, NULL, NULL);
		exit (errno);
	}
	if (id1 == 0) //for children process
		ft_createchild1(fd_pipe, argv, path, env);
	id2 = fork();
	if (id2 == -1)
	{
		ft_error(3, NULL, NULL);
		exit (errno);
	}
	if (id2 == 0)
		ft_createchild2(fd_pipe, argv, path, env); // child
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	int status;
	waitpid(id1 ,NULL , 0); //wait first
	// waitpid(id2 ,NULL , 0); //wait first
	waitpid(id2 , &status, 0); //status keep value for exit (id2)

	// wait(NULL); // wait child parent or parent process that finish first (in case sleep)
	//return(0); if you don't use WEXITSTATUS(status)
	return (WEXITSTATUS(status));
}
