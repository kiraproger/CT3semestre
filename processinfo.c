#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <grp.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
int main()
{	
	pid_t cpid; // current process ID
	printf("The process ID is %d\n" , cpid);
	printf("The user ID is %d\n", getuid());
	gid_t cgid ; //current group ID
	cgid = getgid();
	printf ("The group ID is %d\n", cgid);
	struct group* cginfo = getgrgid(cgid); // current group info
	printf ("The group name is %s\n", cginfo -> gr_name);
	errno = 0;
	int cp_prio = getpriority(PRIO_PROCESS, cpid) ;//current process priority
	if (errno == 0)
		printf ("The priority of process is %d\n", cp_prio);
	// It needs, because getpriority can return -1 without maistake
	return 0;
}
	
	
	
