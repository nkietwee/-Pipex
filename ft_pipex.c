/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:53:23 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/27 02:15:28 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_createchild2(int fd_pipe[], char **argv, char **path, char **env)
{
	int		fd_outfile;
	char	**cmd2;

	fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd_outfile < 1)
	{
		ft_freefree(path);
		ft_error(5, argv[4], NULL, 1);
	}
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);
	close(fd_pipe[0]);
	cmd2 = ft_split(argv[3], ' ');
	if (ft_strcmp(cmd2[0], '/') == 1)
		ft_execve_path(cmd2, env);
	else if (ft_strcmp(cmd2[0], '/') == 0)
		ft_execve_cmd(path, cmd2, env);
}

void	ft_createchild1(int fd_pipe[], char **argv, char **path, char **env)
{
	int		fd_infile;
	char	**cmd1;

	close(fd_pipe[0]);
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile < 1)
	{
		ft_freefree(path);
		ft_error(5, argv[1], NULL, 0);
	}
	cmd1 = ft_split(argv[2], ' ');
	dup2(fd_infile, STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_infile);
	close(fd_pipe[1]);
	if (ft_strcmp(cmd1[0], '/') == 1)
		ft_execve_path(cmd1, env);
	else if (ft_strcmp(cmd1[0], '/') == 0)
		ft_execve_cmd(path, cmd1, env);
}

char	**ft_findpath(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H')
			break ;
		i++;
	}
	path = ft_split((envp[i] + 5), ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin_free(path[i], "/");
		i++;
	}
	return (path);
}

int	main(int argc, char **argv, char **env)
{
	t_pipe	px;

	if (argc != 5)
		ft_error(1, NULL, NULL, 1);
	px.path = ft_findpath(env);
	if (pipe(px.fd_pipe) == -1)
		ft_error(2, NULL, NULL, errno);
	px.id1 = fork();
	if (px.id1 == -1)
		ft_error(3, NULL, NULL, errno);
	if (px.id1 == 0)
		ft_createchild1(px.fd_pipe, argv, px.path, env);
	px.id2 = fork();
	if (px.id2 == -1)
		ft_error(3, NULL, NULL, errno);
	if (px.id2 == 0)
		ft_createchild2(px.fd_pipe, argv, px.path, env);
	if (px.id2 != 0)
		ft_freefree(px.path);
	close(px.fd_pipe[0]);
	close(px.fd_pipe[1]);
	waitpid(px.id1, NULL, 0);
	waitpid(px.id2, &px.status, 0);
	return (WEXITSTATUS(px.status));
}

/*
int	main(int argc, char **argv, char **env)
{
	char	**path;
	int		fd_pipe[2];
	int		id1;
	int		id2;
	int		status;

	if (argc != 5)
	{
		ft_error(1, NULL, NULL);
		exit(1);
	}
	path = ft_findpath(env);
	if (pipe(fd_pipe) == -1)
	{
		ft_error(2, NULL, NULL);
		exit (errno);
	}
	id1 = fork();
	if (id1 == -1)
	{
		ft_error(3, NULL, NULL);
		exit (errno);
	}
	if (id1 == 0)
		ft_createchild1(fd_pipe, argv, path, env);
	id2 = fork();
	if (id2 == -1)
	{
		ft_error(3, NULL, NULL);
		exit (errno);
	}
	if (id2 == 0)
		ft_createchild2(fd_pipe, argv, path, env);
	if (id2 != 0)
		ft_freefree(path);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(id1, NULL, 0);
	waitpid(id2, &status, 0);
	return (WEXITSTATUS(status));
}*/
