/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:19:20 by nkietwee          #+#    #+#             */
/*   Updated: 2023/01/22 02:36:08 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// C program to illustrate
// pipe system call in C
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #define MSGSIZE 16
// char* msg1 = "hello, world #1";
// char* msg2 = "hello, world #2";
// char* msg3 = "hello, world #3";
  
// int	main()
// {
//     char	inbuf[MSGSIZE];
//     int		p[2], i;
  
//     // printf("p[0] === %d\n", p[0]);
//     // printf("p[1] === %d\n", p[1]);
 
//     if (pipe(p) < 0)
//         exit(1);
  
//     /* continued */
//     /* write pipe */
//     // printf("p[0] === %d\n", p[0]);
//     // printf("p[1] === %d\n", p[1]);
//     //printf("p[2] === %d\n", p[2]);
//     // exit(1);
  
//     write(p[1], msg1, MSGSIZE);
//     write(p[1], msg2, MSGSIZE);
//     write(p[1], msg3, MSGSIZE);
  
//     for (i = 0; i < 3; i++) {
//         /* read pipe */
//         read(p[0], inbuf, MSGSIZE);
//         printf("%s\n", inbuf);
//     }
//     return 0;
// }


// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>
// int main()
// {

// 	// make two process which run same
// 	// program after this instruction
// 	fork();
// 	fork();
// 	fork();
// 	printf("Hello world!\n");
// 	// fork();

// 	return 0;
// }

// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>

// void forkexample()
// {
// 	int x = 1;
//     printf("fork === %d\n",fork());

// 	if (fork() == 0)
// 		printf("Child has x = %d\n", ++x);
// 	else
// 		printf("Parent has x = %d\n", --x);
// }
// int main()
// {
// 	forkexample();
// 	return 0;
// }


/*
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// int	main(void)
int	main(int argc,char *argv[])
{
	int	id;
	int	n;
	pid_t wait(int *stat_loc);

	id = fork();
	n = 0;
	if (id == 0)
		n = 1;
	else
		wait(NULL);
	int	i;
	for(i = n ; i < n + 5 ; i++)
	{
		// printf("%d " , id);
		printf("%d " , i);
		fflush(stdout); 
	}
	// printf("\n");
	return(0);
}*/

#include<unistd.h>
#include<stdio.h>

int	main(void)
{
	printf("-----Hello\n");
	printf("World\n");
	fork();
	fork();

	// printf("World\n");

	// printf("------\n");
	// printf("------\n");
	
	// printf("%lu\n", sizeof(char));
	// printf("%lu\n", sizeof(char *));
	// write(1, "Hello\n", 6);
	// write(1, "World\n", 6);

	// char	name[5];

	// scanf("Name : %s" ,name);
	// printf("%s", name);
}