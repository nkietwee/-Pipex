/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:12:35 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/27 16:13:34 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execve_cmd(char **path, char **cmd, char **env)
{
	t_pipe	px;

	px.i = 0;
	while (path[px.i] != NULL)
	{
		px.findpath = ft_strjoin(path[px.i], cmd[0]);
		if (access(px.findpath, F_OK) == 0)
		{
			if (execve(px.findpath, cmd, env) == -1)
			{
				ft_freefree(path);
				free(px.findpath);
				ft_freefree(cmd);
				exit(errno);
			}
		}
		free(px.findpath);
		px.i++;
	}
	if (path[px.i] == NULL)
	{
		ft_error(6, NULL, cmd[0], 127);
		ft_freefree(path);
		ft_freefree(cmd);
	}
}

void	ft_execve_path(char **cmd, char **env)
{
	int	i;

	i = 0;
	if (access(cmd[0], F_OK) == 0)
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			ft_freefree(cmd);
			exit(errno);
		}
	}
	else if (access(cmd[0], F_OK) == -1)
	{
		ft_error(4, NULL, cmd[0], 127);
		ft_freefree(cmd);
	}
}

void	ft_error(int mode, char *argv, char *cmd, int errnum)
{
	if (mode == 1)
		ft_putstr_fd("plz check your argument", STDOUT_FILENO);
	else if (mode == 2)
		ft_putstr_fd("Cannot create pipe", STDOUT_FILENO);
	else if (mode == 3)
		ft_putstr_fd("Cannot create fork", STDOUT_FILENO);
	else if (mode == 4)
	{
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (mode == 5)
	{
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (mode == 6)
	{
		ft_putstr_fd("zsh: command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	exit(errnum);
}

void	ft_freefree(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
