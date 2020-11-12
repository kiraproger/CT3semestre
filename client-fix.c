#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

int main(int argc, char* argv[])
{
    if (argc != 3){
    	printf ("Client must receive 2 parametrs: <serverqueue> <message> \n");
    	return 1;}
    	
    
    mqd_t mq1 = mq_open (argv[1], O_WRONLY);
    
    if (mq1 == -1){
    	perror ("Failed to open message queue"); 
        return 1;}
        
    mq_send(mq1, argv[2], strlen(argv[2]), 0);
    
    if (errno == -1)
    {
    	mq_close (mq1);
    	perror ("Failed to send");
    	return 1;
    }
    
    return 0;
}
