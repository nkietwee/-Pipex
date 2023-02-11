/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:15:33 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/11 20:31:36 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for pipe , close ,STDIN_FILENO
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <errno.h>
#include <sys/errno.h>
// #include "libft/libft.h"
#include <fcntl.h> // open


void		ft_createparent(int fd_pipe[], char **argv , char **path, char **env);
void		ft_createchild(int fd_pipe[], char **argv , char **path, char **env);
char	**ft_findpath(char **envp);
void ft_execve_cmd(char **path, char **cmd, char **env);
void ft_execve_path(char **cmd, char **env);
// void ft_execve_path(char **path, char **cmd, char **envp);
void ft_error(int mode,char *argv, char *cmd);
void	ft_sleep(int n);



//libft
size_t	ft_strlen(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
// int		ft_find_substring(char *haystack, char *needle);
int	ft_strcmp(char *s1, char s2);

#endif
