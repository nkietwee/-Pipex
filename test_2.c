/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:41:02 by nkietwee          #+#    #+#             */
/*   Updated: 2023/01/30 23:38:32 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include <sys/wait.h>
	// pid_t wait(int *stat_loc);
// int	main(void)
// {
// 	int	id = fork();
// 	int	n;
// 	if (id == 0)
// 		n = 1;
// 	else
// 		n = 6;
// 	// if (id == 0)
// 	if (id != 0)
// 		wait(NULL);
// 	int	i;
// 	for (i = n ; i < n + 5 ; i++ )
// 	{
// 		printf("%d", i);
// 		// fflush(stdout);
// 	}
// 	if (id != 0)
// 		printf("\n");

// }




// C program to illustrate
// pipe system call in C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MSGSIZE 16
char* msg1 = "hello, world #1";
char* msg2 = "hello, world #2";
char* msg3 = "hello, world #3";

int main()
{
    char inbuf[MSGSIZE];
    int p[2], i;

    // if (pipe(p) < 0)
    if (pipe(p) != 0)
        exit(1);

    /* continued */
    /* write pipe */
    write(p[1], msg1, MSGSIZE);
    write(p[1], msg2, MSGSIZE);
    write(p[1], msg3, MSGSIZE);

    for (i = 0; i < 3; i++)
	{
        /* read pipe */
        read(p[0], inbuf, MSGSIZE);
        printf("%s\n", inbuf);
		// printf("----Hello World----\n");
    }
    return 0;
}
