#include<stdio.h>
#include<unistd.h>
int main()
{
	pid_t pid, parent_pid;
	pid = fork ();
	if (pid < 0)
	{
		fprintf(stderr, "Fork failed\n");
		return 1;
	}
	else if (pid == 0)
	{
		printf("child process created.\n");
		printf("child process id:%d\n",getpid());
		printf("parent process id : %d\n",getpid());
	}
	else{
	
	printf("parent process id: %d\n", getpid());
	printf("child process id: %d\n", pid);
}
return 0;
}
