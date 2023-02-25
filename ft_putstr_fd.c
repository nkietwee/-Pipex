/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:05:44 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/12 16:49:36 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	// while(s[i])
	// {
	// 	write(fd, &s[i], 1);
	// 	i++;
	// }
}

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	int	i;

// 	i = 0;
// 	ft_putstr_fd ("zsh: command not found: ", STDOUT_FILENO);
// 	ft_putstr_fd (argv[2], STDOUT_FILENO);

// }
