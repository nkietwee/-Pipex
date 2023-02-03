/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:15:33 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/03 18:00:08 by nkietwee         ###   ########.fr       */
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
// #include "libft/libft.h"
#include <fcntl.h> // open


int		ft_createparent(int fd_pipe[], char **argv , char **path, char **envp);
int		ft_createchild(int fd_pipe[], char **argv , char **path, char **envp);
char	**ft_findpath(char **envp);


//libft
size_t	ft_strlen(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);


#endif
