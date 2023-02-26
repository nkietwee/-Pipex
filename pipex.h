/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:15:33 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/27 02:23:11 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <fcntl.h>

typedef struct s_pipe
{
	char	**path;
	int		fd_pipe[2];
	int		id1;
	int		id2;
	int		status;
	int		i;
	char	*findpath;
}	t_pipe;

void	ft_createchild1(int fd_pipe[], char **argv, char **path, char **env);
void	ft_createchild2(int fd_pipe[], char **argv, char **path, char **env);
char	**ft_findpath(char **envp);
void	ft_execve_cmd(char **path, char **cmd, char **env);
void	ft_execve_path(char **cmd, char **env);
void	ft_error(int mode, char *argv, char *cmd, int errnum);
void	ft_freefree(char **str);

//libft
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_free(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char s2);

#endif
