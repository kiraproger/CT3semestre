#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[])
{

	if (argc != 3){
		printf("You need 2 arguments\n");
		return 1;
	}
	
	mqd_t mq1 = mq_open (argv[1], O_RDWR );
	
	if (mq1 == -1)
	{
		perror("Failed to open queue\n");
		return 1;}

	int len = strlen(argv[2]);//we need to know message len 

	if (len > 128)
	{
		printf("Sorry, the message can't be more, than 128 symbols\n");
		exit (1);
	}
	
	char msg_len [5] = {0} ; // this is the message, in which we will sent message len, the size of msg_len is 3 because the max size of message is 128 (3 symbols)
	
	sprintf (msg_len, "%d", len);

	mq_send (mq1, msg_len, 3, 1); // we sent len of message
	mq_send (mq1, argv[2], len, 1); // we sent message

	return 0;
} 
		 
	
