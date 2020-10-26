#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main()
{

	struct  mq_attr mq2_inf;

	mqd_t mq1 = mq_open("/queue1",O_CREAT, &mq2_inf);
	
	if( mq1 == -1){
		perror("Failed to open");
		return 1;
	}
	
	struct  mq_attr mq1_inf;
	
	errno = 0;
	
	mq_getattr(mq1, &mq1_inf);
	
	if (errno == -1){
		perror("Failed to get attributes");
		return 1;
	}

	printf (" The maximum of messages is %ld \n", mq1_inf.mq_maxmsg);
	printf (" The maximum size of message in bytes is %ld \n", mq1_inf.mq_msgsize);
	printf (" The messages currently in queue : %ld \n" , mq1_inf.mq_curmsgs);

	return 0;
	}	
		

