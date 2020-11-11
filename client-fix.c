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
    	printf ("Client must receive 2 parametrs \n");
    	exit (1);}
    	
    
    mqd_t mq1 = mq_open (argv[1], O_WRONLY);
    
    if (mq1 == -1){
    	perror ("Failed to open message queue"); 
        exit(1);}
        
    size_t len = strlen (argv[2]);
    
    int i = mq_send(mq1, argv[2], len, 0);
    
    if (i == -1)
    {
    	perror ("Failed to send");
    	exit(1);
    }
    
    return 0;
}
