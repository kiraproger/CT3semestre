#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void print_proc_info ()
{
	printf("PID = %d PPID = %d UID = %d GID = %d\n", getpid(), getppid(), getuid(), getgid());
}

int main()
{
	pid_t child_id = fork();
	
	if (child_id == -1)
	{
		perror("Failed fork");
		return 1;
	}

	if(child_id == 0)
	{
		print_proc_info();
		kill (getpid(), SIGCHLD);
		return 42;
	}

	
	int child_status;
    	waitpid(child_id, &child_status, 0);

   	if (WIFEXITED(child_status))
        	printf("child has exited, status  = %d\n", WEXITSTATUS(child_status));

    	else if (WIFSIGNALED(child_status))
        	printf("child was killed by signall '%s' (%d)\n", strsignal(WTERMSIG(child_status)), WTERMSIG(child_status));

    	else
        	printf("unexpected child status : %d\n", child_status);

    	print_proc_info();


	return 0;
}


