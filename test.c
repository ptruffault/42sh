#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	if (argc == 2)
		kill(getpid(), atoi(argv[1]));
}
