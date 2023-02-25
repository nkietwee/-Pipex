#include "pipex.h"

int	main(void)
{
	int pid1 = fork();
	if (pid1 != 0)
		exit (2);
	int pid2 = fork();
	if (pid2 == 0)
		exit (4);
	return (3);
}
