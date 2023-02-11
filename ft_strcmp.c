/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:33:36 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/05 23:33: by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string.h>


int	ft_strcmp(char *s1, char s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2)
	{
		if (s1[i] == s2)
			return(1);
		i++;
	}
	return (0);

}

// #include<stdio.h>
// int	main(void)
// {
// 	printf("%d" ,ft_strcmp(" /bin" , '/'));

// }
